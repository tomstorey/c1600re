#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "C1600R.h"

#define CONSOLE_BAUD 57600      /* Baud rate for the console port */

/* PLL configuration */
#define FCY_33MHZ 33281250      /* Desired PLL output frequency at 33MHz */
#define FCY_25MHZ 24968750      /* Desired PLL output frequency at 25MHz */
#define FCY_XTAL 4000000        /* Frequency of XTAL that feeds the PLL */
#define PREEN 1                 /* Prescaler enabled (1), disabled (0) */

#define FCY_CLK2 8064000        /* Frequency of oscillator connected to CLK2 */

#define MAX_MRBLR 65535         /* The maximum number of bytes to be received
                                 * at a time by a single BD */

typedef enum {
    STATE_DEFAULT = 0,
    STATE_REINIT_RX_BD,
    STATE_PING,
    STATE_LOAD_CODE,
    STATE_EXECUTE,
    STATE_JUMP,
} state_machine_state_t;

#define COMMAND_NONE 0
#define COMMAND_RX_PING 1
#define COMMAND_TX_PONG 2
#define COMMAND_RX_LOAD_CODE 3
#define COMMAND_TX_CODE_LOADED 4
#define COMMAND_RX_EXECUTE 5
#define COMMAND_RX_JUMP 6
#define COMMAND_TX_RUNNING 7

/* Store buffer descriptors in DPRAM - two rx BDs are provided for chaining
 * the reception of large amounts of data */
volatile __SMCRxBufferDescriptor_t *rxbd = (void *)0x0FF00400;
volatile __SMCTxBufferDescriptor_t *txbd = (void *)0x0FF00410;

/* Some working buffers for the UART */
volatile uint8_t rx_buffer[256] = {0};
volatile uint8_t tx_buffer[256] = {0};

/* Current command received from the host */
volatile uint8_t command = COMMAND_NONE;

/* Current state of the bootloader state machine */
volatile state_machine_state_t state = STATE_DEFAULT;

void
init_memory_params(void)
{
    /*
     * Configure memory parameters such as DRAM refreshing, and chip selects.
     *
     * This must be done before most other things, for example, configuring the
     * PLL, as the external peripherals must be accessible to read the CPU
     * speed strap.
     */

    /* Configure DRAM memory interface parameters */
    PEPAR = 0x07C0;
    GMR = 0x07840180;

    /* CS0/ map boot ROMs at 0x04000000-0403FFFF (256KB) */
    BR0 = 0x04000003;
    OR0 = 0x5FFC0002;

    /* CS5/ and CS6/ map onboard RAM at 0x02000000-027FFFFF (8MB) */
    BR5 = 0x02000001;
    OR5 = 0x1FC00001;
    BR6 = 0x02400001;
    OR6 = 0x1FC00001;

    /* CS3/ to map external peripherals at 0x0D000000-0D0FFFFF (1MB) */
    BR3 = 0x0D000001;
    OR3 = 0xFFF00006;
}

void
init_pll(void)
{
    /*
     * Configure the PLL for operational frequency
     * 
     * Requires chip selects to be configured first so that the SYSOPT register
     * can be read to determine CPU speed strap.
     * 
     * The MODCK1-0 configuration on the 1600R is binary 10, this enables the
     * PLL as well as dividing the XTAL frequency by 128 by default on reset.
     * Thus, only the multiplication factor needs to be changed. The prescaler
     * can be disabled, refer to the MC68360 UM for details.
     */
    if (SYSOPTbits.SPEED == 0) {
        PLLCRbits.MF = (FCY_33MHZ / (FCY_XTAL / 128));
    } else {
        PLLCRbits.MF = (FCY_25MHZ / (FCY_XTAL / 128));
    }
}

void
init_others(void)
{
    /*
     * Initialise other registers
     */
    SYPCR = 0x47;               /* Enables bus monitor, disable dog */
    SDCR = 0x740;               /* Recommended by User Manual */

    CICR = 0x390001;            /* SCC priorities and spreading */
    CICRbits.IRL = 4;           /* CPM IRQ level */
    CICRbits.HP = 0b11111;      /* Highest priority interrupt is PORTC */
    CICRbits.VBA = 0b101;       /* Upper 3 bits of CPM interrupt vector */
    
    CR = 0x8001;                /* Reset the CP */

    /* Disable and clear any CP interrupts that might be present */
    CIMR = 0;
    CIPR = 0xFFFFFFFF;
    CISR = 0xFFFFFFFF;
}

void
init_size_and_test_ram(void)
{
    /* TODO */
}

void
init_bss_and_data(void)
{
    /*
     * Zeroise the BSS area and copy initialised data to RAM
     * 
     * Requires chip selects to be configured first so that the RAM banks are
     * accessible.
     */
    extern uint32_t _bss_start;
    extern uint32_t _bss_end;
    extern uint32_t _rodata_end;
    extern uint32_t _data_start;
    extern uint32_t _data_end;
    uint32_t *src;
    uint32_t *dst;

    /* BSS */
    for (dst = (uint32_t *)&_bss_start; dst < (uint32_t *)&_bss_end; dst++) {
        *dst = 0;
    }

    /* Initialised data */
    for (src = (uint32_t *)&_rodata_end, dst = (uint32_t *)&_data_start;
         dst < (uint32_t *)&_data_end;
         src++, dst++) {
        *dst = *src;
    }
}

void
init_ports(void)
{
    /*
     * Initialise PORTA, PORTB, PORTC pins as required by internal peripherals
     */
    PBPAR = 0;
    PBPARbits.DD6 = 1;          /* PB6 is console tx, SMTXD1 */
    PBPARbits.DD7 = 1;          /* PB7 is console rx, SMRXD1 */

    PBDIR = 0;
    PBDIRbits.DR8 = 1;          /* PB8 is output, console DTR (sw control)
                                 * PB9 is input, console DST (sw control) */
    
    PBODR = 0;
}

void
init_console_uart(void)
{
    /*
     * Initialise SMC1 - console port
     */

    /* Configure baud rate generator
     *
     * The Clock Divider can be calculated as such:
     *
     * system frequency / (baud * 16); e.g.
     * 33281250 / (9600 * 16)
     *
     * This gives a CD of 216.67 which could be rounded to either 216 or 217
     * with approx +/- 30bps error (9629 or 9585 respectively).
     *
     * Error rate as a percentage can be calculated as, e.g.:
     *
     * ((9585 - 9600) / 9600) * 1000 = -1.56%
     * ((9629 - 9600) / 9600) * 1000 = +3.02%
     *
     * An absolute error rate of less than 5% is acceptable. */
    BRGC1bits.RST = 1;          /* Reset the BRG */

    if (SYSOPTbits.SPEED == 0) {
        /* Configure clock divider to produce the desired baud rate at 33MHz,
         * and enable the BRG */
        BRGC1bits.CD = (FCY_33MHZ / (CONSOLE_BAUD * 16));
        BRGC1bits.EN = 1;
    } else {
        /* Configure clock divider to produce the desired baud rate at 25MHz,
         * and enable the BRG */
        BRGC1bits.CD = (FCY_25MHZ / (CONSOLE_BAUD * 16));
        BRGC1bits.EN = 1;
    }

    SIMODEbits.SMC1 = 0;        /* Connect BRG1 to SMC1 */
    SIMODEbits.SMC1CS = 0;

    /* Set buffer descriptor pointers */
    SMC1RBASE = (uint16_t)((uint32_t)rxbd);
    SMC1TBASE = (uint16_t)((uint32_t)txbd);

    /* Initialise BDs */
    CRbits.OPCODE = 0;          /* Init tx/rx params */
    CRbits.CHNUM = 9;           /* Ch 9 = SMC1 */
    CRbits.FLG = 1;             /* Do it */

    /* Setup function codes for SMC SDMA channels */
    SMC1RFCRbits.MOT = 1;       /* Motorola byte ordering */
    SMC1RFCRbits.FC = 8;        /* Function code */
    SMC1TFCRbits.MOT = 1;
    SMC1TFCRbits.FC = 8;
    
    SMC1MRBLR = 1;              /* Maximum receive buffer length */

    SMC1MAX_IDL = 0;            /* Disable idle function */

    /* Configure the tx and rx buffer descriptors */
    txbd->SRC = NULL;
    txbd->LEN = 0;
    txbd->flags.W = 1;          /* This is the last BD in the chain */

    rxbd[0].DST = (uint8_t *)&rx_buffer;
    rxbd[0].flags.W = 1;         /* This is the last BD in the chain for now */
    rxbd[0].flags.I = 1;         /* Interrupt on closure */
    rxbd[0].flags.E = 1;         /* BD is empty - CP owns this BD now */

    rxbd[1].DST = (uint8_t *)NULL;
    rxbd[1].flags.W = 1;
    rxbd[1].flags.I = 1;

    /* Configure SMC1 for UART, 8 bits, no parity */
    SMCMR1 = 0;
    SMCMR1bits.CLEN = 9;        /* 8 data bits */
    SMCMR1bits.SM = 2;          /* UART mode */
}

void
init_final(void)
{
    /*
     * Final initialisation, configure things like interrupts, and finish
     * initialising peripherals.
     * 
     * This should be done last, and sets everything in motion.
     */

    /* SMC1 - UART */
    SMCE1 = 0xFF;               /* Clear all event bits */
    SMCM1bits.RX = 1;           /* Enable rx interrupts */
    CIMRbits.SMC1 = 1;          /* Enable interrupts for SMC1 */
    SMCMR1bits.TEN = 1;         /* Enable transmitter */
    SMCMR1bits.REN = 1;         /* Enable receiver */
    PBDATbits.D8 = 0;           /* DTR to idle state */

    /* Unmask interrupts */
    asm volatile ("andi.w #0xF8FF, %sr");
}

int
main(void)
{
    uint32_t code_len = 0;
    uint32_t addr = 0;
    uint8_t bd_idx = 0;
    uint32_t ctr;

    /* Initialise all the everythings */
    init_memory_params();
    init_pll();
    init_others();
    init_size_and_test_ram();
    init_bss_and_data();
    init_ports();
    init_console_uart();
    init_final();

    /* Infinite loop for the state machine */
    for (;;) {
        switch (state) {
            case STATE_PING:
                /* The loader script can ping the bootloader to see when it is
                 * ready to accept data */
                tx_buffer[0] = (uint8_t)COMMAND_TX_PONG;

                txbd->SRC = (uint8_t *)&tx_buffer;
                txbd->LEN = 1;
                txbd->flags.u16 = 0xA000;

                while (txbd->flags.R == 1);

                state = STATE_REINIT_RX_BD;

                break;
            
            case STATE_LOAD_CODE:
                /* Loading code
                 *
                 * The first thing to do is get the length of the data that
                 * is being received */
                SMC1MRBLR = 4;
                rxbd[0].DST = (uint8_t *)&code_len;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Next get the address where the data is to be loaded */
                SMC1MRBLR = 4;
                rxbd[0].DST = (uint8_t *)&addr;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Finally, receive the data itself this is done by alternating
                 * through rx BDs, ensuring one is always setup and ready to
                 * receive more data when the current one closes. */
                bd_idx = 0;

                while (code_len > 0) {
                    /* Delay while target buffer descriptor is in use */
                    while (rxbd[bd_idx].flags.E);

                    /* How much more data can we receive? */
                    if (code_len > MAX_MRBLR) {
                        SMC1MRBLR = MAX_MRBLR;
                    } else {
                        SMC1MRBLR = code_len;
                    }

                    rxbd[bd_idx].DST = (uint8_t *)addr;
                    addr += SMC1MRBLR;
                    code_len -= SMC1MRBLR;

                    if (code_len == 0) {
                        /* This is the last BD that needs to be configured, so
                         * set the W flag regardless of which one it is */
                        rxbd[bd_idx].flags.u16 = 0xA000;
                    } else {
                        /* There will be more data to come, so make sure the W
                         * flag is set correctly in BD 0 to ensure that BD 1
                         * can still be used */
                        if (bd_idx == 0) {
                            /* Do not set the W flag for BD 0 */
                            rxbd[bd_idx].flags.u16 = 0x8000;
                        } else {
                            /* Set the W flag for BD 1 */
                            rxbd[bd_idx].flags.u16 = 0xA000;
                        }
                    }

                    bd_idx = (bd_idx + 1) & 0x1;
                }

                /* Wait for both BDs to close */
                while (rxbd[0].flags.E || rxbd[1].flags.E);

                /* Respond with code loaded */
                tx_buffer[0] = (uint8_t)COMMAND_TX_CODE_LOADED;

                txbd->SRC = (uint8_t *)&tx_buffer;
                txbd->LEN = 1;
                txbd->flags.u16 = 0xA000;

                while (txbd->flags.R == 1);

                /* Done */
                state = STATE_REINIT_RX_BD;

                break;
                
            case STATE_EXECUTE:
            case STATE_JUMP:
                /* When executing, receive 4 bytes that will form the address
                 * to jump to, then JSR or JMP to that address */
                SMC1MRBLR = 4;
                rxbd[0].DST = (uint8_t *)&addr;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Respond with running */
                tx_buffer[0] = (uint8_t)COMMAND_TX_RUNNING;

                txbd->SRC = (uint8_t *)&tx_buffer;
                txbd->LEN = 1;
                txbd->flags.u16 = 0xA000;

                while (txbd->flags.R == 1);

                /* Delay a bit to ensure last operation has completed */
                for (ctr = 500; ctr > 0; ctr--);

                if (state == STATE_EXECUTE) {
                    asm volatile(
                        /* Put addr into A0 then jump to subroutine  */
                        "movea.l    %[addr], %%a0                   \n\t"
                        "jsr        %%a0@                           \n\t"

                        /* If the user code should happen to return, and if
                         * it should happen to work successfully, go back
                         * to default state */
                        :
                        :[addr]"rm"(addr)
                        :
                    );

                    state = STATE_REINIT_RX_BD;
                } else {
                    asm volatile(
                        /* Put addr into A0 then jump  */
                        "movea.l    %[addr], %%a0                   \n\t"
                        "jmp        %%a0@                           \n\t"

                        /* User code cannot return from a jump */
                        :
                        :[addr]"rm"(addr)
                        :
                    );
                }

                break;

            case STATE_REINIT_RX_BD:
                /* Re-initialise the rx BD to receive another command */
                state = STATE_DEFAULT;

                /* Delay a bit to ensure last operation has completed */
                for (ctr = 500; ctr > 0; ctr--);

                SMC1MRBLR = 1;
                rxbd[0].DST = (uint8_t *)&rx_buffer;
                rxbd[0].flags.u16 = 0xB000;

                /* Fall through to default state */

            case STATE_DEFAULT:
            default:
                /* Set the OK LED to indicate waiting for a command, all other
                 * LEDs off */
                LEDCR = 0x7F;

                /* Set the next state machine state based on the command */
                switch (command) {
                    case COMMAND_RX_PING:
                        /* Respond to ping */
                        state = STATE_PING;

                        break;

                    case COMMAND_RX_LOAD_CODE:
                        /* Loading code */
                        state = STATE_LOAD_CODE;

                        break;

                    case COMMAND_RX_EXECUTE:
                        /* Execute (JSR) to an address */
                        state = STATE_EXECUTE;

                        break;

                    case COMMAND_RX_JUMP:
                        /* Execute (JMP) to an address */
                        state = STATE_JUMP;

                        break;

                    case COMMAND_NONE:
                        /* Do nothing */
                        break;

                    default:
                        /* Invalid command */
                        command = COMMAND_NONE;
                        state = STATE_REINIT_RX_BD;

                        break;
                }

                if (state != STATE_DEFAULT) {
                    /* If we have switched state, initialise stuff */
                    command = COMMAND_NONE;

                    /* Clear the OK LED */
                    LEDCRbits.OK = 1;
                }

                break;
        }
    }

    return 0;
}

void __attribute__((interrupt))
SMC1InterruptHandler(void)
{
    /* Get pended interrupts */
    const __SMCEbits_t events = (*(__SMCEbits_t *)&SMCE1);

    if (events.RX == 1) {
        if (state == STATE_DEFAULT) {
            /* If the state machine is in default state, the first received
             * byte is a command */
            command = rx_buffer[0];
        }
    }

    SMCE1 = events.u8;          /* Clear interrupts that were pended */
    CISR = 0x10;                /* Reset CISR bit */
}
