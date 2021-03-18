#include <stdint.h>
#include <stdbool.h>

#include "C1600R.h"

#include "FreeRTOS-Kernel/include/FreeRTOS.h"
#include "FreeRTOS-Kernel/include/task.h"
#include "FreeRTOS-Kernel/include/timers.h"

/* PLL configuration */
#define FCY_33MHZ 33281250      /* Desired PLL output frequency at 33MHz */
#define FCY_25MHZ 24968750      /* Desired PLL output frequency at 25MHz */
#define FCY_XTAL 4000000        /* Frequency of XTAL that feeds the PLL */

static TaskHandle_t task1_handle = NULL;
static TaskHandle_t task2_handle = NULL;
static TaskHandle_t task3_handle = NULL;
static TaskHandle_t task4_handle = NULL;
static TaskHandle_t task5_handle = NULL;

static void task1(void *param);
static void task2(void *param);
static void task3(void *param);
static void task4(void *param);
static void task5(void *param);

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
    extern uint32_t __ram_end;

    /* CS3/ to map external peripherals at 0x0D000000-0D0FFFFF (1MB) */
    BR3 = 0x0D000001;
    OR3 = 0xFFF00006;

    /* CS0/ map boot ROMs at 0x04000000-0403FFFF (256KB) */
    BR0 = 0x04000003;
    OR0 = 0x5FFC0002;

    /* Configure DRAM memory interface parameters */
    PEPAR = 0x07C0;
    GMR = 0x07840180;

    /* CS5/ and CS6/ map on-board RAM at 0x02000000-027FFFFF (8MB) */
    BR5 = 0x02000001;
    OR5 = 0x1FC00001;
    BR6 = 0x02400001;
    OR6 = 0x1FC00001;

    /* Relocate the stack out of the internal DPRAM and into on-board RAM */
    asm volatile(
        /* Figure out how many words to copy from old stack to new stack */
        "    move.l  #0x0ff00400, %%d0      \n\t"
        "    move.l  %%sp, %%d1             \n\t"
        "    sub.l   %%d1, %%d0             \n\t"
        "    move.l  %%d0, %%d1             \n\t" /* D1 = num of bytes used */
        "    lsr.l   #1, %%d0               \n\t" /* D0 = words to copy */
        "    movea.l %%sp, %%a5             \n\t"
        "    adda.l  %%d1, %%a5             \n\t" /* A5 = top of old stack */
        "    movea.l #%[ram_end], %%sp      \n\t" /* A7 = top of new stack */

        /* Copy old stack to new stack */
        "0:  move.w  %%a5@-, %%sp@-         \n\t"
        "    subq.l  #1, %%d0               \n\t"
        "    bne     0b                     \n\t"

        /* Fix up the frame pointer */
        "    adda.l  %%d1, %%a5             \n\t"
        "    suba.l  %%fp, %%a5             \n\t" /* A5 is frame size */
        "    movea.l #%[ram_end], %%fp      \n\t" /* FP = top of new stack */
        "    suba.l  %%a5, %%fp             \n\t" /* Subtract frame size */
        :
        :[ram_end]"rm"(__ram_end)
    );
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
init_final(void)
{
    /*
     * Final initialisation, configure things like interrupts, and finish
     * initialising peripherals.
     * 
     * This should be done last, and sets everything in motion.
     */

    /* Unmask interrupts */
    asm volatile("andi.w #0xF8FF, %sr");
}

void
vApplicationSetupInterrupts(void)
{
    /* Configure a timer to generate tick interrupt */
    PICRbits.PIRQL = 1;         /* IRQ 1 */
    PICRbits.PIV = 0x40;        /* Vector 0x40 */
    PITRbits.CTR = 0x4E;        /* Approx 10ms */

    portENABLE_INTERRUPTS();
}

int
main(void)
{
    /* Initialise all the everythings */
    init_memory_params();
    init_pll();
    init_others();
    init_bss_and_data();
    init_final();

    /* Create some tasks */
    xTaskCreate(task1, "OK LED Task", 256, NULL, 3, &task1_handle);
    xTaskCreate(task2, "LED1 Task", 256, NULL, 3, &task2_handle);
    xTaskCreate(task3, "LED2 Task", 256, NULL, 3, &task3_handle);
    xTaskCreate(task4, "LED3 Task", 256, NULL, 3, &task4_handle);
    xTaskCreate(task5, "LED4 Task", 256, NULL, 3, &task5_handle);

    vTaskStartScheduler();

    while (true);

    return 0;
}

void __attribute__((interrupt))
PeriodicInterruptTimer(void)
{
    /* Tick */
    asm volatile("trap #14");
}

void
task1(void *param)
{
    while (true) {
        LEDCRbits.OK ^= 1;

        vTaskDelay(47);
    }
}

void
task2(void *param)
{
    while (true) {
        LEDCRbits.LED1 ^= 1;

        vTaskDelay(58);
    }
}

void
task3(void *param)
{
    while (true) {
        LEDCRbits.LED2 ^= 1;

        vTaskDelay(65);
    }
}

void
task4(void *param)
{
    while (true) {
        LEDCRbits.LED3 ^= 1;

        vTaskDelay(71);
    }
}

void
task5(void *param)
{
    while (true) {
        LEDCRbits.LED4 ^= 1;

        vTaskDelay(82);
    }
}
