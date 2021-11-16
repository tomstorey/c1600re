#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "C1600R.h"

/* Uncomment to use SCC3 via the WIC slot for higher speed bootloading */
#define USE_SCC3_UART

#ifdef USE_SCC3_UART
#define CONSOLE_BAUD 230400     /* Baud rate for the console port */
#define MRBLR_REG SCC3MRBLR
#else /* USE_SCC3_UART */
#define CONSOLE_BAUD 57600      /* Baud rate for the console port */
#define MRBLR_REG SMC1MRBLR
#endif /* USE_SCC3_UART */

#define MAX_MRBLR 65535         /* The maximum number of bytes to be received
                                 * at a time by a single BD */
#define MAX_TXDATA 256          /* The maximum number of bytes to be sent at a
                                 * time by a single BD */

typedef enum {
    STATE_DEFAULT = 0,
    STATE_REINIT_RX_BD,
    STATE_PING,
    STATE_LOAD_CODE,
    STATE_EXECUTE,
    STATE_JUMP,
    STATE_READ_MEM,
    STATE_WRITE_MEM,
} state_machine_state_t;

enum {
    COMMAND_NONE = 0,
    COMMAND_RX_PING,
    COMMAND_TX_PONG,
    COMMAND_RX_LOAD_CODE,
    COMMAND_TX_CODE_LOADED,
    COMMAND_RX_EXECUTE,
    COMMAND_RX_JUMP,
    COMMAND_TX_RUNNING,
    COMMAND_RX_READ_MEM,
    COMMAND_TX_READ_MEM,
    COMMAND_RX_WRITE_MEM,
    COMMAND_TX_WRITE_MEM,
};

/* Store buffer descriptors in DPRAM - two rx BDs are provided for chaining
 * the reception of large amounts of data */
#ifdef USE_SCC3_UART
volatile __SCCUARTRxBufferDescriptor_t *rxbd = (void *)(MODULE_BASE+0x400);
volatile __SCCUARTTxBufferDescriptor_t *txbd = (void *)(MODULE_BASE+0x410);
#else /* USE_SCC3_UART */
volatile __SMCRxBufferDescriptor_t *rxbd = (void *)(MODULE_BASE+0x400);
volatile __SMCTxBufferDescriptor_t *txbd = (void *)(MODULE_BASE+0x410);
#endif /* USE_SCC3_UART */

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
    MCR = 0x00007FFF;

    /* Configure DRAM memory interface parameters */
    PEPAR = 0x07C0;
    GMR = 0x07840180;

    /* CS3/ to map external peripherals at 0x0D000000-0D0FFFFF (1MB) */
    OR3 = 0xFFF00006;
    BR3 = 0x0D000001;

    /* CS4/ to map PCMCIA at 0x08000000-09FFFFFF (32MB) */
    OR4 = 0xFE000006;
    BR4 = 0x08000001;

    /* CS7/ to map NVRAM at 0x0E000000-0E007FFF (32KB) */
    OR7 = 0x6FFF8004;
    BR7 = 0x0E000001;

    /* CS0/ map boot ROMs at 0x04000000-0403FFFF (4MB) */
    BR0 = 0x04000003;
    OR0 = 0x5FC00002;

    /* CS5/ and CS6/ map onboard RAM at 0x02000000-027FFFFF (8MB) */
    BR5 = 0x02000001;
    OR5 = 0x1FC00001;
    BR6 = 0x02400001;
    OR6 = 0x1FC00001;
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
    SDCR = 0x0740;              /* Recommended by User Manual */

    CICR = 0x390001;            /* SCC priorities and spreading */
    CICRbits.IRL = 4;           /* CPM IRQ level */
    CICRbits.HP = 0b11111;      /* Highest priority interrupt is PORTC */
    CICRbits.VBA = 0b111;       /* Upper 3 bits of CPM interrupt vector */
    
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
    PAPAR = 0;
    PBPAR = 0;
    PCPAR = 0;

    PADIR = 0;
    PBDIR = 0;
    PCDIR = 0;

    PAODR = 0;
    PBODR = 0;

#ifdef USE_SCC3_UART
    PAPARbits.DD4 = 1;          /* PA4 = RXD3 */
    PAPARbits.DD5 = 1;          /* PA5 = TXD3 */
#else /* USE_SCC3_UART */
    PBPARbits.DD6 = 1;          /* PB6 is console tx, SMTXD1 */
    PBPARbits.DD7 = 1;          /* PB7 is console rx, SMRXD1 */

    PBDIRbits.DR8 = 1;          /* PB8 is output, console DTR (sw control)
                                 * PB9 is input, console DST (sw control) */
#endif /* USE_SCC3_UART */
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
    BRGC1 = 1 << _BRGC1_RST_POSITION; /* Reset the BRG */

    if (SYSOPTbits.SPEED == 0) {
        /* Configure clock divider to produce the desired baud rate at 33MHz,
         * and enable the BRG */
        BRGC1bits.CD = (FCY_33MHZ / (CONSOLE_BAUD * 16));
    } else {
        /* Configure clock divider to produce the desired baud rate at 25MHz,
         * and enable the BRG */
        BRGC1bits.CD = (FCY_25MHZ / (CONSOLE_BAUD * 16));
    }

    BRGC1bits.ATB = 0;
    BRGC1bits.EN = 1;

#ifdef USE_SCC3_UART
    /* Connect BRG1 to SCC3 */
    SICRbits.R3CS = 0;
    SICRbits.T3CS = 0;
    SICRbits.SC3 = 0;

    /* Set buffer descriptor pointers */
    SCC3RBASE = (uint16_t)((uint32_t)rxbd);
    SCC3TBASE = (uint16_t)((uint32_t)txbd);

    /* Setup function codes for SCC SDMA channels */
    SCC3RFCRbits.MOT = 1;       /* Motorola byte ordering */
    SCC3RFCRbits.FC = 8;        /* Function code */
    SCC3TFCRbits.MOT = 1;
    SCC3TFCRbits.FC = 8;

    SCC3MRBLR = 1;              /* Maximum receive buffer length */

    /* Clear/initialise defaults as recommended by the User Manual */
    SCC3MAX_IDL = 0;
    SCC3BRKCR = 0;
    SCC3PAREC = 0;
    SCC3FRMEC = 0;
    SCC3NOSEC = 0;
    SCC3BRKEC = 0;
    SCC3UADDR1 = 0;
    SCC3UADDR2 = 0;
    SCC3TOSEQ = 0;
    SCC3CHARACTER1 = 0x8000;
    SCC3CHARACTER2 = 0x8000;
    SCC3CHARACTER3 = 0x8000;
    SCC3CHARACTER4 = 0x8000;
    SCC3CHARACTER5 = 0x8000;
    SCC3CHARACTER6 = 0x8000;
    SCC3CHARACTER7 = 0x8000;
    SCC3CHARACTER8 = 0x8000;
    SCC3RCCM = 0xC0FF;

    /* Configure SCC3 clocking, UART mode, 8 bits, no parity */
    GSMR3H = 0;
    GSMR3L = 0;
    GSMR3Hbits.RTSM = 0;
    GSMR3Lbits.MODE = 4;        /* UART mode */
    GSMR3Lbits.RDCR = 2;        /* 16x clock mode for RX */
    GSMR3Lbits.TDCR = 2;        /* 16x clock mode for TX */
    PSMR3 = 0;                  /* Disable parity and flow control */
    PSMR3UARTbits.CL = 3;       /* 8 bit chars */
#else /* USE_SCC3_UART */
    /* Connect BRG1 to SMC1 */
    SIMODEbits.SMC1 = 0;
    SIMODEbits.SMC1CS = 0;

    /* Set buffer descriptor pointers */
    SMC1RBASE = (uint16_t)((uint32_t)rxbd);
    SMC1TBASE = (uint16_t)((uint32_t)txbd);

    /* Setup function codes for SMC SDMA channels */
    SMC1RFCRbits.MOT = 1;       /* Motorola byte ordering */
    SMC1RFCRbits.FC = 8;        /* Function code */
    SMC1TFCRbits.MOT = 1;
    SMC1TFCRbits.FC = 8;
    
    SMC1MRBLR = 1;              /* Maximum receive buffer length */

    SMC1MAX_IDL = 0;            /* Disable idle function */

    /* Configure SMC1 for UART, 8 bits, no parity */
    SMCMR1 = 0;
    SMCMR1bits.CLEN = 9;        /* 8 data bits */
    SMCMR1bits.SM = 2;          /* UART mode */
#endif /* USE_SCC3_UART */

    /* Configure the tx and rx buffer descriptors */
    txbd[0].SRC = NULL;
    txbd[0].LEN = 0;
    txbd[0].flags.u16 = 0x2000;

    txbd[1].SRC = NULL;
    txbd[1].LEN = 0;
    txbd[1].flags.u16 = 0x2000;

    rxbd[0].DST = (uint8_t *)&rx_buffer;
    rxbd[0].flags.u16 = 0xB000;

    rxbd[1].DST = (uint8_t *)NULL;
    rxbd[1].flags.u16 = 0x3000;

#ifdef USE_SCC3_UART
    /* Init SCC3 params */
    CRbits.OPCODE = 0;          /* Init tx/rx params */
    CRbits.CHNUM = 8;           /* Ch 9 = SCC3 */
    CRbits.FLG = 1;             /* Do it */
#else /* USE_SCC3_UART */
    /* Init SMC1 params */
    CRbits.OPCODE = 0;          /* Init tx/rx params */
    CRbits.CHNUM = 9;           /* Ch 9 = SMC1 */
    CRbits.FLG = 1;             /* Do it */
#endif /* USE_SCC3_UART */
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

#ifdef USE_SCC3_UART
    /* Configure interrupts for SCC3 */
    SCCE3 = 0xFFFF;             /* Clear any pending events */
    SCCM3UARTbits.RX = 1;       /* Enable RX interrupts */
    CIMRbits.SCC3 = 1;          /* Enable interrupts for SCC3 */

    /* Enable transmitter and receiver */
    GSMR3Lbits.ENT = 1;
    GSMR3Lbits.ENR = 1;
#else /* USE_SCC3_UART */
    /* Configure interrupts for SMC1 */
    SMCE1 = 0xFF;               /* Clear all event bits */
    SMCM1bits.RX = 1;           /* Enable rx interrupts */
    CIMRbits.SMC1 = 1;          /* Enable interrupts for SMC1 */

    /* Enable transmitter and receiver */
    SMCMR1bits.TEN = 1;         /* Enable transmitter */
    SMCMR1bits.REN = 1;         /* Enable receiver */

    PBDATbits.D8 = 0;           /* DTR to idle state */
#endif /* USE_SCC3_UART */

    /* Unmask interrupts */
    asm volatile ("andi.w #0xF8FF, %sr");
}

int
main(void)
{
    uint32_t data_len = 0;
    uint32_t addr = 0;
    uint8_t bd_idx = 0;
    uint32_t ctr;
    uint8_t data_type = 0;
    uint8_t data_u8;
    uint16_t data_u16;
    uint32_t data_u32;

    /* Initialise all the everythings */
    init_memory_params();
    init_pll();
    init_others();
    init_size_and_test_ram();
    init_bss_and_data();
    init_ports();
    init_console_uart();
    init_final();

    /* Set the OK LED to indicate waiting for a command, all other
     * LEDs off */
    LEDCR = 0x7F;

    /* Infinite loop for the state machine */
    for (;;) {
        switch (state) {
            case STATE_PING:
                /* The loader script can ping the bootloader to see when it is
                 * ready to accept data */
                tx_buffer[0] = (uint8_t)COMMAND_TX_PONG;

                txbd[0].SRC = (uint8_t *)&tx_buffer;
                txbd[0].LEN = 1;
                txbd[0].flags.u16 = 0xA000;

                while (txbd[0].flags.R == 1);

                state = STATE_REINIT_RX_BD;

                break;
            
            case STATE_LOAD_CODE:
                /* Loading code
                 *
                 * The first thing to do is get the length of the data that
                 * is being received */
                MRBLR_REG = 4;
                rxbd[0].DST = (uint8_t *)&data_len;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Next get the address where the data is to be loaded */
                rxbd[0].DST = (uint8_t *)&addr;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Finally, receive the data itself this is done by alternating
                 * through rx BDs, ensuring one is always setup and ready to
                 * receive more data when the current one closes. */
                bd_idx = 0;

                while (data_len > 0) {
                    /* Delay while next buffer descriptor is in use */
                    while (rxbd[bd_idx].flags.E);

                    /* How much more data can we receive? */
                    if (data_len > MAX_MRBLR) {
                        MRBLR_REG = MAX_MRBLR;
                    } else {
                        MRBLR_REG = data_len;
                    }

                    rxbd[bd_idx].DST = (uint8_t *)addr;
                    addr += MRBLR_REG;
                    data_len -= MRBLR_REG;

                    if (data_len == 0) {
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
                            /* Always set the W flag for BD 1 */
                            rxbd[bd_idx].flags.u16 = 0xA000;
                        }
                    }

                    bd_idx = (bd_idx + 1) & 0x1;
                }

                /* Wait for both BDs to close */
                while (rxbd[0].flags.E || rxbd[1].flags.E);

                /* Respond with code loaded */
                tx_buffer[0] = (uint8_t)COMMAND_TX_CODE_LOADED;

                txbd[0].SRC = (uint8_t *)&tx_buffer;
                txbd[0].LEN = 1;
                txbd[0].flags.u16 = 0xA000;

                while (txbd[0].flags.R == 1);

                /* Done */
                state = STATE_REINIT_RX_BD;

                break;
                
            case STATE_EXECUTE:
            case STATE_JUMP:
                /* When executing, receive 4 bytes that will form the address
                 * to jump to, then JSR or JMP to that address */
                MRBLR_REG = 4;
                rxbd[0].DST = (uint8_t *)&addr;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Respond with running */
                tx_buffer[0] = (uint8_t)COMMAND_TX_RUNNING;

                txbd[0].SRC = (uint8_t *)&tx_buffer;
                txbd[0].LEN = 1;
                txbd[0].flags.u16 = 0xA000;

                while (txbd[0].flags.R == 1);

                /* Delay a bit to ensure last operation has completed */
                for (ctr = 50000; ctr > 0; ctr--);

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

            case STATE_READ_MEM:
                /* Reading memory
                 *
                 * The first thing to do is to get the length of the memory
                 * that is to be read - this indicates the number of bytes. */
                MRBLR_REG = 4;
                rxbd[0].DST = (uint8_t *)&data_len;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Next get the address where the data is to be loaded */
                rxbd[0].DST = (uint8_t *)&addr;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Respond to say that data will follow, and setup the first
                 * tx BD to send the first lot of data */
                tx_buffer[0] = (uint8_t)COMMAND_TX_READ_MEM;

                txbd[0].SRC = (uint8_t *)&tx_buffer;
                txbd[0].LEN = 1;
                txbd[0].flags.u16 = 0x8000;

                bd_idx = 1;

                while (data_len > 0) {
                    /* Delay while next buffer descriptor is in use */
                    while (txbd[bd_idx].flags.R);

                    /* How much more data can we send? */
                    if (data_len > MAX_TXDATA) {
                        txbd[bd_idx].LEN = MAX_TXDATA;
                    } else {
                        txbd[bd_idx].LEN = data_len;
                    }

                    txbd[bd_idx].SRC = (uint8_t *)addr;
                    addr += txbd[bd_idx].LEN;
                    data_len -= txbd[bd_idx].LEN;

                    if (data_len == 0) {
                        /* This is the last BD that needs to be configured, so
                         * set the W flag regardless of which one it is */
                        txbd[bd_idx].flags.u16 = 0xA000;
                    } else {
                        /* There will be more data to send, so make sure the W
                         * flag is set correctly in BD 0 to ensure that BD 1
                         * can still be used */
                        if (bd_idx == 0) {
                            /* Do not set the W flag for BD 0 */
                            txbd[bd_idx].flags.u16 = 0x8000;
                        } else {
                            /* Always set the W flag for BD 1 */
                            txbd[bd_idx].flags.u16 = 0xA000;
                        }
                    }

                    bd_idx = (bd_idx + 1) & 0x1;
                }

                /* Wait for both BDs to close */
                while (txbd[0].flags.R || txbd[1].flags.R);

                /* Done */
                state = STATE_REINIT_RX_BD;

                break;

            case STATE_WRITE_MEM:
                /* Writing memory
                 *
                 * Memory can be written as byte, word, or long types.
                 *
                 * The first step is to receive the type that is to be written.
                 * This comes in the form of a single byte specifying the byte
                 * width of the type (1 for byte, 2 for word, 4 for long). */
                MRBLR_REG = 1;
                rxbd[0].DST = (uint8_t *)&data_type;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Next is a 32 bit value specifying the number of writes of
                 * that type to be performed. */
                MRBLR_REG = 4;
                rxbd[0].DST = (uint8_t *)&data_len;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Next get the address where the data is to be loaded */
                rxbd[0].DST = (uint8_t *)&addr;
                rxbd[0].flags.u16 = 0xA000;

                while (rxbd[0].flags.E == 1);

                /* Setup how many bytes to receive for each piece of data */
                MRBLR_REG = data_type;

                /* All subsequent data is then the data to be written. */
                while (data_len > 0) {
                    if (data_type == 0x01) {
                        rxbd[0].DST = (uint8_t *)&data_u8;
                    } else if (data_type == 0x02) {
                        rxbd[0].DST = (uint8_t *)&data_u16;
                    } else if (data_type == 0x04) {
                        rxbd[0].DST = (uint8_t *)&data_u32;
                    }

                    rxbd[0].flags.u16 = 0xA000;

                    while (rxbd[0].flags.E == 1);

                    if (data_type == 0x01) {
                        *(uint8_t *)addr = data_u8;
                    } else if (data_type == 0x02) {
                        *(uint16_t *)addr = data_u16;
                    } else if (data_type == 0x04) {
                        *(uint32_t *)addr = data_u32;
                    }

                    addr += data_type;
                    data_len--;
                }

                /* Respond with code loaded */
                tx_buffer[0] = (uint8_t)COMMAND_TX_WRITE_MEM;

                txbd[0].SRC = (uint8_t *)&tx_buffer;
                txbd[0].LEN = 1;
                txbd[0].flags.u16 = 0xA000;

                while (txbd[0].flags.R == 1);

                /* Done */
                state = STATE_REINIT_RX_BD;

                break;

            case STATE_REINIT_RX_BD:
                /* Re-initialise the rx BD to receive another command */
                state = STATE_DEFAULT;
                command = COMMAND_NONE;

                /* Delay a bit to ensure last operation has completed */
                for (ctr = 500; ctr > 0; ctr--);

                MRBLR_REG = 1;
                rxbd[0].DST = (uint8_t *)&rx_buffer;
                rxbd[0].flags.u16 = 0xB000;

                /* Set the OK LED */
                LEDCRbits.OK = 0;

                /* Fall through to default state */

            case STATE_DEFAULT:
            default:
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

                    case COMMAND_RX_READ_MEM:
                        /* Reading memory */
                        state = STATE_READ_MEM;

                        break;

                    case COMMAND_RX_WRITE_MEM:
                        /* Writing memory */
                        state = STATE_WRITE_MEM;

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

#ifdef USE_SCC3_UART
void __attribute__((interrupt))
SCC3InterruptHandler(void)
{
    const __SCCEUARTbits_t events = { .u16 = SCCE3 };

    if (events.RX) {
        if (state == STATE_DEFAULT) {
            /* If the state machine is in default state, the first received
             * byte is a command */
            command = rx_buffer[0];
        }
    }

    /* Clear event/interrupt flags */
    SCCE3 = events.u16;
    CISR = 1 << _CISR_SCC3_POSITION;
}
#else /* USE_SCC3_UART */
void __attribute__((interrupt))
SMC1InterruptHandler(void)
{
    /* Get pended interrupts */
    const __SMCEbits_t events = { .u8 = SMCE1 };

    if (events.RX) {
        if (state == STATE_DEFAULT) {
            /* If the state machine is in default state, the first received
             * byte is a command */
            command = rx_buffer[0];
        }
    }

    /* Clear event/interrupt flags */
    SMCE1 = events.u8;
    CISR = 1 << _CISR_SMC1_POSITION;
}
#endif /* USE_SCC3_UART */
