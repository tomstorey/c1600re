#ifndef C1600R_H
#define C1600R_H

/* Frequencies that are used to configure the CPU, generate baud rates
 * etc */
#define FCY_XTAL 4000000        /* Frequency of XTAL that feeds the PLL */
#define FCY_33MHZ 33000000      /* Desired PLL output frequency at 33MHz */
#define FCY_25MHZ 25000000      /* Desired PLL output frequency at 25MHz */
#define FCY_CLK2 8064000        /* Frequency of oscillator connected to CLK2 */

/* MODULE_BASE is where the MBAR register will be configured to locate the
 * DPRAM and internal peripheral registers. This value forms the basis for all
 * other CPU peripheral register addresses in this header file. */
#define MODULE_BASE 0x0FF00000

/* PERIPHERAL_BASE is where BR3/OR3 are configured to place the peripheral
 * memory range. */
#define PERIPHERAL_BASE 0x0D000000

/* This value is used as the initial frame pointer value, and is used as a
 * terminal value for the stack relocation code */
#define FRAME_TERM 0xDEADBEEF

/* #define __DEBUG__ */

/* Base addresses for various peripheral configuration registers */
#define DPRBASE MODULE_BASE
#define REGB (DPRBASE + 0x1000)
#define SCC1BASE (DPRBASE + 0xC00)
#define MISCBASE (DPRBASE + 0xCB0)
#define SCC2BASE (DPRBASE + 0xD00)
#define SPIBASE (DPRBASE + 0xD80)
#define TIMERBASE (DPRBASE + 0xDB0)
#define SCC3BASE (DPRBASE + 0xE00)
#define IDMA1BASE (DPRBASE + 0xE70)
#define SMC1BASE (DPRBASE + 0xE80)
#define SCC4BASE (DPRBASE + 0xF00)
#define IDMA2BASE (DPRBASE + 0xF70)
#define SMC2BASE (DPRBASE + 0xF80)

#ifndef __ASSEMBLER__

#include <stdint.h>

/******************************************************************************
 *                      Cisco Router Specific Registers
 *
 * The following registers are external to the QUICC and specific to the Cisco
 * router itself.
 *****************************************************************************/

#define SYSOPT (*(volatile uint8_t *)(PERIPHERAL_BASE + 0x80000))
typedef union {
    struct {
        uint8_t HWREV3:1;
        uint8_t HWREV2:1;
        uint8_t HWREV1:1;
        uint8_t HWREV0:1;
        uint8_t SPEED:1;
        uint8_t :3;
    };
    struct {
        uint8_t HWREV:4;
        uint8_t :4;
    };
    struct {
        uint8_t u8;
    };
} __SYSOPTbits_t;
#define SYSOPTbits (*(volatile __SYSOPTbits_t *)(PERIPHERAL_BASE + 0x80000))


#define LEDCR (*(volatile uint8_t *)(PERIPHERAL_BASE + 0x80001))
typedef union {
    struct {
        uint8_t OK:1;
        uint8_t LED1:1;
        uint8_t LED2:1;
        uint8_t LED3:1;
        uint8_t LED4:1;
        uint8_t :1;
        uint8_t REAROK:1;
        uint8_t :1;
    };
    struct {
        uint8_t u8;
    };
} __LEDCRbits_t;
#define LEDCRbits (*(volatile __LEDCRbits_t *)(PERIPHERAL_BASE + 0x80001))


#define INTCON (*(volatile uint8_t *)(PERIPHERAL_BASE + 0x80004))
typedef union {
    struct {
        uint8_t :5;
        uint8_t ONBOARD:1;
        uint8_t :1;
        uint8_t WIC:1;
    };
    struct {
        uint8_t u8;
    };
} __INTCONbits_t;
#define INTCONbits (*(volatile __INTCONbits_t *)(PERIPHERAL_BASE + 0x80004))


#define INTSRC (*(volatile uint8_t *)(PERIPHERAL_BASE + 0x80005))
typedef union {
    struct {
        uint8_t :5;
        uint8_t ONBOARD:1;
        uint8_t :1;
        uint8_t WIC:1;
    };
    struct {
        uint8_t u8;
    };
} __INTSRCbits_t;
#define INTSRCbits (*(volatile __INTSRCbits_t *)(PERIPHERAL_BASE + 0x80005))


#define PCTL (*(volatile uint8_t *)(PERIPHERAL_BASE + 0x8000F))
typedef union {
    struct {
        uint8_t :7;
        uint8_t RST:1;
    };
    struct {
        uint8_t u8;
    };
} __PCTLbits_t;
#define PCTLbits (*(volatile __PCTLbits_t *)(PERIPHERAL_BASE + 0x8000F))


/* This register is a work in progress */
#define SPCR (*(volatile uint8_t *)(PERIPHERAL_BASE + 0x30000))
typedef union {
    struct {
        uint8_t VPPSEL1:1;
        uint8_t VPPSEL0:1;
        uint8_t :2;
        uint8_t EN:1;
        uint8_t PWR:1;
        uint8_t :2;
    };
    struct {
        uint8_t VPPSEL:2;
        uint8_t :6;
    };
    struct {
        uint8_t u8;
    };
} __SPCRbits_t;
#define SPCRbits (*(volatile __SPCRbits_t *)(PERIPHERAL_BASE + 0x30000))


/* This register is a work in progress */
#define SSTR (*(volatile uint8_t *)(PERIPHERAL_BASE + 0x30001))
typedef union {
    struct {
        uint8_t CD1:1;
        uint8_t CD0:1;
        uint8_t :5;
        uint8_t READY:1;
    };
    struct {
        uint8_t CD:2;
        uint8_t :6;
    };
    struct {
        uint8_t u8;
    };
} __SSTRbits_t;
#define SSTRbits (*(volatile __SSTRbits_t *)(PERIPHERAL_BASE + 0x30001))


/* This register is a work in progress */
#define SSCR (*(volatile uint8_t *)(PERIPHERAL_BASE + 0x30002))
typedef union {
    struct {
        uint8_t CD:1;
        uint8_t :7;
    };
    struct {
        uint8_t u8;
    };
} __SSCRbits_t;
#define SSCRbits (*(volatile __SSCRbits_t *)(PERIPHERAL_BASE + 0x30002))


/* This register is a work in progress */
#define SACR (*(volatile uint8_t *)(PERIPHERAL_BASE + 0x30003))
typedef union {
    struct {
        uint8_t :1;
        uint8_t ADDEN:1;
        uint8_t :3;
        uint8_t WAIT2:1;
        uint8_t WAIT1:1;
        uint8_t WAIT0:1;
    };
    struct {
        uint8_t :5;
        uint8_t WAIT:3;
    };
    struct {
        uint8_t u8;
    };
} __SACRbits_t;
#define SACRbits (*(volatile __SACRbits_t *)(PERIPHERAL_BASE + 0x30003))

/******************************************************************************
 *                            QUICC Parameter RAM
 *****************************************************************************/

typedef union {
    struct {
        uint8_t :3;
        uint8_t MOT:1;
        uint8_t FC3:1;
        uint8_t FC2:1;
        uint8_t FC1:1;
        uint8_t FC0:1;
    };
    struct {
        uint8_t :4;
        uint8_t FC:4;
    };
    struct {
        uint8_t u8;
    };
} __RFCRbits_t;

typedef union {
    struct {
        uint8_t :3;
        uint8_t MOT:1;
        uint8_t FC3:1;
        uint8_t FC2:1;
        uint8_t FC1:1;
        uint8_t FC0:1;
    };
    struct {
        uint8_t :4;
        uint8_t FC:4;
    };
    struct {
        uint8_t u8;
    };
} __TFCRbits_t;

typedef struct {
    union {
        struct {
            uint16_t E:1;
            uint16_t :1;
            uint16_t W:1;
            uint16_t I:1;
            uint16_t L:1;
            uint16_t :1;
            uint16_t CM:1;
            uint16_t :7;
            uint16_t OV:1;
            uint16_t ME:1;
        };
        struct {
            uint16_t u16;
        };
    } flags;
    uint16_t LEN;
    uint8_t *DST;
} __SPIRxBufferDescriptor_t;

typedef struct {
    union {
        struct {
            uint16_t R:1;
            uint16_t :1;
            uint16_t W:1;
            uint16_t I:1;
            uint16_t L:1;
            uint16_t :1;
            uint16_t CM:1;
            uint16_t :7;
            uint16_t UN:1;
            uint16_t ME:1;
        };
        struct {
            uint16_t u16;
        };
    } flags;
    uint16_t LEN;
    uint8_t *SRC;
} __SPITxBufferDescriptor_t;

typedef struct {
    union {
        struct {
            uint16_t V:1;
            uint16_t :1;
            uint16_t W:1;
            uint16_t I:1;
            uint16_t L:1;
            uint16_t :1;
            uint16_t CM:1;
            uint16_t :6;
            uint16_t SE:1;
            uint16_t DE:1;
            uint16_t DA:1;
            uint16_t :16;
        };
        struct {
            uint16_t u16;
        };
    } flags;
    uint32_t LEN;
    uint8_t *SRC;
    uint8_t *DST;
} __IDMABufferDescriptor_t;

typedef struct {
    union {
        struct {
            uint16_t E:1;
            uint16_t :1;
            uint16_t W:1;
            uint16_t I:1;
            uint16_t :2;
            uint16_t CM:1;
            uint16_t ID:1;
            uint16_t :2;
            uint16_t BR:1;
            uint16_t FR:1;
            uint16_t PR:1;
            uint16_t :1;
            uint16_t OV:1;
            uint16_t CD:1;
        };
        struct {
            uint16_t u16;
        };
    } flags;
    uint16_t LEN;
    uint8_t *DST;
} __SMCRxBufferDescriptor_t;

typedef struct {
    union {
        struct {
            uint16_t R:1;
            uint16_t :1;
            uint16_t W:1;
            uint16_t I:1;
            uint16_t :2;
            uint16_t CM:1;
            uint16_t P:1;
            uint16_t :8;
        };
        struct {
            uint16_t u16;
        };
    } flags;
    uint16_t LEN;
    uint8_t *SRC;
} __SMCTxBufferDescriptor_t;

typedef struct {
    union {
        struct {
            uint16_t E:1;
            uint16_t :1;
            uint16_t W:1;
            uint16_t I:1;
            uint16_t C:1;
            uint16_t A:1;
            uint16_t CM:1;
            uint16_t ID:1;
            uint16_t AM:1;
            uint16_t :1;
            uint16_t BR:1;
            uint16_t FR:1;
            uint16_t PR:1;
            uint16_t :1;
            uint16_t OV:1;
            uint16_t CD:1;
        };
        struct {
            uint16_t u16;
        };
    } flags;
    uint16_t LEN;
    uint8_t *DST;
} __SCCUARTRxBufferDescriptor_t;

typedef struct {
    union {
        struct {
            uint16_t R:1;
            uint16_t :1;
            uint16_t W:1;
            uint16_t I:1;
            uint16_t CR:1;
            uint16_t A:1;
            uint16_t CM:1;
            uint16_t P:1;
            uint16_t NS:1;
            uint16_t :6;
            uint16_t CT:1;
        };
        struct {
            uint16_t u16;
        };
    } flags;
    uint16_t LEN;
    uint8_t *SRC;
} __SCCUARTTxBufferDescriptor_t;


/* SCC1 */
#define SCC1RBASE (*(volatile uint16_t *)(SCC1BASE))
#define SCC1TBASE (*(volatile uint16_t *)(SCC1BASE + 0x2))
#define SCC1RFCR (*(volatile uint8_t *)(SCC1BASE + 0x4))
#define SCC1RFCRbits (*(volatile __RFCRbits_t *)(SCC1BASE + 0x4))
#define SCC1TFCR (*(volatile uint8_t *)(SCC1BASE + 0x5))
#define SCC1TFCRbits (*(volatile __TFCRbits_t *)(SCC1BASE + 0x5))
#define SCC1MRBLR (*(volatile uint16_t *)(SCC1BASE + 0x6))

/* SCC1 UART protocol specific registers */
#define SCC1MAX_IDL (*(volatile uint16_t *)(SCC1BASE + 0x38))
#define SCC1BRKCR (*(volatile uint16_t *)(SCC1BASE + 0x3C))
#define SCC1PAREC (*(volatile uint16_t *)(SCC1BASE + 0x3E))
#define SCC1FRMEC (*(volatile uint16_t *)(SCC1BASE + 0x40))
#define SCC1NOSEC (*(volatile uint16_t *)(SCC1BASE + 0x42))
#define SCC1BRKEC (*(volatile uint16_t *)(SCC1BASE + 0x44))
#define SCC1BRKLN (*(volatile uint16_t *)(SCC1BASE + 0x46))
#define SCC1UADDR1 (*(volatile uint16_t *)(SCC1BASE + 0x48))
#define SCC1UADDR2 (*(volatile uint16_t *)(SCC1BASE + 0x4A))
#define SCC1TOSEQ (*(volatile uint16_t *)(SCC1BASE + 0x4E))
#define SCC1CHARACTER1 (*(volatile uint16_t *)(SCC1BASE + 0x50))
#define SCC1CHARACTER2 (*(volatile uint16_t *)(SCC1BASE + 0x52))
#define SCC1CHARACTER3 (*(volatile uint16_t *)(SCC1BASE + 0x54))
#define SCC1CHARACTER4 (*(volatile uint16_t *)(SCC1BASE + 0x56))
#define SCC1CHARACTER5 (*(volatile uint16_t *)(SCC1BASE + 0x58))
#define SCC1CHARACTER6 (*(volatile uint16_t *)(SCC1BASE + 0x5A))
#define SCC1CHARACTER7 (*(volatile uint16_t *)(SCC1BASE + 0x5C))
#define SCC1CHARACTER8 (*(volatile uint16_t *)(SCC1BASE + 0x5E))
#define SCC1RCCM (*(volatile uint16_t *)(SCC1BASE + 0x60))
#define SCC1RCCR (*(volatile uint16_t *)(SCC1BASE + 0x62))
#define SCC1RLBC (*(volatile uint16_t *)(SCC1BASE + 0x64))


/* TODO: MISCBASE */


/* SCC2 */
#define SCC2RBASE (*(volatile uint16_t *)(SCC2BASE))
#define SCC2TBASE (*(volatile uint16_t *)(SCC2BASE + 0x2))
#define SCC2RFCR (*(volatile uint8_t *)(SCC2BASE + 0x4))
#define SCC2RFCRbits (*(volatile __RFCRbits_t *)(SCC2BASE + 0x4))
#define SCC2TFCR (*(volatile uint8_t *)(SCC2BASE + 0x5))
#define SCC2TFCRbits (*(volatile __TFCRbits_t *)(SCC2BASE + 0x5))
#define SCC2MRBLR (*(volatile uint16_t *)(SCC2BASE + 0x6))

/* SCC2 UART protocol specific registers */
#define SCC2MAX_IDL (*(volatile uint16_t *)(SCC2BASE + 0x38))
#define SCC2BRKCR (*(volatile uint16_t *)(SCC2BASE + 0x3C))
#define SCC2PAREC (*(volatile uint16_t *)(SCC2BASE + 0x3E))
#define SCC2FRMEC (*(volatile uint16_t *)(SCC2BASE + 0x40))
#define SCC2NOSEC (*(volatile uint16_t *)(SCC2BASE + 0x42))
#define SCC2BRKEC (*(volatile uint16_t *)(SCC2BASE + 0x44))
#define SCC2BRKLN (*(volatile uint16_t *)(SCC2BASE + 0x46))
#define SCC2UADDR1 (*(volatile uint16_t *)(SCC2BASE + 0x48))
#define SCC2UADDR2 (*(volatile uint16_t *)(SCC2BASE + 0x4A))
#define SCC2TOSEQ (*(volatile uint16_t *)(SCC2BASE + 0x4E))
#define SCC2CHARACTER1 (*(volatile uint16_t *)(SCC2BASE + 0x50))
#define SCC2CHARACTER2 (*(volatile uint16_t *)(SCC2BASE + 0x52))
#define SCC2CHARACTER3 (*(volatile uint16_t *)(SCC2BASE + 0x54))
#define SCC2CHARACTER4 (*(volatile uint16_t *)(SCC2BASE + 0x56))
#define SCC2CHARACTER5 (*(volatile uint16_t *)(SCC2BASE + 0x58))
#define SCC2CHARACTER6 (*(volatile uint16_t *)(SCC2BASE + 0x5A))
#define SCC2CHARACTER7 (*(volatile uint16_t *)(SCC2BASE + 0x5C))
#define SCC2CHARACTER8 (*(volatile uint16_t *)(SCC2BASE + 0x5E))
#define SCC2RCCM (*(volatile uint16_t *)(SCC2BASE + 0x60))
#define SCC2RCCR (*(volatile uint16_t *)(SCC2BASE + 0x62))
#define SCC2RLBC (*(volatile uint16_t *)(SCC2BASE + 0x64))


/* SPI */
#define SPIRBASE (*(volatile uint16_t *)(SPIBASE))
#define SPITBASE (*(volatile uint16_t *)(SPIBASE + 0x2))
#define SPIRFCR (*(volatile uint8_t *)(SPIBASE + 0x4))
#define SPIRFCRbits (*(volatile __RFCRbits_t *)(SPIBASE + 0x4))
#define SPITFCR (*(volatile uint8_t *)(SPIBASE + 0x5))
#define SPITFCRbits (*(volatile __TFCRbits_t *)(SPIBASE + 0x5))
#define SPIMRBLR (*(volatile uint16_t *)(SPIBASE + 0x6))


/* TODO: TIMERBASE */


/* SCC3 */
#define SCC3RBASE (*(volatile uint16_t *)(SCC3BASE))
#define SCC3TBASE (*(volatile uint16_t *)(SCC3BASE + 0x2))
#define SCC3RFCR (*(volatile uint8_t *)(SCC3BASE + 0x4))
#define SCC3RFCRbits (*(volatile __RFCRbits_t *)(SCC3BASE + 0x4))
#define SCC3TFCR (*(volatile uint8_t *)(SCC3BASE + 0x5))
#define SCC3TFCRbits (*(volatile __TFCRbits_t *)(SCC3BASE + 0x5))
#define SCC3MRBLR (*(volatile uint16_t *)(SCC3BASE + 0x6))

/* SCC3 UART protocol specific registers */
#define SCC3MAX_IDL (*(volatile uint16_t *)(SCC3BASE + 0x38))
#define SCC3BRKCR (*(volatile uint16_t *)(SCC3BASE + 0x3C))
#define SCC3PAREC (*(volatile uint16_t *)(SCC3BASE + 0x3E))
#define SCC3FRMEC (*(volatile uint16_t *)(SCC3BASE + 0x40))
#define SCC3NOSEC (*(volatile uint16_t *)(SCC3BASE + 0x42))
#define SCC3BRKEC (*(volatile uint16_t *)(SCC3BASE + 0x44))
#define SCC3BRKLN (*(volatile uint16_t *)(SCC3BASE + 0x46))
#define SCC3UADDR1 (*(volatile uint16_t *)(SCC3BASE + 0x48))
#define SCC3UADDR2 (*(volatile uint16_t *)(SCC3BASE + 0x4A))
#define SCC3TOSEQ (*(volatile uint16_t *)(SCC3BASE + 0x4E))
#define SCC3CHARACTER1 (*(volatile uint16_t *)(SCC3BASE + 0x50))
#define SCC3CHARACTER2 (*(volatile uint16_t *)(SCC3BASE + 0x52))
#define SCC3CHARACTER3 (*(volatile uint16_t *)(SCC3BASE + 0x54))
#define SCC3CHARACTER4 (*(volatile uint16_t *)(SCC3BASE + 0x56))
#define SCC3CHARACTER5 (*(volatile uint16_t *)(SCC3BASE + 0x58))
#define SCC3CHARACTER6 (*(volatile uint16_t *)(SCC3BASE + 0x5A))
#define SCC3CHARACTER7 (*(volatile uint16_t *)(SCC3BASE + 0x5C))
#define SCC3CHARACTER8 (*(volatile uint16_t *)(SCC3BASE + 0x5E))
#define SCC3RCCM (*(volatile uint16_t *)(SCC3BASE + 0x60))
#define SCC3RCCR (*(volatile uint16_t *)(SCC3BASE + 0x62))
#define SCC3RLBC (*(volatile uint16_t *)(SCC3BASE + 0x64))


/* IDMA1 */
#define IDMA1IBASE (*(volatile uint16_t *)(IDMA1BASE))
#define IDMA1IBPTR (*(volatile uint16_t *)(IDMA1BASE + 0x2))


/* SMC1 */
#define SMC1RBASE (*(volatile uint16_t *)(SMC1BASE))
#define SMC1TBASE (*(volatile uint16_t *)(SMC1BASE + 0x2))
#define SMC1RFCR (*(volatile uint8_t *)(SMC1BASE + 0x4))
#define SMC1RFCRbits (*(volatile __RFCRbits_t *)(SMC1BASE + 0x4))
#define SMC1TFCR (*(volatile uint8_t *)(SMC1BASE + 0x5))
#define SMC1TFCRbits (*(volatile __TFCRbits_t *)(SMC1BASE + 0x5))
#define SMC1MRBLR (*(volatile uint16_t *)(SMC1BASE + 0x6))
#define SMC1MAX_IDL (*(volatile uint16_t *)(SMC1BASE + 0x28))
#define SMC1BRKLN (*(volatile uint16_t *)(SMC1BASE + 0x2C))
#define SMC1BRKEC (*(volatile uint16_t *)(SMC1BASE + 0x2E))
#define SMC1BRKCR (*(volatile uint16_t *)(SMC1BASE + 0x30))


/* SCC4 */
#define SCC4RBASE (*(volatile uint16_t *)(SCC4BASE))
#define SCC4TBASE (*(volatile uint16_t *)(SCC4BASE + 0x2))
#define SCC4RFCR (*(volatile uint8_t *)(SCC4BASE + 0x4))
#define SCC4RFCRbits (*(volatile __RFCRbits_t *)(SCC4BASE + 0x4))
#define SCC4TFCR (*(volatile uint8_t *)(SCC4BASE + 0x5))
#define SCC4TFCRbits (*(volatile __TFCRbits_t *)(SCC4BASE + 0x5))
#define SCC4MRBLR (*(volatile uint16_t *)(SCC4BASE + 0x6))

/* SCC1 UART protocol specific registers */
#define SCC4MAX_IDL (*(volatile uint16_t *)(SCC4BASE + 0x38))
#define SCC4BRKCR (*(volatile uint16_t *)(SCC4BASE + 0x3C))
#define SCC4PAREC (*(volatile uint16_t *)(SCC4BASE + 0x3E))
#define SCC4FRMEC (*(volatile uint16_t *)(SCC4BASE + 0x40))
#define SCC4NOSEC (*(volatile uint16_t *)(SCC4BASE + 0x42))
#define SCC4BRKEC (*(volatile uint16_t *)(SCC4BASE + 0x44))
#define SCC4BRKLN (*(volatile uint16_t *)(SCC4BASE + 0x46))
#define SCC4UADDR1 (*(volatile uint16_t *)(SCC4BASE + 0x48))
#define SCC4UADDR2 (*(volatile uint16_t *)(SCC4BASE + 0x4A))
#define SCC4TOSEQ (*(volatile uint16_t *)(SCC4BASE + 0x4E))
#define SCC4CHARACTER1 (*(volatile uint16_t *)(SCC4BASE + 0x50))
#define SCC4CHARACTER2 (*(volatile uint16_t *)(SCC4BASE + 0x52))
#define SCC4CHARACTER3 (*(volatile uint16_t *)(SCC4BASE + 0x54))
#define SCC4CHARACTER4 (*(volatile uint16_t *)(SCC4BASE + 0x56))
#define SCC4CHARACTER5 (*(volatile uint16_t *)(SCC4BASE + 0x58))
#define SCC4CHARACTER6 (*(volatile uint16_t *)(SCC4BASE + 0x5A))
#define SCC4CHARACTER7 (*(volatile uint16_t *)(SCC4BASE + 0x5C))
#define SCC4CHARACTER8 (*(volatile uint16_t *)(SCC4BASE + 0x5E))
#define SCC4RCCM (*(volatile uint16_t *)(SCC4BASE + 0x60))
#define SCC4RCCR (*(volatile uint16_t *)(SCC4BASE + 0x62))
#define SCC4RLBC (*(volatile uint16_t *)(SCC4BASE + 0x64))


/* IDMA2 */
#define IDMA2IBASE (*(volatile uint16_t *)(IDMA2BASE))
#define IDMA2IBPTR (*(volatile uint16_t *)(IDMA2BASE + 0x2))


/* SMC2 */
#define SMC2RBASE (*(volatile uint16_t *)(SMC2BASE))
#define SMC2TBASE (*(volatile uint16_t *)(SMC2BASE + 0x2))
#define SMC2RFCR (*(volatile uint8_t *)(SMC2BASE + 0x4))
#define SMC2RFCRbits (*(volatile __RFCRbits_t *)(SMC2BASE + 0x4))
#define SMC2TFCR (*(volatile uint8_t *)(SMC2BASE + 0x5))
#define SMC2TFCRbits (*(volatile __TFCRbits_t *)(SMC2BASE + 0x5))
#define SMC2MRBLR (*(volatile uint16_t *)(SMC2BASE + 0x6))
#define SMC2MAX_IDL (*(volatile uint16_t *)(SMC2BASE + 0x28))
#define SMC2BRKLN (*(volatile uint16_t *)(SMC2BASE + 0x2C))
#define SMC2BRKEC (*(volatile uint16_t *)(SMC2BASE + 0x2E))
#define SMC2BRKCR (*(volatile uint16_t *)(SMC2BASE + 0x30))


/******************************************************************************
 *                               SIM Registers
 *****************************************************************************/
#define MCR (*(volatile uint32_t *)(REGB + 0))
typedef union {
    struct {
        uint32_t BR040ID2:1;
        uint32_t BR040ID1:1;
        uint32_t BR040ID0:1;
        uint32_t :12;
        uint32_t BSTM:1;
        uint32_t ASTM:1;
        uint32_t FRZ1:1;
        uint32_t FRZ0:1;
        uint32_t BCLROID2:1;
        uint32_t BCLROID1:1;
        uint32_t BCLROID0:1;
        uint32_t SHEN1:1;
        uint32_t SHEN0:1;
        uint32_t SUPV:1;
        uint32_t BCLRISM2:1;
        uint32_t BCLRISM1:1;
        uint32_t BCLRISM0:1;
        uint32_t IARB3:1;
        uint32_t IARB2:1;
        uint32_t IARB1:1;
        uint32_t IARB0:1;
    };
    struct {
        uint32_t :25;
        uint32_t BCLRIIDM2:1;
        uint32_t BCLRIIDM1:1;
        uint32_t BCLRIIDM0:1;
        uint32_t :4;
    };
    struct {
        uint32_t BR040ID:3;
        uint32_t :14;
        uint32_t FRZ:2;
        uint32_t BCLROID:3;
        uint32_t SHEN:2;
        uint32_t :1;
        uint32_t BCLRISM:3;
        uint32_t IARB:4;
    };
    struct {
        uint32_t :25;
        uint32_t BCLRIID:3;
        uint32_t :4;
    };
    struct {
        uint32_t u32;
    };
} __MCRbits_t;
#define MCRbits (*(volatile __MCRbits_t *)(REGB + 0))


#define AVR (*(volatile uint8_t *)(REGB + 0x8))


#define RSR (*(volatile uint8_t *)(REGB + 0x9))
typedef union {
    struct {
        uint8_t EXT:1;
        uint8_t POW:1;
        uint8_t SW:1;
        uint8_t DBF:1;
        uint8_t :1;
        uint8_t LOC:1;
        uint8_t SRST:1;
        uint8_t SRSTP:1;
    };
    struct {
        uint8_t u8;
    };
} __RSRbits_t;
#define RSRbits (*(volatile __RSRbits_t *)(REGB + 0x9))


#define CLKOCR (*(volatile uint8_t *)(REGB + 0xC))
typedef union {
    struct {
        uint8_t CLKOWP:1;
        uint8_t :3;
        uint8_t COM2:2;
        uint8_t COM1:2;
    };
    struct {
        uint8_t u8;
    };
} __CLKOCRbits_t;
#define CLKOCRbits (*(volatile __CLKCORbits_t *)(REGB + 0xC))


#define PLLCR (*(volatile uint16_t *)(REGB + 0x10))
typedef union {
    struct {
        uint16_t PLLEN:1;
        uint16_t PLLWP:1;
        uint16_t PREEN:1;
        uint16_t STSIM:1;
        uint16_t MF11:1;
        uint16_t MF10:1;
        uint16_t MF9:1;
        uint16_t MF8:1;
        uint16_t MF7:1;
        uint16_t MF6:1;
        uint16_t MF5:1;
        uint16_t MF4:1;
        uint16_t MF3:1;
        uint16_t MF2:1;
        uint16_t MF1:1;
        uint16_t MF0:1;
    };
    struct {
        uint16_t :4;
        uint16_t MF:12;
    };
    struct {
        uint16_t u16;
    };
} __PLLCRbits_t;
#define PLLCRbits (*(volatile __PLLCRbits_t *)(REGB + 0x10))


#define CDVCR (*(volatile uint16_t *)(REGB + 0x14))
typedef union {
    struct {
        uint16_t CDVWP:1;
        uint16_t DFSY1:1;
        uint16_t DFSY0:1;
        uint16_t DFTM1:1;
        uint16_t DFTM0:1;
        uint16_t INTEN2:1;
        uint16_t INTEN1:1;
        uint16_t INTEN0:1;
        uint16_t RRQEN:1;
        uint16_t DFNL2:1;
        uint16_t DFNL1:1;
        uint16_t DFNL0:1;
        uint16_t DFNH2:1;
        uint16_t DFNH1:1;
        uint16_t DFNH0:1;
        uint16_t CSRC:1;
    };
    struct {
        uint16_t :1;
        uint16_t DFSY:2;
        uint16_t DFTM:2;
        uint16_t INTEN:3;
        uint16_t :1;
        uint16_t DFNL:3;
        uint16_t DFNH:3;
        uint16_t :1;
    };
    struct {
        uint16_t u16;
    };
} __CDVCRbits_t;
#define CDVCRbits (*(volatile __CDVCRbits_t *)(REGB + 0x14))


#define PEPAR (*(volatile uint16_t *)(REGB + 0x16))
typedef union {
    struct {
        uint16_t :1;
        uint16_t SINTOUT2:1;
        uint16_t SINTOUT1:1;
        uint16_t SINTOUT0:1;
        uint16_t :1;
        uint16_t CF1MODE1:1;
        uint16_t CF1MODE0:1;
        uint16_t IPIPE1_RAS1DD:1;
        uint16_t ADDR_WE:1;
        uint16_t OE_AMUX:1;
        uint16_t PWW:1;
        uint16_t CAS23_IACK36:1;
        uint16_t :1;
        uint16_t CAS01_IACK12:1;
        uint16_t CS7_IACK7:1;
        uint16_t AVEC_IACK5:1;
    };
    struct {
        uint16_t :1;
        uint16_t SINTOUT:3;
        uint16_t :1;
        uint16_t CF1MODE:2;
        uint16_t :9;
    };
    struct {
        uint16_t u16;
    };
} __PEPARbits_t;
#define PEPARbits (*(volatile __PEPARRbits_t *)(REGB + 0x16))


#define SYPCR (*(volatile uint8_t *)(REGB + 0x22))
typedef union {
    struct {
        uint8_t SWE:1;
        uint8_t SWRI:1;
        uint8_t SWT1:1;
        uint8_t SWT0:1;
        uint8_t DBFE:1;
        uint8_t BME:1;
        uint8_t BMT1:1;
        uint8_t BMT0:1;
    };
    struct {
        uint8_t :2;
        uint8_t SWT:2;
        uint8_t :2;
        uint8_t BMT:2;
    };
    struct {
        uint8_t u8;
    };
} __SYPCRbits_t;
#define SYPCRbits (*(volatile __SYPCRbits_t *)(REGB + 0x22))


#define SWIV (*(volatile uint8_t *)(REGB + 0x23))


#define PICR (*(volatile uint16_t *)(REGB + 0x26))
typedef union {
    struct {
        uint16_t :5;
        uint16_t PIRQL2:1;
        uint16_t PIRQL1:1;
        uint16_t PIRQL0:1;
        uint16_t PIV7:1;
        uint16_t PIV6:1;
        uint16_t PIV5:1;
        uint16_t PIV4:1;
        uint16_t PIV3:1;
        uint16_t PIV2:1;
        uint16_t PIV1:1;
        uint16_t PIV0:1;
    };
    struct {
        uint16_t :5;
        uint16_t PIRQL:3;
        uint16_t PIV:8;
    };
    struct {
        uint16_t u16;
    };
} __PICRbits_t;
#define PICRbits (*(volatile __PICRbits_t *)(REGB + 0x26))

#define PITR (*(volatile uint16_t *)(REGB + 0x2A))
typedef union {
    struct {
        uint16_t :6;
        uint16_t SWP:1;
        uint16_t PTP:1;
        uint16_t CTR7:1;
        uint16_t CTR6:1;
        uint16_t CTR5:1;
        uint16_t CTR4:1;
        uint16_t CTR3:1;
        uint16_t CTR2:1;
        uint16_t CTR1:1;
        uint16_t CTR0:1;
    };
    struct {
        uint16_t :8;
        uint16_t CTR:8;
    };
    struct {
        uint16_t u16;
    };
} __PITRbits_t;
#define PITRbits (*(volatile __PITRbits_t *)(REGB + 0x2A))


#define SWSR (*(volatile uint8_t *)(REGB + 0x2F))


#define BKAR (*(volatile uint32_t *)(REGB + 0x30))


#define BKCR (*(volatile uint32_t *)(REGB + 0x34))
typedef union {
    struct {
        uint32_t :12;
        uint32_t BAS:1;
        uint32_t BUSS:1;
        uint32_t RW1:1;
        uint32_t RW0:1;
        uint32_t SIZM:1;
        uint32_t SIZ1:1;
        uint32_t SIZ0:1;
        uint32_t NEG:1;
        uint32_t MA1:1;
        uint32_t MA0:1;
        uint32_t AS8:1;
        uint32_t AS7:1;
        uint32_t AS6:1;
        uint32_t AS5:1;
        uint32_t AS4:1;
        uint32_t AS3:1;
        uint32_t AS2:1;
        uint32_t AS1:1;
        uint32_t AS0:1;
        uint32_t V:1;
    };
    struct {
        uint32_t :14;
        uint32_t RW:2;
        uint32_t :1;
        uint32_t SIZ:2;
        uint32_t :1;
        uint32_t MA:2;
        uint32_t AS:9;
        uint32_t :1;
    };
    struct {
        uint32_t u32;
    };
} __BKCRbits_t;
#define BKCRbits (*(volatile __BKCRbits_t *)(REGB + 0x34))


#define GMR (*(volatile uint32_t *)(REGB + 0x40))
typedef union {
    struct {
        uint32_t RCNT7:1;
        uint32_t RCNT6:1;
        uint32_t RCNT5:1;
        uint32_t RCNT4:1;
        uint32_t RCNT3:1;
        uint32_t RCNT2:1;
        uint32_t RCNT1:1;
        uint32_t RCNT0:1;
        uint32_t RFEN:1;
        uint32_t RCYC1:1;
        uint32_t RCYC0:1;
        uint32_t PGS2:1;
        uint32_t PGS1:1;
        uint32_t PGS0:1;
        uint32_t DPS1:1;
        uint32_t DPS0:1;
        uint32_t WBT40:1;
        uint32_t WBTQ:1;
        uint32_t SYNC:1;
        uint32_t EMWS:1;
        uint32_t OPAR:1;
        uint32_t PBEE:1;
        uint32_t TSS40:1;
        uint32_t NCS:1;
        uint32_t DWQ:1;
        uint32_t W40:1;
        uint32_t GAMX:1;
        uint32_t :5;
    };
    struct {
        uint32_t RCNT:8;
        uint32_t :1;
        uint32_t RCYC:2;
        uint32_t PGS:3;
        uint32_t DPS:2;
        uint32_t :16;
    };
    struct {
        uint32_t u32;
    };
} __GMRbits_t;
#define GMRbits (*(volatile __GMRbits_t *)(REGB + 0x40))


#define MSTAT (*(volatile uint16_t *)(REGB + 0x44))
typedef union {
    struct {
        uint16_t :7;
        uint16_t WPER:1;
        uint16_t PER7:1;
        uint16_t PER6:1;
        uint16_t PER5:1;
        uint16_t PER4:1;
        uint16_t PER3:1;
        uint16_t PER2:1;
        uint16_t PER1:1;
        uint16_t PER0:1;
    };
    struct {
        uint16_t :8;
        uint16_t PER:8;
    };
    struct {
        uint16_t u16;
    };
} __MSTATbits_t;
#define MSTATbits (*(volatile __MSTATbits_t *)(REGB + 0x44))


#define BR0 (*(volatile uint32_t *)(REGB + 0x50))
#define BR1 (*(volatile uint32_t *)(REGB + 0x60))
#define BR2 (*(volatile uint32_t *)(REGB + 0x70))
#define BR3 (*(volatile uint32_t *)(REGB + 0x80))
#define BR4 (*(volatile uint32_t *)(REGB + 0x90))
#define BR5 (*(volatile uint32_t *)(REGB + 0xA0))
#define BR6 (*(volatile uint32_t *)(REGB + 0xB0))
#define BR7 (*(volatile uint32_t *)(REGB + 0xC0))
typedef union {
    struct {
        uint32_t BA31:1;
        uint32_t BA30:1;
        uint32_t BA29:1;
        uint32_t BA28:1;
        uint32_t BA27:1;
        uint32_t BA26:1;
        uint32_t BA25:1;
        uint32_t BA24:1;
        uint32_t BA23:1;
        uint32_t BA22:1;
        uint32_t BA21:1;
        uint32_t BA20:1;
        uint32_t BA19:1;
        uint32_t BA18:1;
        uint32_t BA17:1;
        uint32_t BA16:1;
        uint32_t BA15:1;
        uint32_t BA14:1;
        uint32_t BA13:1;
        uint32_t BA12:1;
        uint32_t BA11:1;
        uint32_t FC3:1;
        uint32_t FC2:1;
        uint32_t FC1:1;
        uint32_t FC0:1;
        uint32_t TRLXQ:1;
        uint32_t BACK40:1;
        uint32_t CSNT40:1;
        uint32_t CSNTQ:1;
        uint32_t PAREN:1;
        uint32_t WP:1;
        uint32_t V:1;
    };
    struct {
        uint32_t BA:21;
        uint32_t FC:4;
        uint32_t :7;
    };
    struct {
        uint32_t u32;
    };
} __BRbits_t;
#define BR0bits (*(volatile __BRbits_t *)(REGB + 0x50))
#define BR1bits (*(volatile __BRbits_t *)(REGB + 0x60))
#define BR2bits (*(volatile __BRbits_t *)(REGB + 0x70))
#define BR3bits (*(volatile __BRbits_t *)(REGB + 0x80))
#define BR4bits (*(volatile __BRbits_t *)(REGB + 0x90))
#define BR5bits (*(volatile __BRbits_t *)(REGB + 0xA0))
#define BR6bits (*(volatile __BRbits_t *)(REGB + 0xB0))
#define BR7bits (*(volatile __BRbits_t *)(REGB + 0xC0))


#define OR0 (*(volatile uint32_t *)(REGB + 0x54))
#define OR1 (*(volatile uint32_t *)(REGB + 0x64))
#define OR2 (*(volatile uint32_t *)(REGB + 0x74))
#define OR3 (*(volatile uint32_t *)(REGB + 0x84))
#define OR4 (*(volatile uint32_t *)(REGB + 0x94))
#define OR5 (*(volatile uint32_t *)(REGB + 0xA4))
#define OR6 (*(volatile uint32_t *)(REGB + 0xB4))
#define OR7 (*(volatile uint32_t *)(REGB + 0xC4))
typedef union {
    struct {
        uint32_t TCYC3:1;
        uint32_t TCYC2:1;
        uint32_t TCYC1:1;
        uint32_t TCYC0:1;
        uint32_t AM27:1;
        uint32_t AM26:1;
        uint32_t AM25:1;
        uint32_t AM24:1;
        uint32_t AM23:1;
        uint32_t AM22:1;
        uint32_t AM21:1;
        uint32_t AM20:1;
        uint32_t AM19:1;
        uint32_t AM18:1;
        uint32_t AM17:1;
        uint32_t AM16:1;
        uint32_t AM15:1;
        uint32_t AM14:1;
        uint32_t AM13:1;
        uint32_t AM12:1;
        uint32_t AM11:1;
        uint32_t FCM3:1;
        uint32_t FCM2:1;
        uint32_t FCM1:1;
        uint32_t FCM0:1;
        uint32_t BCYC1:1;
        uint32_t BCYC0:1;
        uint32_t :1;
        uint32_t PGME:1;
        uint32_t SPS1:1;
        uint32_t SPS0:1;
        uint32_t DSSEL:1;
    };
    struct {
        uint32_t TCYC:4;
        uint32_t AM:17;
        uint32_t FCM:4;
        uint32_t BCYC:2;
        uint32_t :2;
        uint32_t SPS:2;
        uint32_t :1;
    };
    struct {
        uint32_t u32;
    };
} __ORbits_t;
#define OR0bits (*(volatile __ORbits_t *)(REGB + 0x54))
#define OR1bits (*(volatile __ORbits_t *)(REGB + 0x64))
#define OR2bits (*(volatile __ORbits_t *)(REGB + 0x74))
#define OR3bits (*(volatile __ORbits_t *)(REGB + 0x84))
#define OR4bits (*(volatile __ORbits_t *)(REGB + 0x94))
#define OR5bits (*(volatile __ORbits_t *)(REGB + 0xA4))
#define OR6bits (*(volatile __ORbits_t *)(REGB + 0xB4))
#define OR7bits (*(volatile __ORbits_t *)(REGB + 0xC4))


#define ICCR (*(volatile uint16_t *)(REGB + 0x500))
typedef union {
    struct {
        uint16_t STP:1;
        uint16_t FRZ1:1;
        uint16_t FRZ0:1;
        uint16_t ARBP1:1;
        uint16_t ARBP0:1;
        uint16_t ISM2:1;
        uint16_t ISM1:1;
        uint16_t ISM0:1;
        uint16_t :1;
        uint16_t IAID2:1;
        uint16_t IAID1:1;
        uint16_t IAID0:1;
        uint16_t :4;
    };
    struct {
        uint16_t :1;
        uint16_t FRZ:2;
        uint16_t ARBP:2;
        uint16_t ISM:3;
        uint16_t :1;
        uint16_t IAID:3;
        uint16_t :4;
    };
    struct {
        uint16_t u16;
    };
} __ICCRbits_t;
#define ICCRbits (*(volatile __ICCRbits_t *)(REGB + 0x500))


#define CMR1 (*(volatile uint16_t *)(REGB + 0x504))
#define CMR2 (*(volatile uint16_t *)(REGB + 0x526))
typedef union {
    struct {
        uint16_t ECO:1;
        uint16_t SRM:1;
        uint16_t SD:1;
        uint16_t RCI:1;
        uint16_t REQG1:1;
        uint16_t REQG0:1;
        uint16_t SAPI:1;
        uint16_t DAPI:1;
        uint16_t SSIZE1:1;
        uint16_t SSIZE0:1;
        uint16_t DSIZE1:1;
        uint16_t DSIZE0:1;
        uint16_t BT1:1;
        uint16_t BT0:1;
        uint16_t RST:1;
        uint16_t STR:1;
    };
    struct {
        uint16_t :4;
        uint16_t REQG:2;
        uint16_t :2;
        uint16_t SSIZE:2;
        uint16_t DSIZE:2;
        uint16_t BT:2;
        uint16_t :2;
    };
    struct {
        uint16_t u16;
    };
} __CMRbits_t;
#define CMR1bits (*(volatile __CMRbits_t *)(REGB + 0x504))
#define CMR2bits (*(volatile __CMRbits_t *)(REGB + 0x526))


#define SAPR1 (*(volatile uint32_t *)(REGB + 0x508))
#define SAPR2 (*(volatile uint32_t *)(REGB + 0x528))


#define DAPR1 (*(volatile uint32_t *)(REGB + 0x50C))
#define DAPR2 (*(volatile uint32_t *)(REGB + 0x52C))


#define BCR1 (*(volatile uint32_t *)(REGB + 0x510))
#define BCR2 (*(volatile uint32_t *)(REGB + 0x530))


#define FCR1 (*(volatile uint8_t *)(REGB + 0x514))
#define FCR2 (*(volatile uint8_t *)(REGB + 0x534))
typedef union {
    struct {
        uint8_t DFC3:1;
        uint8_t DFC2:1;
        uint8_t DFC1:1;
        uint8_t DFC0:1;
        uint8_t SFC3:1;
        uint8_t SFC2:1;
        uint8_t SFC1:1;
        uint8_t SFC0:1;
    };
    struct {
        uint8_t DFC:4;
        uint8_t SFC:4;
    };
    struct {
        uint8_t u8;
    };
} __FCRbits_t;
#define FCR1bits (*(volatile __FCRbits_t *)(REGB + 0x514))
#define FCR2bits (*(volatile __FCRbits_t *)(REGB + 0x534))


#define CMAR1 (*(volatile uint8_t *)(REGB + 0x516))
#define CMAR2 (*(volatile uint8_t *)(REGB + 0x536))
typedef union {
    struct {
        uint8_t :2;
        uint8_t AD:1;
        uint8_t BRKP:1;
        uint8_t OB:1;
        uint8_t BES:1;
        uint8_t BED:1;
        uint8_t DONE:1;
    };
    struct {
        uint8_t u8;
    };
} __CMARbits_t;
#define CMAR1bits (*(volatile __CMARbits_t *)(REGB + 0x516))
#define CMAR2bits (*(volatile __CMARbits_t *)(REGB + 0x536))


#define CSR1 (*(volatile uint8_t *)(REGB + 0x518))
#define CSR2 (*(volatile uint8_t *)(REGB + 0x538))
typedef union {
    struct {
        uint8_t :2;
        uint8_t AD:1;
        uint8_t BRKP:1;
        uint8_t OB:1;
        uint8_t BES:1;
        uint8_t BED:1;
        uint8_t DONE:1;
    };
    struct {
        uint8_t u8;
    };
} __CSRbits_t;
#define CSR1bits (*(volatile __CSRbits_t *)(REGB + 0x518))
#define CSR2bits (*(volatile __CSRbits_t *)(REGB + 0x538))


#define SDSR (*(volatile uint8_t *)(REGB + 0x51C))
typedef union {
    struct {
        uint8_t :5;
        uint8_t RINT:1;
        uint8_t SBER:1;
        uint8_t SBKP:1;
    };
    struct {
        uint8_t u8;
    };
} __SDSRbits_t;
#define SDSRbits (*(volatile __SDSRbits_t *)(REGB + 0x51C))

#define SDCR (*(volatile uint16_t *)(REGB + 0x51E))
typedef union {
    struct {
        uint16_t :1;
        uint16_t FRZ1:1;
        uint16_t FRZ0:1;
        uint16_t :2;
        uint16_t SISM2:1;
        uint16_t SISM1:1;
        uint16_t SISM0:1;
        uint16_t :1;
        uint16_t SAID2:1;
        uint16_t SAID1:1;
        uint16_t SAID0:1;
        uint16_t :2;
        uint16_t INTE:1;
        uint16_t INTB:1;
    };
    struct {
        uint16_t :1;
        uint16_t FRZ:2;
        uint16_t :2;
        uint16_t SISM:3;
        uint16_t :1;
        uint16_t SAID:3;
        uint16_t :4;
    };
    struct {
        uint16_t u16;
    };
} __SDCRbits_t;
#define SDCRbits (*(volatile __SDCRbits_t *)(REGB + 0x51E))

#define SDAR (*(volatile uint32_t *)(REGB + 0x520))


#define CICR (*(volatile uint32_t *)(REGB + 0x540))
typedef union {
    struct {
        uint32_t :8;
        uint32_t SCdP1:1;
        uint32_t SCdP0:1;
        uint32_t SCcP1:1;
        uint32_t SCcP0:1;
        uint32_t SCbP1:1;
        uint32_t SCbP0:1;
        uint32_t SCaP1:1;
        uint32_t SCaP0:1;
        uint32_t IRL2:1;
        uint32_t IRL1:1;
        uint32_t IRL0:1;
        uint32_t HP4:1;
        uint32_t HP3:1;
        uint32_t HP2:1;
        uint32_t HP1:1;
        uint32_t HP0:1;
        uint32_t VBA2:1;
        uint32_t VBA1:1;
        uint32_t VBA0:1;
        uint32_t :4;
        uint32_t SPS:1;
    };
    struct {
        uint32_t :8;
        uint32_t SCdP:2;
        uint32_t SCcP:2;
        uint32_t SCbP:2;
        uint32_t SCaP:2;
        uint32_t IRL:3;
        uint32_t HP:5;
        uint32_t VBA:3;
        uint32_t :5;
    };
    struct {
        uint32_t u32;
    };
} __CICRbits_t;
#define CICRbits (*(volatile __CICRbits_t *)(REGB + 0x540))

#define CIPR (*(volatile uint32_t *)(REGB + 0x544))
typedef union {
    struct {
        uint32_t PC0:1;
        uint32_t SCC1:1;
        uint32_t SCC2:1;
        uint32_t SCC3:1;
        uint32_t SCC4:1;
        uint32_t PC1:1;
        uint32_t TIMER1:1;
        uint32_t PC2:1;
        uint32_t PC3:1;
        uint32_t SDMA:1;
        uint32_t IDMA1:1;
        uint32_t IDMA2:1;
        uint32_t :1;
        uint32_t TIMER2:1;
        uint32_t RTT:1;
        uint32_t :1;
        uint32_t PC4:1;
        uint32_t PC5:1;
        uint32_t :1;
        uint32_t TIMER3:1;
        uint32_t PC6:1;
        uint32_t PC7:1;
        uint32_t PC8:1;
        uint32_t :1;
        uint32_t TIMER4:1;
        uint32_t PC9:1;
        uint32_t SPI:1;
        uint32_t SMC1:1;
        uint32_t SMC2:1;
        uint32_t PC10:1;
        uint32_t PC11:1;
        uint32_t :1;
    };
    struct {
        uint32_t :28;
        uint32_t PIP:1;
        uint32_t :3;
    };
    struct {
        uint32_t u32;
    };
} __CIPRbits_t;
#define CIPRbits (*(volatile __CIPRbits_t *)(REGB + 0x544))

#define CIMR (*(volatile uint32_t *)(REGB + 0x548))
typedef union {
    struct {
        uint32_t PC0:1;
        uint32_t SCC1:1;
        uint32_t SCC2:1;
        uint32_t SCC3:1;
        uint32_t SCC4:1;
        uint32_t PC1:1;
        uint32_t TIMER1:1;
        uint32_t PC2:1;
        uint32_t PC3:1;
        uint32_t SDMA:1;
        uint32_t IDMA1:1;
        uint32_t IDMA2:1;
        uint32_t :1;
        uint32_t TIMER2:1;
        uint32_t RTT:1;
        uint32_t :1;
        uint32_t PC4:1;
        uint32_t PC5:1;
        uint32_t :1;
        uint32_t TIMER3:1;
        uint32_t PC6:1;
        uint32_t PC7:1;
        uint32_t PC8:1;
        uint32_t :1;
        uint32_t TIMER4:1;
        uint32_t PC9:1;
        uint32_t SPI:1;
        uint32_t SMC1:1;
        uint32_t SMC2:1;
        uint32_t PC10:1;
        uint32_t PC11:1;
        uint32_t :1;
    };
    struct {
        uint32_t :28;
        uint32_t PIP:1;
        uint32_t :3;
    };
    struct {
        uint32_t u32;
    };
} __CIMRbits_t;
#define CIMRbits (*(volatile __CIMRbits_t *)(REGB + 0x548))

#define CISR (*(volatile uint32_t *)(REGB + 0x54C))
typedef union {
    struct {
        uint32_t PC0:1;
        uint32_t SCC1:1;
        uint32_t SCC2:1;
        uint32_t SCC3:1;
        uint32_t SCC4:1;
        uint32_t PC1:1;
        uint32_t TIMER1:1;
        uint32_t PC2:1;
        uint32_t PC3:1;
        uint32_t SDMA:1;
        uint32_t IDMA1:1;
        uint32_t IDMA2:1;
        uint32_t :1;
        uint32_t TIMER2:1;
        uint32_t RTT:1;
        uint32_t :1;
        uint32_t PC4:1;
        uint32_t PC5:1;
        uint32_t :1;
        uint32_t TIMER3:1;
        uint32_t PC6:1;
        uint32_t PC7:1;
        uint32_t PC8:1;
        uint32_t :1;
        uint32_t TIMER4:1;
        uint32_t PC9:1;
        uint32_t SPI:1;
        uint32_t SMC1:1;
        uint32_t SMC2:1;
        uint32_t PC10:1;
        uint32_t PC11:1;
        uint32_t :1;
    };
    struct {
        uint32_t :28;
        uint32_t PIP:1;
        uint32_t :3;
    };
    struct {
        uint32_t u32;
    };
} __CISRbits_t;
#define CISRbits (*(volatile __CISRbits_t *)(REGB + 0x54C))


#define PADIR (*(volatile uint16_t *)(REGB + 0x550))
typedef union {
    struct {
        uint16_t DR15:1;
        uint16_t DR14:1;
        uint16_t DR13:1;
        uint16_t DR12:1;
        uint16_t DR11:1;
        uint16_t DR10:1;
        uint16_t DR9:1;
        uint16_t DR8:1;
        uint16_t DR7:1;
        uint16_t DR6:1;
        uint16_t DR5:1;
        uint16_t DR4:1;
        uint16_t DR3:1;
        uint16_t DR2:1;
        uint16_t DR1:1;
        uint16_t DR0:1;
    };
    struct {
        uint16_t u16;
    };
} __PADIRbits_t;
#define PADIRbits (*(volatile __PADIRbits_t *)(REGB + 0x550))

#define PAPAR (*(volatile uint16_t *)(REGB + 0x552))
typedef union {
    struct {
        uint16_t DD15:1;
        uint16_t DD14:1;
        uint16_t DD13:1;
        uint16_t DD12:1;
        uint16_t DD11:1;
        uint16_t DD10:1;
        uint16_t DD9:1;
        uint16_t DD8:1;
        uint16_t DD7:1;
        uint16_t DD6:1;
        uint16_t DD5:1;
        uint16_t DD4:1;
        uint16_t DD3:1;
        uint16_t DD2:1;
        uint16_t DD1:1;
        uint16_t DD0:1;
    };
    struct {
        uint16_t u16;
    };
} __PAPARbits_t;
#define PAPARbits (*(volatile __PAPARbits_t *)(REGB + 0x552))

#define PAODR (*(volatile uint16_t *)(REGB + 0x554))
typedef union {
    struct {
        uint16_t :8;
        uint16_t OD7:1;
        uint16_t OD6:1;
        uint16_t OD5:1;
        uint16_t OD4:1;
        uint16_t OD3:1;
        uint16_t :1;
        uint16_t OD1:1;
        uint16_t :1;
    };
    struct {
        uint16_t u16;
    };
} __PAODRbits_t;
#define PAODRbits (*(volatile __PAODRbits_t *)(REGB + 0x554))

#define PADAT (*(volatile uint16_t *)(REGB + 0x556))
typedef union {
    struct {
        uint16_t D15:1;
        uint16_t D14:1;
        uint16_t D13:1;
        uint16_t D12:1;
        uint16_t D11:1;
        uint16_t D10:1;
        uint16_t D9:1;
        uint16_t D8:1;
        uint16_t D7:1;
        uint16_t D6:1;
        uint16_t D5:1;
        uint16_t D4:1;
        uint16_t D3:1;
        uint16_t D2:1;
        uint16_t D1:1;
        uint16_t D0:1;
    };
    struct {
        uint16_t u16;
    };
} __PADATbits_t;
#define PADATbits (*(volatile __PADATbits_t *)(REGB + 0x556))


#define PCDIR (*(volatile uint16_t *)(REGB + 0x560))
typedef union {
    struct {
        uint16_t :4;
        uint16_t DR11:1;
        uint16_t DR10:1;
        uint16_t DR9:1;
        uint16_t DR8:1;
        uint16_t DR7:1;
        uint16_t DR6:1;
        uint16_t DR5:1;
        uint16_t DR4:1;
        uint16_t DR3:1;
        uint16_t DR2:1;
        uint16_t DR1:1;
        uint16_t DR0:1;
    };
    struct {
        uint16_t u16;
    };
} __PCDIRbits_t;
#define PCDIRbits (*(volatile __PCDIRbits_t *)(REGB + 0x560))

#define PCPAR (*(volatile uint16_t *)(REGB + 0x562))
typedef union {
    struct {
        uint16_t :4;
        uint16_t DD11:1;
        uint16_t DD10:1;
        uint16_t DD9:1;
        uint16_t DD8:1;
        uint16_t DD7:1;
        uint16_t DD6:1;
        uint16_t DD5:1;
        uint16_t DD4:1;
        uint16_t DD3:1;
        uint16_t DD2:1;
        uint16_t DD1:1;
        uint16_t DD0:1;
    };
    struct {
        uint16_t u16;
    };
} __PCPARbits_t;
#define PCPARbits (*(volatile __PCPARbits_t *)(REGB + 0x562))

#define PCSO (*(volatile uint16_t *)(REGB + 0x564))
typedef union {
    struct {
        uint16_t :4;
        uint16_t CD4:1;
        uint16_t CTS4:1;
        uint16_t CD3:1;
        uint16_t CTS3:1;
        uint16_t CD2:1;
        uint16_t CTS2:1;
        uint16_t CD1:1;
        uint16_t CTS1:1;
        uint16_t :4;
    };
    struct {
        uint16_t u16;
    };
} __PCSObits_t;
#define PCSObits (*(volatile __PCSObits_t *)(REGB + 0x564))

#define PCDAT (*(volatile uint16_t *)(REGB + 0x566))
typedef union {
    struct {
        uint16_t :4;
        uint16_t D11:1;
        uint16_t D10:1;
        uint16_t D9:1;
        uint16_t D8:1;
        uint16_t D7:1;
        uint16_t D6:1;
        uint16_t D5:1;
        uint16_t D4:1;
        uint16_t D3:1;
        uint16_t D2:1;
        uint16_t D1:1;
        uint16_t D0:1;
    };
    struct {
        uint16_t u16;
    };
} __PCDATbits_t;
#define PCDATbits (*(volatile __PCDATbits_t *)(REGB + 0x566))

#define PCINT (*(volatile uint16_t *)(REGB + 0x568))
typedef union {
    struct {
        uint16_t :4;
        uint16_t EDM11:1;
        uint16_t EDM10:1;
        uint16_t EDM9:1;
        uint16_t EDM8:1;
        uint16_t EDM7:1;
        uint16_t EDM6:1;
        uint16_t EDM5:1;
        uint16_t EDM4:1;
        uint16_t EDM3:1;
        uint16_t EDM2:1;
        uint16_t EDM1:1;
        uint16_t EDM0:1;
    };
    struct {
        uint16_t u16;
    };
} __PCINTbits_t;
#define PCINTbits (*(volatile __PCINTbits_t *)(REGB + 0x568))


#define TGCR (*(volatile uint16_t *)(REGB + 0x580))
typedef union {
    struct {
        uint16_t CAS4:1;
        uint16_t FRZ4:1;
        uint16_t STP4:1;
        uint16_t RST4:1;
        uint16_t GM2:1;
        uint16_t FRZ3:1;
        uint16_t STP3:1;
        uint16_t RST3:1;
        uint16_t CAS2:1;
        uint16_t FRZ2:1;
        uint16_t STP2:1;
        uint16_t RST2:1;
        uint16_t GM1:1;
        uint16_t FRZ1:1;
        uint16_t STP1:1;
        uint16_t RST1:1;
    };
    struct {
        uint16_t u16;
    };
} __TGCRbits_t;
#define TGCRbits (*(volatile __TGCRbits_t *)(REGB + 0x580))


#define TMR1 (*(volatile uint16_t *)(REGB + 0x590))
#define TMR2 (*(volatile uint16_t *)(REGB + 0x592))
#define TMR3 (*(volatile uint16_t *)(REGB + 0x5A0))
#define TMR4 (*(volatile uint16_t *)(REGB + 0x5A2))
typedef union {
    struct {
        uint16_t PS7:1;
        uint16_t PS6:1;
        uint16_t PS5:1;
        uint16_t PS4:1;
        uint16_t PS3:1;
        uint16_t PS2:1;
        uint16_t PS1:1;
        uint16_t PS0:1;
        uint16_t CE1:1;
        uint16_t CE0:1;
        uint16_t OM:1;
        uint16_t ORI:1;
        uint16_t FRR:1;
        uint16_t ICLK1:1;
        uint16_t ICLK0:1;
        uint16_t GE:1;
    };
    struct {
        uint16_t PS:8;
        uint16_t CE:2;
        uint16_t :3;
        uint16_t ICLK:2;
        uint16_t :1;
    };
    struct {
        uint16_t u16;
    };
} __TMRbits_t;
#define TMR1bits (*(volatile __TMRbits_t *)(REGB + 0x590))
#define TMR2bits (*(volatile __TMRbits_t *)(REGB + 0x592))
#define TMR3bits (*(volatile __TMRbits_t *)(REGB + 0x5A0))
#define TMR4bits (*(volatile __TMRbits_t *)(REGB + 0x5A2))


#define TRR1 (*(volatile uint16_t *)(REGB + 0x594))
#define TRR2 (*(volatile uint16_t *)(REGB + 0x596))
#define TRR3 (*(volatile uint16_t *)(REGB + 0x5A4))
#define TRR4 (*(volatile uint16_t *)(REGB + 0x5A6))


#define TCR1 (*(volatile uint16_t *)(REGB + 0x598))
#define TCR2 (*(volatile uint16_t *)(REGB + 0x59A))
#define TCR3 (*(volatile uint16_t *)(REGB + 0x5A8))
#define TCR4 (*(volatile uint16_t *)(REGB + 0x5AA))


#define TCN1 (*(volatile uint16_t *)(REGB + 0x59C))
#define TCN2 (*(volatile uint16_t *)(REGB + 0x59E))
#define TCN3 (*(volatile uint16_t *)(REGB + 0x5AC))
#define TCN4 (*(volatile uint16_t *)(REGB + 0x5AE))


#define TER1 (*(volatile uint16_t *)(REGB + 0x5B0))
#define TER2 (*(volatile uint16_t *)(REGB + 0x5B2))
#define TER3 (*(volatile uint16_t *)(REGB + 0x5B4))
#define TER4 (*(volatile uint16_t *)(REGB + 0x5B6))
typedef union {
    struct {
        uint16_t :14;
        uint16_t REF:1;
        uint16_t CAP:1;
    };
    struct {
        uint16_t u16;
    };
} __TERbits_t;
#define TER1bits (*(volatile __TERbits_t *)(REGB + 0x5B0))
#define TER2bits (*(volatile __TERbits_t *)(REGB + 0x5B2))
#define TER3bits (*(volatile __TERbits_t *)(REGB + 0x5B4))
#define TER4bits (*(volatile __TERbits_t *)(REGB + 0x5B6))


#define CR (*(volatile uint16_t *)(REGB + 0x5C0))
typedef union {
    struct {
        uint16_t RST:1;
        uint16_t :3;
        uint16_t OPCODE3:1;
        uint16_t OPCODE2:1;
        uint16_t OPCODE1:1;
        uint16_t OPCODE0:1;
        uint16_t CHNUM3:1;
        uint16_t CHNUM2:1;
        uint16_t CHNUM1:1;
        uint16_t CHNUM0:1;
        uint16_t :3;
        uint16_t FLG:1;
    };
    struct {
        uint16_t :4;
        uint16_t OPCODE:4;
        uint16_t CHNUM:4;
        uint16_t :4;
    };
    struct {
        uint16_t u16;
    };
} __CRbits_t;
#define CRbits (*(volatile __CRbits_t *)(REGB + 0x5C0))


#define BRGC1 (*(volatile uint32_t *)(REGB + 0x5F0))
#define BRGC2 (*(volatile uint32_t *)(REGB + 0x5F4))
#define BRGC3 (*(volatile uint32_t *)(REGB + 0x5F8))
#define BRGC4 (*(volatile uint32_t *)(REGB + 0x5FC))
typedef union {
    struct {
        uint32_t :14;
        uint32_t RST:1;
        uint32_t EN:1;
        uint32_t EXTC1:1;
        uint32_t EXTC0:1;
        uint32_t ATB:1;
        uint32_t CD11:1;
        uint32_t CD10:1;
        uint32_t CD9:1;
        uint32_t CD8:1;
        uint32_t CD7:1;
        uint32_t CD6:1;
        uint32_t CD5:1;
        uint32_t CD4:1;
        uint32_t CD3:1;
        uint32_t CD2:1;
        uint32_t CD1:1;
        uint32_t CD0:1;
        uint32_t DIV16:1;
    };
    struct {
        uint32_t :16;
        uint32_t EXTC:2;
        uint32_t :1;
        uint32_t CD:12;
        uint32_t :1;
    };
    struct {
        uint32_t u32;
    };
} __BRGCbits_t;
#define BRGC1bits (*(volatile __BRGCbits_t *)(REGB + 0x5F0))
#define BRGC2bits (*(volatile __BRGCbits_t *)(REGB + 0x5F4))
#define BRGC3bits (*(volatile __BRGCbits_t *)(REGB + 0x5F8))
#define BRGC4bits (*(volatile __BRGCbits_t *)(REGB + 0x5FC))


#define GSMR1L (*(volatile uint32_t *)(REGB + 0x600))
#define GSMR2L (*(volatile uint32_t *)(REGB + 0x620))
#define GSMR3L (*(volatile uint32_t *)(REGB + 0x640))
#define GSMR4L (*(volatile uint32_t *)(REGB + 0x660))
typedef union {
    struct {
        uint32_t :1;
        uint32_t EDGE1:1;
        uint32_t EDGE0:1;
        uint32_t TCI:1;
        uint32_t TSNC1:1;
        uint32_t TSNC0:1;
        uint32_t RINV:1;
        uint32_t TINV:1;
        uint32_t TPL2:1;
        uint32_t TPL1:1;
        uint32_t TPL0:1;
        uint32_t TPP1:1;
        uint32_t TPP0:1;
        uint32_t TEND:1;
        uint32_t TDCR1:1;
        uint32_t TDCR0:1;
        uint32_t RDCR1:1;
        uint32_t RDCR0:1;
        uint32_t RENC2:1;
        uint32_t RENC1:1;
        uint32_t RENC0:1;
        uint32_t TENC2:1;
        uint32_t TENC1:1;
        uint32_t TENC0:1;
        uint32_t DIAG1:1;
        uint32_t DIAG0:1;
        uint32_t ENR:1;
        uint32_t ENT:1;
        uint32_t MODE3:1;
        uint32_t MODE2:1;
        uint32_t MODE1:1;
        uint32_t MODE0:1;
    };
    struct {
        uint32_t :1;
        uint32_t EDGE:2;
        uint32_t :1;
        uint32_t TSNC:2;
        uint32_t :2;
        uint32_t TPL:3;
        uint32_t TPP:2;
        uint32_t :1;
        uint32_t TDCR:2;
        uint32_t RDCR:2;
        uint32_t RENC:3;
        uint32_t TENC:3;
        uint32_t DIAG:2;
        uint32_t :2;
        uint32_t MODE:4;
    };
    struct {
        uint32_t u32;
    };
} __GSMRLbits_t;
#define GSMR1Lbits (*(volatile __GSMRLbits_t *)(REGB + 0x600))
#define GSMR2Lbits (*(volatile __GSMRLbits_t *)(REGB + 0x620))
#define GSMR3Lbits (*(volatile __GSMRLbits_t *)(REGB + 0x640))
#define GSMR4Lbits (*(volatile __GSMRLbits_t *)(REGB + 0x660))


#define GSMR1H (*(volatile uint32_t *)(REGB + 0x604))
#define GSMR2H (*(volatile uint32_t *)(REGB + 0x624))
#define GSMR3H (*(volatile uint32_t *)(REGB + 0x644))
#define GSMR4H (*(volatile uint32_t *)(REGB + 0x664))
typedef union {
    struct {
        uint32_t :15;
        uint32_t GDE:1;
        uint32_t TCRC1:1;
        uint32_t TCRC0:1;
        uint32_t REVD:1;
        uint32_t TRX:1;
        uint32_t TTX:1;
        uint32_t CDP:1;
        uint32_t CTSP:1;
        uint32_t CDS:1;
        uint32_t CTSS:1;
        uint32_t TFL:1;
        uint32_t RFW:1;
        uint32_t TXSY:1;
        uint32_t SYNL1:1;
        uint32_t SYNL0:1;
        uint32_t RTSM:1;
        uint32_t RSYN:1;
    };
    struct {
        uint32_t :16;
        uint32_t TCRC:2;
        uint32_t :10;
        uint32_t SYNL:2;
        uint32_t :2;
    };
    struct {
        uint32_t u32;
    };
} __GSMRHbits_t;
#define GSMR1Hbits (*(volatile __GSMRHbits_t *)(REGB + 0x604))
#define GSMR2Hbits (*(volatile __GSMRHbits_t *)(REGB + 0x624))
#define GSMR3Hbits (*(volatile __GSMRHbits_t *)(REGB + 0x644))
#define GSMR4Hbits (*(volatile __GSMRHbits_t *)(REGB + 0x664))


/* TODO Protocol specific structs */
#define PSMR1 (*(volatile uint16_t *)(REGB + 0x608))
#define PSMR2 (*(volatile uint16_t *)(REGB + 0x628))
#define PSMR3 (*(volatile uint16_t *)(REGB + 0x648))
#define PSMR4 (*(volatile uint16_t *)(REGB + 0x668))
typedef union {
    struct {
        uint16_t FLC:1;
        uint16_t SL:1;
        uint16_t CL1:1;
        uint16_t CL0:1;
        uint16_t UM1:1;
        uint16_t UM0:1;
        uint16_t FRZ:1;
        uint16_t RZS:1;
        uint16_t SYN:1;
        uint16_t DRT:1;
        uint16_t :1;
        uint16_t PEN:1;
        uint16_t RPM1:1;
        uint16_t RPM0:1;
        uint16_t TPM1:1;
        uint16_t TPM0:1;
    };
    struct {
        uint16_t :2;
        uint16_t CL:2;
        uint16_t UM:2;
        uint16_t :6;
        uint16_t RPM:2;
        uint16_t TPM:2;
    };
    struct {
        uint16_t u16;
    };
} __PSMRUARTbits_t;
#define PSMR1UARTbits (*(volatile __PSMRUARTbits_t *)(REGB + 0x608))
#define PSMR2UARTbits (*(volatile __PSMRUARTbits_t *)(REGB + 0x628))
#define PSMR3UARTbits (*(volatile __PSMRUARTbits_t *)(REGB + 0x648))
#define PSMR4UARTbits (*(volatile __PSMRUARTbits_t *)(REGB + 0x668))


#define TODR1 (*(volatile uint16_t *)(REGB + 0x60C))
#define TODR2 (*(volatile uint16_t *)(REGB + 0x62C))
#define TODR3 (*(volatile uint16_t *)(REGB + 0x64C))
#define TODR4 (*(volatile uint16_t *)(REGB + 0x66C))
typedef union {
    struct {
        uint16_t TOD:1;
        uint16_t :15;
    };
    struct {
        uint16_t u16;
    };
} __TODRbits_t;
#define TODR1bits (*(volatile __TODRbits_t *)(REGB + 0x60C))
#define TODR2bits (*(volatile __TODRbits_t *)(REGB + 0x62C))
#define TODR3bits (*(volatile __TODRbits_t *)(REGB + 0x64C))
#define TODR4bits (*(volatile __TODRbits_t *)(REGB + 0x66C))


#define DSR1 (*(volatile uint16_t *)(REGB + 0x60E))
#define DSR2 (*(volatile uint16_t *)(REGB + 0x62E))
#define DSR3 (*(volatile uint16_t *)(REGB + 0x64E))
#define DSR4 (*(volatile uint16_t *)(REGB + 0x66E))
typedef union {
    struct {
        uint16_t SYN2:8;
        uint16_t SYN1:8;
    };
    struct {
        uint16_t u16;
    };
} __DSRbits_t;
#define DSR1bits (*(volatile __DSRbits_t *)(REGB + 0x60E))
#define DSR2bits (*(volatile __DSRbits_t *)(REGB + 0x62E))
#define DSR3bits (*(volatile __DSRbits_t *)(REGB + 0x64E))
#define DSR4bits (*(volatile __DSRbits_t *)(REGB + 0x66E))


/* TODO Protocol specific structs */
#define SCCE1 (*(volatile uint16_t *)(REGB + 0x610))
#define SCCE2 (*(volatile uint16_t *)(REGB + 0x630))
#define SCCE3 (*(volatile uint16_t *)(REGB + 0x650))
#define SCCE4 (*(volatile uint16_t *)(REGB + 0x670))
typedef union {
    struct {
        uint16_t :3;
        uint16_t GLR:1;
        uint16_t GLT:1;
        uint16_t :1;
        uint16_t AB:1;
        uint16_t IDL:1;
        uint16_t GRA:1;
        uint16_t BRKE:1;
        uint16_t BRKS:1;
        uint16_t :1;
        uint16_t CCR:1;
        uint16_t BSY:1;
        uint16_t TX:1;
        uint16_t RX:1;
    };
    struct {
        uint16_t u16;
    };
} __SCCEUARTbits_t;
#define SCCE1UARTbits (*(volatile __SCCEUARTbits_t *)(REGB + 0x610))
#define SCCE2UARTbits (*(volatile __SCCEUARTbits_t *)(REGB + 0x630))
#define SCCE3UARTbits (*(volatile __SCCEUARTbits_t *)(REGB + 0x650))
#define SCCE4UARTbits (*(volatile __SCCEUARTbits_t *)(REGB + 0x670))


/* TODO Protocol specific structs */
#define SCCM1 (*(volatile uint16_t *)(REGB + 0x614))
#define SCCM2 (*(volatile uint16_t *)(REGB + 0x634))
#define SCCM3 (*(volatile uint16_t *)(REGB + 0x654))
#define SCCM4 (*(volatile uint16_t *)(REGB + 0x674))
typedef union {
    struct {
        uint16_t :3;
        uint16_t GLR:1;
        uint16_t GLT:1;
        uint16_t :1;
        uint16_t AB:1;
        uint16_t IDL:1;
        uint16_t GRA:1;
        uint16_t BRKE:1;
        uint16_t BRKS:1;
        uint16_t :1;
        uint16_t CCR:1;
        uint16_t BSY:1;
        uint16_t TX:1;
        uint16_t RX:1;
    };
    struct {
        uint16_t u16;
    };
} __SCCMUARTbits_t;
#define SCCM1UARTbits (*(volatile __SCCMUARTbits_t *)(REGB + 0x614))
#define SCCM2UARTbits (*(volatile __SCCMUARTbits_t *)(REGB + 0x634))
#define SCCM3UARTbits (*(volatile __SCCMUARTbits_t *)(REGB + 0x654))
#define SCCM4UARTbits (*(volatile __SCCMUARTbits_t *)(REGB + 0x674))


#define SCCS1 (*(volatile uint8_t *)(REGB + 0x617))
#define SCCS2 (*(volatile uint8_t *)(REGB + 0x637))
#define SCCS3 (*(volatile uint8_t *)(REGB + 0x657))
#define SCCS4 (*(volatile uint8_t *)(REGB + 0x677))
typedef union {
    struct {
        uint8_t :7;
        uint8_t ID:1;
    };
    struct {
        uint8_t u8;
    };
} __SCCSbits_t;
#define SCCS1bits (*(volatile __SCCSbits_t *)(REGB + 0x617))
#define SCCS2bits (*(volatile __SCCSbits_t *)(REGB + 0x637))
#define SCCS3bits (*(volatile __SCCSbits_t *)(REGB + 0x657))
#define SCCS4bits (*(volatile __SCCSbits_t *)(REGB + 0x677))


#define SMCMR1 (*(volatile uint16_t *)(REGB + 0x682))
#define SMCMR2 (*(volatile uint16_t *)(REGB + 0x692))
typedef union {
    struct {
        uint16_t :1;
        uint16_t CLEN3:1;
        uint16_t CLEN2:1;
        uint16_t CLEN1:1;
        uint16_t CLEN0:1;
        uint16_t SL:1;
        uint16_t PEN:1;
        uint16_t PM:1;
        uint16_t :2;
        uint16_t SM1:1;
        uint16_t SM0:1;
        uint16_t DM1:1;
        uint16_t DM0:1;
        uint16_t TEN:1;
        uint16_t REN:1;
    };
    struct {
        uint16_t :1;
        uint16_t CLEN:4;
        uint16_t :5;
        uint16_t SM:2;
        uint16_t DM:2;
        uint16_t :2;
    };
    struct {
        uint16_t u16;
    };
} __SMCMRbits_t;
#define SMCMR1bits (*(volatile __SMCMRbits_t *)(REGB + 0x682))
#define SMCMR2bits (*(volatile __SMCMRbits_t *)(REGB + 0x692))


#define SMCE1 (*(volatile uint8_t *)(REGB + 0x686))
#define SMCE2 (*(volatile uint8_t *)(REGB + 0x696))
typedef union {
    struct {
        uint8_t :1;
        uint8_t BRKE:1;
        uint8_t :1;
        uint8_t BRK:1;
        uint8_t :1;
        uint8_t BSY:1;
        uint8_t TX:1;
        uint8_t RX:1;
    };
    struct {
        uint8_t u8;
    };
} __SMCEbits_t;
#define SMCE1bits (*(volatile __SMCEbits_t *)(REGB + 0x686))
#define SMCE2bits (*(volatile __SMCEbits_t *)(REGB + 0x696))


#define SMCM1 (*(volatile uint8_t *)(REGB + 0x68A))
#define SMCM2 (*(volatile uint8_t *)(REGB + 0x69A))
typedef union {
    struct {
        uint8_t :1;
        uint8_t BRKE:1;
        uint8_t :1;
        uint8_t BRK:1;
        uint8_t :1;
        uint8_t BSY:1;
        uint8_t TX:1;
        uint8_t RX:1;
    };
    struct {
        uint8_t u8;
    };
} __SMCMbits_t;
#define SMCM1bits (*(volatile __SMCMbits_t *)(REGB + 0x68A))
#define SMCM2bits (*(volatile __SMCMbits_t *)(REGB + 0x69A))


#define SPMODE (*(volatile uint16_t *)(REGB + 0x6A0))
typedef union {
    struct {
        uint16_t :1;
        uint16_t LOOP:1;
        uint16_t CI:1;
        uint16_t CP:1;
        uint16_t DIV16:1;
        uint16_t REV:1;
        uint16_t MS:1;
        uint16_t EN:1;
        uint16_t LEN3:1;
        uint16_t LEN2:1;
        uint16_t LEN1:1;
        uint16_t LEN0:1;
        uint16_t PM3:1;
        uint16_t PM2:1;
        uint16_t PM1:1;
        uint16_t PM0:1;
    };
    struct {
        uint16_t :8;
        uint16_t LEN:4;
        uint16_t PM:4;
    };
    struct {
        uint16_t u16;
    };
} __SPMODEbits_t;
#define SPMODEbits (*(volatile __SPMODEbits_t *)(REGB + 0x6A0))


#define SPIE (*(volatile uint8_t *)(REGB + 0x6A6))
typedef union {
    struct {
        uint8_t :2;
        uint8_t MME:1;
        uint8_t TXE:1;
        uint8_t :1;
        uint8_t BSY:1;
        uint8_t RXB:1;
        uint8_t TXB:1;
    };
    struct {
        uint8_t u8;
    };
} __SPIEbits_t;
#define SPIEbits (*(volatile __SPIEbits_t *)(REGB + 0x6A6))


#define SPIM (*(volatile uint8_t *)(REGB + 0x6AA))
typedef union {
    struct {
        uint8_t :2;
        uint8_t MME:1;
        uint8_t TXE:1;
        uint8_t :1;
        uint8_t BSY:1;
        uint8_t RXB:1;
        uint8_t TXB:1;
    };
    struct {
        uint8_t u8;
    };
} __SPIMbits_t;
#define SPIMbits (*(volatile __SPIMbits_t *)(REGB + 0x6AA))


#define SPCOM (*(volatile uint8_t *)(REGB + 0x6AD))
typedef union {
    struct {
        uint8_t STR:1;
        uint8_t :7;
    };
    struct {
        uint8_t u8;
    };
} __SPCOMbits_t;
#define SPCOMbits (*(volatile __SPCOMbits_t *)(REGB + 0x6AD))


#define PBDIR (*(volatile uint32_t *)(REGB + 0x6B8))
typedef union {
    struct {
        uint32_t :14;
        uint32_t DR17:1;
        uint32_t DR16:1;
        uint32_t DR15:1;
        uint32_t DR14:1;
        uint32_t DR13:1;
        uint32_t DR12:1;
        uint32_t DR11:1;
        uint32_t DR10:1;
        uint32_t DR9:1;
        uint32_t DR8:1;
        uint32_t DR7:1;
        uint32_t DR6:1;
        uint32_t DR5:1;
        uint32_t DR4:1;
        uint32_t DR3:1;
        uint32_t DR2:1;
        uint32_t DR1:1;
        uint32_t DR0:1;
    };
    struct {
        uint32_t u32;
    };
} __PBDIRbits_t;
#define PBDIRbits (*(volatile __PBDIRbits_t *)(REGB + 0x6B8))


#define PBPAR (*(volatile uint32_t *)(REGB + 0x6BC))
typedef union {
    struct {
        uint32_t :14;
        uint32_t DD17:1;
        uint32_t DD16:1;
        uint32_t DD15:1;
        uint32_t DD14:1;
        uint32_t DD13:1;
        uint32_t DD12:1;
        uint32_t DD11:1;
        uint32_t DD10:1;
        uint32_t DD9:1;
        uint32_t DD8:1;
        uint32_t DD7:1;
        uint32_t DD6:1;
        uint32_t DD5:1;
        uint32_t DD4:1;
        uint32_t DD3:1;
        uint32_t DD2:1;
        uint32_t DD1:1;
        uint32_t DD0:1;
    };
    struct {
        uint32_t u32;
    };
} __PBPARbits_t;
#define PBPARbits (*(volatile __PBPARbits_t *)(REGB + 0x6BC))


#define PBODR (*(volatile uint16_t *)(REGB + 0x6C2))
typedef union {
    struct {
        uint16_t OD15:1;
        uint16_t OD14:1;
        uint16_t OD13:1;
        uint16_t OD12:1;
        uint16_t OD11:1;
        uint16_t OD10:1;
        uint16_t OD9:1;
        uint16_t OD8:1;
        uint16_t OD7:1;
        uint16_t OD6:1;
        uint16_t OD5:1;
        uint16_t OD4:1;
        uint16_t OD3:1;
        uint16_t OD2:1;
        uint16_t OD1:1;
        uint16_t OD0:1;
    };
    struct {
        uint16_t u16;
    };
} __PBODRbits_t;
#define PBODRbits (*(volatile __PBODRbits_t *)(REGB + 0x6C2))


#define PBDAT (*(volatile uint32_t *)(REGB + 0x6C4))
typedef union {
    struct {
        uint32_t :14;
        uint32_t D17:1;
        uint32_t D16:1;
        uint32_t D15:1;
        uint32_t D14:1;
        uint32_t D13:1;
        uint32_t D12:1;
        uint32_t D11:1;
        uint32_t D10:1;
        uint32_t D9:1;
        uint32_t D8:1;
        uint32_t D7:1;
        uint32_t D6:1;
        uint32_t D5:1;
        uint32_t D4:1;
        uint32_t D3:1;
        uint32_t D2:1;
        uint32_t D1:1;
        uint32_t D0:1;
    };
    struct {
        uint32_t u32;
    };
} __PBDATbits_t;
#define PBDATbits (*(volatile __PBDATbits_t *)(REGB + 0x6C4))


#define SIMODE (*(volatile uint32_t *)(REGB + 0x6E0))
typedef union {
    struct {
        uint32_t SMC2:1;
        uint32_t SMC2CS2:1;
        uint32_t SMC2CS1:1;
        uint32_t SMC2CS0:1;
        uint32_t SDMB1:1;
        uint32_t SDMB0:1;
        uint32_t RFSDB1:1;
        uint32_t RFSDB0:1;
        uint32_t DSCB:1;
        uint32_t CRTB:1;
        uint32_t STZB:1;
        uint32_t CEB:1;
        uint32_t FEB:1;
        uint32_t GMB:1;
        uint32_t TFSDB1:1;
        uint32_t TFSDB0:1;
        uint32_t SMC1:1;
        uint32_t SMC1CS2:1;
        uint32_t SMC1CS1:1;
        uint32_t SMC1CS0:1;
        uint32_t SDMA1:1;
        uint32_t SDMA0:1;
        uint32_t RFSDA1:1;
        uint32_t RFSDA0:1;
        uint32_t DSCA:1;
        uint32_t CRTA:1;
        uint32_t STZA:1;
        uint32_t CEA:1;
        uint32_t FEA:1;
        uint32_t GMA:1;
        uint32_t TFSDA1:1;
        uint32_t TFSDA0:1;
    };
    struct {
        uint32_t :1;
        uint32_t SMC2CS:3;
        uint32_t SDMB:2;
        uint32_t RFSDB:2;
        uint32_t :6;
        uint32_t TFSDB:2;
        uint32_t :1;
        uint32_t SMC1CS:3;
        uint32_t SDMA:2;
        uint32_t RFSDA:2;
        uint32_t :6;
        uint32_t TFSDA:2;
    };
    struct {
        uint32_t u32;
    };
} __SIMODEbits_t;
#define SIMODEbits (*(volatile __SIMODEbits_t *)(REGB + 0x6E0))


#define SIGMR (*(volatile uint8_t *)(REGB + 0x6E4))
typedef union {
    struct {
        uint8_t :4;
        uint8_t ENB:1;
        uint8_t ENA:1;
        uint8_t RDM1:1;
        uint8_t RDM0:1;
    };
    struct {
        uint8_t :6;
        uint8_t RDM:2;
    };
    struct {
        uint8_t u8;
    };
} __SIGMRbits_t;
#define SIGMRbits (*(volatile __SIGMRbits_t *)(REGB + 0x6E4))


#define SISTR (*(volatile uint8_t *)(REGB + 0x6E6))
typedef union {
    struct {
        uint8_t CRORA:1;
        uint8_t CROTA:1;
        uint8_t CRORB:1;
        uint8_t CROTB:1;
        uint8_t :4;
    };
    struct {
        uint8_t u8;
    };
} __SISTRbits_t;
#define SISTRbits (*(volatile __SISTRbits_t *)(REGB + 0x6E6))


#define SICMR (*(volatile uint8_t *)(REGB + 0x6E7))
typedef union {
    struct {
        uint8_t CSRRA:1;
        uint8_t CSRTA:1;
        uint8_t CSRRB:1;
        uint8_t CSRTB:1;
        uint8_t :4;
    };
    struct {
        uint8_t u8;
    };
} __SICMRbits_t;
#define SICMRbits (*(volatile __SICMRbits_t *)(REGB + 0x6E7))


#define SICR (*(volatile uint32_t *)(REGB + 0x6EC))
typedef union {
    struct {
        uint32_t GR4:1;
        uint32_t SC4:1;
        uint32_t R4CS2:1;
        uint32_t R4CS1:1;
        uint32_t R4CS0:1;
        uint32_t T4CS2:1;
        uint32_t T4CS1:1;
        uint32_t T4CS0:1;
        uint32_t GR3:1;
        uint32_t SC3:1;
        uint32_t R3CS2:1;
        uint32_t R3CS1:1;
        uint32_t R3CS0:1;
        uint32_t T3CS2:1;
        uint32_t T3CS1:1;
        uint32_t T3CS0:1;
        uint32_t GR2:1;
        uint32_t SC2:1;
        uint32_t R2CS2:1;
        uint32_t R2CS1:1;
        uint32_t R2CS0:1;
        uint32_t T2CS2:1;
        uint32_t T2CS1:1;
        uint32_t T2CS0:1;
        uint32_t GR1:1;
        uint32_t SC1:1;
        uint32_t R1CS2:1;
        uint32_t R1CS1:1;
        uint32_t R1CS0:1;
        uint32_t T1CS2:1;
        uint32_t T1CS1:1;
        uint32_t T1CS0:1;
    };
    struct {
        uint32_t :2;
        uint32_t R4CS:3;
        uint32_t T4CS:3;
        uint32_t :2;
        uint32_t R3CS:3;
        uint32_t T3CS:3;
        uint32_t :2;
        uint32_t R2CS:3;
        uint32_t T2CS:3;
        uint32_t :2;
        uint32_t R1CS:3;
        uint32_t T1CS:3;
    };
    struct {
        uint32_t u32;
    };
} __SICRbits_t;
#define SICRbits (*(volatile __SICRbits_t *)(REGB + 0x6EC))

#else /* __ASSEMBLER__ */

#define SYSOPT (PERIPHERAL_BASE + 0x80000)
#define LEDCR (PERIPHERAL_BASE + 0x80001)
#define INTCON (PERIPHERAL_BASE + 0x80004)
#define INTSRC (PERIPHERAL_BASE + 0x80005)
#define PCTL (PERIPHERAL_BASE + 0x8000F)
#define SPCR (PERIPHERAL_BASE + 0x30000)
#define SSTR (PERIPHERAL_BASE + 0x30001)
#define SSCR (PERIPHERAL_BASE + 0x30002)
#define SACR (PERIPHERAL_BASE + 0x30003)
#define SPIRBASE (SPIBASE)
#define SPITBASE (SPIBASE + 0x2)
#define SPIRFCR (SPIBASE + 0x4)
#define SPITFCR (SPIBASE + 0x5)
#define SPIMRBLR (SPIBASE + 0x6)
#define IDMA1IBASE (IDMA1BASE)
#define IDMA1IBPTR (IDMA1BASE + 0x2)
#define SMC1RBASE (SMC1BASE)
#define SMC1TBASE (SMC1BASE + 0x2)
#define SMC1RFCR (SMC1BASE + 0x4)
#define SMC1TFCR (SMC1BASE + 0x5)
#define SMC1MRBLR (SMC1BASE + 0x6)
#define SMC1MAX_IDL (SMC1BASE + 0x28)
#define SMC1BRKLN (SMC1BASE + 0x2C)
#define SMC1BRKEC (SMC1BASE + 0x2E)
#define SMC1BRKCR (SMC1BASE + 0x30)
#define IDMA2IBASE (IDMA2BASE)
#define IDMA2IBPTR (IDMA2BASE + 0x2)
#define SMC2RBASE (SMC2BASE)
#define SMC2TBASE (SMC2BASE + 0x2)
#define SMC2RFCR (SMC2BASE + 0x4)
#define SMC2TFCR (SMC2BASE + 0x5)
#define SMC2MRBLR (SMC2BASE + 0x6)
#define SMC2MAX_IDL (SMC2BASE + 0x28)
#define SMC2BRKLN (SMC2BASE + 0x2C)
#define SMC2BRKEC (SMC2BASE + 0x2E)
#define SMC2BRKCR (SMC2BASE + 0x30)
#define MCR (REGB + 0)
#define AVR (REGB + 0x8)
#define RSR (REGB + 0x9)
#define CLKOCR (REGB + 0xC)
#define PLLCR (REGB + 0x10)
#define CDVCR (REGB + 0x14)
#define PEPAR (REGB + 0x16)
#define SYPCR (REGB + 0x22)
#define SWIV (REGB + 0x23)
#define PICR (REGB + 0x26)
#define PITR (REGB + 0x2A)
#define SWSR (REGB + 0x2F)
#define BKAR (REGB + 0x30)
#define BKCR (REGB + 0x34)
#define GMR (REGB + 0x40)
#define MSTAT (REGB + 0x44)
#define BR0 (REGB + 0x50)
#define BR1 (REGB + 0x60)
#define BR2 (REGB + 0x70)
#define BR3 (REGB + 0x80)
#define BR4 (REGB + 0x90)
#define BR5 (REGB + 0xA0)
#define BR6 (REGB + 0xB0)
#define BR7 (REGB + 0xC0)
#define OR0 (REGB + 0x54)
#define OR1 (REGB + 0x64)
#define OR2 (REGB + 0x74)
#define OR3 (REGB + 0x84)
#define OR4 (REGB + 0x94)
#define OR5 (REGB + 0xA4)
#define OR6 (REGB + 0xB4)
#define OR7 (REGB + 0xC4)
#define ICCR (REGB + 0x500)
#define CMR1 (REGB + 0x504)
#define CMR2 (REGB + 0x526)
#define SAPR1 (REGB + 0x508)
#define SAPR2 (REGB + 0x528)
#define DAPR1 (REGB + 0x50C)
#define DAPR2 (REGB + 0x52C)
#define BCR1 (REGB + 0x510)
#define BCR2 (REGB + 0x530)
#define FCR1 (REGB + 0x514)
#define FCR2 (REGB + 0x534)
#define CMAR1 (REGB + 0x516)
#define CMAR2 (REGB + 0x536)
#define CSR1 (REGB + 0x518)
#define CSR2 (REGB + 0x538)
#define SDSR (REGB + 0x51C)
#define SDCR (REGB + 0x51E)
#define SDAR (REGB + 0x520)
#define CICR (REGB + 0x540)
#define CIPR (REGB + 0x544)
#define CIMR (REGB + 0x548)
#define CISR (REGB + 0x54C)
#define PADIR (REGB + 0x550)
#define PAPAR (REGB + 0x552)
#define PAODR (REGB + 0x554)
#define PADAT (REGB + 0x556)
#define PCDIR (REGB + 0x560)
#define PCPAR (REGB + 0x562)
#define PCSO (REGB + 0x564)
#define PCDAT (REGB + 0x566)
#define PCINT (REGB + 0x568)
#define TGCR (REGB + 0x580)
#define TMR1 (REGB + 0x590)
#define TMR2 (REGB + 0x592)
#define TMR3 (REGB + 0x5A0)
#define TMR4 (REGB + 0x5A2)
#define TRR1 (REGB + 0x594)
#define TRR2 (REGB + 0x596)
#define TRR3 (REGB + 0x5A4)
#define TRR4 (REGB + 0x5A6)
#define TCR1 (REGB + 0x598)
#define TCR2 (REGB + 0x59A)
#define TCR3 (REGB + 0x5A8)
#define TCR4 (REGB + 0x5AA)
#define TCN1 (REGB + 0x59C)
#define TCN2 (REGB + 0x59E)
#define TCN3 (REGB + 0x5AC)
#define TCN4 (REGB + 0x5AE)
#define TER1 (REGB + 0x5B0)
#define TER2 (REGB + 0x5B2)
#define TER3 (REGB + 0x5B4)
#define TER4 (REGB + 0x5B6)
#define CR (REGB + 0x5C0)
#define BRGC1 (REGB + 0x5F0)
#define BRGC2 (REGB + 0x5F4)
#define BRGC3 (REGB + 0x5F8)
#define BRGC4 (REGB + 0x5FC)
#define GSMR1L (REGB + 0x600)
#define GSMR2L (REGB + 0x620)
#define GSMR3L (REGB + 0x640)
#define GSMR4L (REGB + 0x660)
#define GSMR1H (REGB + 0x604)
#define GSMR2H (REGB + 0x624)
#define GSMR3H (REGB + 0x644)
#define GSMR4H (REGB + 0x664)
#define PSMR1 (REGB + 0x608)
#define PSMR2 (REGB + 0x628)
#define PSMR3 (REGB + 0x648)
#define PSMR4 (REGB + 0x668)
#define TODR1 (REGB + 0x60C)
#define TODR2 (REGB + 0x62C)
#define TODR3 (REGB + 0x64C)
#define TODR4 (REGB + 0x66C)
#define DSR1 (REGB + 0x60E)
#define DSR2 (REGB + 0x62E)
#define DSR3 (REGB + 0x64E)
#define DSR4 (REGB + 0x66E)
#define SCCE1 (REGB + 0x610)
#define SCCE2 (REGB + 0x630)
#define SCCE3 (REGB + 0x650)
#define SCCE4 (REGB + 0x670)
#define SCCM1 (REGB + 0x614)
#define SCCM2 (REGB + 0x634)
#define SCCM3 (REGB + 0x654)
#define SCCM4 (REGB + 0x674)
#define SCCS1 (REGB + 0x617)
#define SCCS2 (REGB + 0x637)
#define SCCS3 (REGB + 0x657)
#define SCCS4 (REGB + 0x677)
#define SMCMR1 (REGB + 0x682)
#define SMCMR2 (REGB + 0x692)
#define SMCE1 (REGB + 0x686)
#define SMCE2 (REGB + 0x696)
#define SMCM1 (REGB + 0x68A)
#define SMCM2 (REGB + 0x69A)
#define SPMODE (REGB + 0x6A0)
#define SPIE (REGB + 0x6A6)
#define SPIM (REGB + 0x6AA)
#define SPCOM (REGB + 0x6AD)
#define PBDIR (REGB + 0x6B8)
#define PBPAR (REGB + 0x6BC)
#define PBODR (REGB + 0x6C2)
#define PBDAT (REGB + 0x6C4)
#define SIMODE (REGB + 0x6E0)
#define SIGMR (REGB + 0x6E4)
#define SISTR (REGB + 0x6E6)
#define SICMR (REGB + 0x6E7)
#define SICR (REGB + 0x6EC)

#endif /* __ASSEMBLER__ */

#define _SYSOPT_HWREV3_POSITION        0x00000007
#define _SYSOPT_HWREV3_MASK            0x00000001
#define _SYSOPT_HWREV3_LENGTH          0x00000001

#define _SYSOPT_HWREV2_POSITION        0x00000006
#define _SYSOPT_HWREV2_MASK            0x00000001
#define _SYSOPT_HWREV2_LENGTH          0x00000001

#define _SYSOPT_HWREV1_POSITION        0x00000005
#define _SYSOPT_HWREV1_MASK            0x00000001
#define _SYSOPT_HWREV1_LENGTH          0x00000001

#define _SYSOPT_HWREV0_POSITION        0x00000004
#define _SYSOPT_HWREV0_MASK            0x00000001
#define _SYSOPT_HWREV0_LENGTH          0x00000001

#define _SYSOPT_HWREV_POSITION         0x00000004
#define _SYSOPT_HWREV_MASK             0x0000000F
#define _SYSOPT_HWREV_LENGTH           0x00000004

#define _SYSOPT_SPEED_POSITION         0x00000003
#define _SYSOPT_SPEED_MASK             0x00000001
#define _SYSOPT_SPEED_LENGTH           0x00000001

#define _LEDCR_OK_POSITION             0x00000007
#define _LEDCR_OK_MASK                 0x00000001
#define _LEDCR_OK_LENGTH               0x00000001

#define _LEDCR_LED1_POSITION           0x00000006
#define _LEDCR_LED1_MASK               0x00000001
#define _LEDCR_LED1_LENGTH             0x00000001

#define _LEDCR_LED2_POSITION           0x00000005
#define _LEDCR_LED2_MASK               0x00000001
#define _LEDCR_LED2_LENGTH             0x00000001

#define _LEDCR_LED3_POSITION           0x00000004
#define _LEDCR_LED3_MASK               0x00000001
#define _LEDCR_LED3_LENGTH             0x00000001

#define _LEDCR_LED4_POSITION           0x00000003
#define _LEDCR_LED4_MASK               0x00000001
#define _LEDCR_LED4_LENGTH             0x00000001

#define _LEDCR_REAROK_POSITION         0x00000001
#define _LEDCR_REAROK_MASK             0x00000001
#define _LEDCR_REAROK_LENGTH           0x00000001

#define _INTCON_ONBOARD_POSITION       0x00000002
#define _INTCON_ONBOARD_MASK           0x00000001
#define _INTCON_ONBOARD_LENGTH         0x00000001

#define _INTCON_WIC_POSITION           0x00000000
#define _INTCON_WIC_MASK               0x00000001
#define _INTCON_WIC_LENGTH             0x00000001

#define _INTSRC_ONBOARD_POSITION       0x00000002
#define _INTSRC_ONBOARD_MASK           0x00000001
#define _INTSRC_ONBOARD_LENGTH         0x00000001

#define _INTSRC_WIC_POSITION           0x00000000
#define _INTSRC_WIC_MASK               0x00000001
#define _INTSRC_WIC_LENGTH             0x00000001

#define _PCTL_RST_POSITION             0x00000000
#define _PCTL_RST_MASK                 0x00000001
#define _PCTL_RST_LENGTH               0x00000001

#define _SPCR_VPPSEL1_POSITION         0x00000007
#define _SPCR_VPPSEL1_MASK             0x00000001
#define _SPCR_VPPSEL1_LENGTH           0x00000001

#define _SPCR_VPPSEL0_POSITION         0x00000006
#define _SPCR_VPPSEL0_MASK             0x00000001
#define _SPCR_VPPSEL0_LENGTH           0x00000001

#define _SPCR_VPPSEL_POSITION          0x00000006
#define _SPCR_VPPSEL_MASK              0x00000003
#define _SPCR_VPPSEL_LENGTH            0x00000002

#define _SPCR_EN_POSITION              0x00000003
#define _SPCR_EN_MASK                  0x00000001
#define _SPCR_EN_LENGTH                0x00000001

#define _SPCR_PWR_POSITION             0x00000002
#define _SPCR_PWR_MASK                 0x00000001
#define _SPCR_PWR_LENGTH               0x00000001

#define _SSTR_CD1_POSITION             0x00000007
#define _SSTR_CD1_MASK                 0x00000001
#define _SSTR_CD1_LENGTH               0x00000001

#define _SSTR_CD0_POSITION             0x00000006
#define _SSTR_CD0_MASK                 0x00000001
#define _SSTR_CD0_LENGTH               0x00000001

#define _SSTR_CD_POSITION              0x00000006
#define _SSTR_CD_MASK                  0x00000003
#define _SSTR_CD_LENGTH                0x00000002

#define _SSTR_READY_POSITION           0x00000000
#define _SSTR_READY_MASK               0x00000001
#define _SSTR_READY_LENGTH             0x00000001

#define _SSCR_CD_POSITION              0x00000007
#define _SSCR_CD_MASK                  0x00000001
#define _SSCR_CD_LENGTH                0x00000001

#define _SACR_ADDEN_POSITION           0x00000006
#define _SACR_ADDEN_MASK               0x00000001
#define _SACR_ADDEN_LENGTH             0x00000001

#define _SACR_WAIT2_POSITION           0x00000002
#define _SACR_WAIT2_MASK               0x00000001
#define _SACR_WAIT2_LENGTH             0x00000001

#define _SACR_WAIT1_POSITION           0x00000001
#define _SACR_WAIT1_MASK               0x00000001
#define _SACR_WAIT1_LENGTH             0x00000001

#define _SACR_WAIT0_POSITION           0x00000000
#define _SACR_WAIT0_MASK               0x00000001
#define _SACR_WAIT0_LENGTH             0x00000001

#define _SACR_WAIT_POSITION            0x00000000
#define _SACR_WAIT_MASK                0x00000007
#define _SACR_WAIT_LENGTH              0x00000003

#define _SPIRFCR_MOT_POSITION          0x00000004
#define _SPIRFCR_MOT_MASK              0x00000001
#define _SPIRFCR_MOT_LENGTH            0x00000001

#define _SPIRFCR_FC3_POSITION          0x00000003
#define _SPIRFCR_FC3_MASK              0x00000001
#define _SPIRFCR_FC3_LENGTH            0x00000001

#define _SPIRFCR_FC2_POSITION          0x00000002
#define _SPIRFCR_FC2_MASK              0x00000001
#define _SPIRFCR_FC2_LENGTH            0x00000001

#define _SPIRFCR_FC1_POSITION          0x00000001
#define _SPIRFCR_FC1_MASK              0x00000001
#define _SPIRFCR_FC1_LENGTH            0x00000001

#define _SPIRFCR_FC0_POSITION          0x00000000
#define _SPIRFCR_FC0_MASK              0x00000001
#define _SPIRFCR_FC0_LENGTH            0x00000001

#define _SPIRFCR_FC_POSITION           0x00000000
#define _SPIRFCR_FC_MASK               0x0000000F
#define _SPIRFCR_FC_LENGTH             0x00000004

#define _SMC1RFCR_MOT_POSITION         0x00000004
#define _SMC1RFCR_MOT_MASK             0x00000001
#define _SMC1RFCR_MOT_LENGTH           0x00000001

#define _SMC1RFCR_FC3_POSITION         0x00000003
#define _SMC1RFCR_FC3_MASK             0x00000001
#define _SMC1RFCR_FC3_LENGTH           0x00000001

#define _SMC1RFCR_FC2_POSITION         0x00000002
#define _SMC1RFCR_FC2_MASK             0x00000001
#define _SMC1RFCR_FC2_LENGTH           0x00000001

#define _SMC1RFCR_FC1_POSITION         0x00000001
#define _SMC1RFCR_FC1_MASK             0x00000001
#define _SMC1RFCR_FC1_LENGTH           0x00000001

#define _SMC1RFCR_FC0_POSITION         0x00000000
#define _SMC1RFCR_FC0_MASK             0x00000001
#define _SMC1RFCR_FC0_LENGTH           0x00000001

#define _SMC1RFCR_FC_POSITION          0x00000000
#define _SMC1RFCR_FC_MASK              0x0000000F
#define _SMC1RFCR_FC_LENGTH            0x00000004

#define _SMC2RFCR_MOT_POSITION         0x00000004
#define _SMC2RFCR_MOT_MASK             0x00000001
#define _SMC2RFCR_MOT_LENGTH           0x00000001

#define _SMC2RFCR_FC3_POSITION         0x00000003
#define _SMC2RFCR_FC3_MASK             0x00000001
#define _SMC2RFCR_FC3_LENGTH           0x00000001

#define _SMC2RFCR_FC2_POSITION         0x00000002
#define _SMC2RFCR_FC2_MASK             0x00000001
#define _SMC2RFCR_FC2_LENGTH           0x00000001

#define _SMC2RFCR_FC1_POSITION         0x00000001
#define _SMC2RFCR_FC1_MASK             0x00000001
#define _SMC2RFCR_FC1_LENGTH           0x00000001

#define _SMC2RFCR_FC0_POSITION         0x00000000
#define _SMC2RFCR_FC0_MASK             0x00000001
#define _SMC2RFCR_FC0_LENGTH           0x00000001

#define _SMC2RFCR_FC_POSITION          0x00000000
#define _SMC2RFCR_FC_MASK              0x0000000F
#define _SMC2RFCR_FC_LENGTH            0x00000004

#define _SPITFCR_MOT_POSITION          0x00000004
#define _SPITFCR_MOT_MASK              0x00000001
#define _SPITFCR_MOT_LENGTH            0x00000001

#define _SPITFCR_FC3_POSITION          0x00000003
#define _SPITFCR_FC3_MASK              0x00000001
#define _SPITFCR_FC3_LENGTH            0x00000001

#define _SPITFCR_FC2_POSITION          0x00000002
#define _SPITFCR_FC2_MASK              0x00000001
#define _SPITFCR_FC2_LENGTH            0x00000001

#define _SPITFCR_FC1_POSITION          0x00000001
#define _SPITFCR_FC1_MASK              0x00000001
#define _SPITFCR_FC1_LENGTH            0x00000001

#define _SPITFCR_FC0_POSITION          0x00000000
#define _SPITFCR_FC0_MASK              0x00000001
#define _SPITFCR_FC0_LENGTH            0x00000001

#define _SPITFCR_FC_POSITION           0x00000000
#define _SPITFCR_FC_MASK               0x0000000F
#define _SPITFCR_FC_LENGTH             0x00000004

#define _SMC1TFCR_MOT_POSITION         0x00000004
#define _SMC1TFCR_MOT_MASK             0x00000001
#define _SMC1TFCR_MOT_LENGTH           0x00000001

#define _SMC1TFCR_FC3_POSITION         0x00000003
#define _SMC1TFCR_FC3_MASK             0x00000001
#define _SMC1TFCR_FC3_LENGTH           0x00000001

#define _SMC1TFCR_FC2_POSITION         0x00000002
#define _SMC1TFCR_FC2_MASK             0x00000001
#define _SMC1TFCR_FC2_LENGTH           0x00000001

#define _SMC1TFCR_FC1_POSITION         0x00000001
#define _SMC1TFCR_FC1_MASK             0x00000001
#define _SMC1TFCR_FC1_LENGTH           0x00000001

#define _SMC1TFCR_FC0_POSITION         0x00000000
#define _SMC1TFCR_FC0_MASK             0x00000001
#define _SMC1TFCR_FC0_LENGTH           0x00000001

#define _SMC1TFCR_FC_POSITION          0x00000000
#define _SMC1TFCR_FC_MASK              0x0000000F
#define _SMC1TFCR_FC_LENGTH            0x00000004

#define _SMC2TFCR_MOT_POSITION         0x00000004
#define _SMC2TFCR_MOT_MASK             0x00000001
#define _SMC2TFCR_MOT_LENGTH           0x00000001

#define _SMC2TFCR_FC3_POSITION         0x00000003
#define _SMC2TFCR_FC3_MASK             0x00000001
#define _SMC2TFCR_FC3_LENGTH           0x00000001

#define _SMC2TFCR_FC2_POSITION         0x00000002
#define _SMC2TFCR_FC2_MASK             0x00000001
#define _SMC2TFCR_FC2_LENGTH           0x00000001

#define _SMC2TFCR_FC1_POSITION         0x00000001
#define _SMC2TFCR_FC1_MASK             0x00000001
#define _SMC2TFCR_FC1_LENGTH           0x00000001

#define _SMC2TFCR_FC0_POSITION         0x00000000
#define _SMC2TFCR_FC0_MASK             0x00000001
#define _SMC2TFCR_FC0_LENGTH           0x00000001

#define _SMC2TFCR_FC_POSITION          0x00000000
#define _SMC2TFCR_FC_MASK              0x0000000F
#define _SMC2TFCR_FC_LENGTH            0x00000004

#define _MCR_BR040ID2_POSITION         0x0000001F
#define _MCR_BR040ID2_MASK             0x00000001
#define _MCR_BR040ID2_LENGTH           0x00000001

#define _MCR_BR040ID1_POSITION         0x0000001E
#define _MCR_BR040ID1_MASK             0x00000001
#define _MCR_BR040ID1_LENGTH           0x00000001

#define _MCR_BR040ID0_POSITION         0x0000001D
#define _MCR_BR040ID0_MASK             0x00000001
#define _MCR_BR040ID0_LENGTH           0x00000001

#define _MCR_BR040ID_POSITION          0x0000001D
#define _MCR_BR040ID_MASK              0x00000007
#define _MCR_BR040ID_LENGTH            0x00000003

#define _MCR_BSTM_POSITION             0x00000010
#define _MCR_BSTM_MASK                 0x00000001
#define _MCR_BSTM_LENGTH               0x00000001

#define _MCR_ASTM_POSITION             0x0000000F
#define _MCR_ASTM_MASK                 0x00000001
#define _MCR_ASTM_LENGTH               0x00000001

#define _MCR_FRZ1_POSITION             0x0000000E
#define _MCR_FRZ1_MASK                 0x00000001
#define _MCR_FRZ1_LENGTH               0x00000001

#define _MCR_FRZ0_POSITION             0x0000000D
#define _MCR_FRZ0_MASK                 0x00000001
#define _MCR_FRZ0_LENGTH               0x00000001

#define _MCR_FRZ_POSITION              0x0000000D
#define _MCR_FRZ_MASK                  0x00000003
#define _MCR_FRZ_LENGTH                0x00000002

#define _MCR_BCLROID2_POSITION         0x0000000C
#define _MCR_BCLROID2_MASK             0x00000001
#define _MCR_BCLROID2_LENGTH           0x00000001

#define _MCR_BCLROID1_POSITION         0x0000000B
#define _MCR_BCLROID1_MASK             0x00000001
#define _MCR_BCLROID1_LENGTH           0x00000001

#define _MCR_BCLROID0_POSITION         0x0000000A
#define _MCR_BCLROID0_MASK             0x00000001
#define _MCR_BCLROID0_LENGTH           0x00000001

#define _MCR_BCLROID_POSITION          0x0000000A
#define _MCR_BCLROID_MASK              0x00000007
#define _MCR_BCLROID_LENGTH            0x00000003

#define _MCR_SHEN1_POSITION            0x00000009
#define _MCR_SHEN1_MASK                0x00000001
#define _MCR_SHEN1_LENGTH              0x00000001

#define _MCR_SHEN0_POSITION            0x00000008
#define _MCR_SHEN0_MASK                0x00000001
#define _MCR_SHEN0_LENGTH              0x00000001

#define _MCR_SHEN_POSITION             0x00000008
#define _MCR_SHEN_MASK                 0x00000003
#define _MCR_SHEN_LENGTH               0x00000002

#define _MCR_SUPV_POSITION             0x00000007
#define _MCR_SUPV_MASK                 0x00000001
#define _MCR_SUPV_LENGTH               0x00000001

#define _MCR_BCLRISM2_POSITION         0x00000006
#define _MCR_BCLRISM2_MASK             0x00000001
#define _MCR_BCLRISM2_LENGTH           0x00000001

#define _MCR_BCLRIIDM2_POSITION        0x00000006
#define _MCR_BCLRIIDM2_MASK            0x00000001
#define _MCR_BCLRIIDM2_LENGTH          0x00000001

#define _MCR_BCLRISM1_POSITION         0x00000005
#define _MCR_BCLRISM1_MASK             0x00000001
#define _MCR_BCLRISM1_LENGTH           0x00000001

#define _MCR_BCLRIIDM1_POSITION        0x00000005
#define _MCR_BCLRIIDM1_MASK            0x00000001
#define _MCR_BCLRIIDM1_LENGTH          0x00000001

#define _MCR_BCLRISM0_POSITION         0x00000004
#define _MCR_BCLRISM0_MASK             0x00000001
#define _MCR_BCLRISM0_LENGTH           0x00000001

#define _MCR_BCLRIIDM0_POSITION        0x00000004
#define _MCR_BCLRIIDM0_MASK            0x00000001
#define _MCR_BCLRIIDM0_LENGTH          0x00000001

#define _MCR_BCLRISM_POSITION          0x00000004
#define _MCR_BCLRISM_MASK              0x00000007
#define _MCR_BCLRISM_LENGTH            0x00000003

#define _MCR_BCLRIID_POSITION          0x00000004
#define _MCR_BCLRIID_MASK              0x00000007
#define _MCR_BCLRIID_LENGTH            0x00000003

#define _MCR_IARB3_POSITION            0x00000003
#define _MCR_IARB3_MASK                0x00000001
#define _MCR_IARB3_LENGTH              0x00000001

#define _MCR_IARB2_POSITION            0x00000002
#define _MCR_IARB2_MASK                0x00000001
#define _MCR_IARB2_LENGTH              0x00000001

#define _MCR_IARB1_POSITION            0x00000001
#define _MCR_IARB1_MASK                0x00000001
#define _MCR_IARB1_LENGTH              0x00000001

#define _MCR_IARB0_POSITION            0x00000000
#define _MCR_IARB0_MASK                0x00000001
#define _MCR_IARB0_LENGTH              0x00000001

#define _MCR_IARB_POSITION             0x00000000
#define _MCR_IARB_MASK                 0x0000000F
#define _MCR_IARB_LENGTH               0x00000004

#define _RSR_EXT_POSITION              0x00000007
#define _RSR_EXT_MASK                  0x00000001
#define _RSR_EXT_LENGTH                0x00000001

#define _RSR_POW_POSITION              0x00000006
#define _RSR_POW_MASK                  0x00000001
#define _RSR_POW_LENGTH                0x00000001

#define _RSR_SW_POSITION               0x00000005
#define _RSR_SW_MASK                   0x00000001
#define _RSR_SW_LENGTH                 0x00000001

#define _RSR_DBF_POSITION              0x00000004
#define _RSR_DBF_MASK                  0x00000001
#define _RSR_DBF_LENGTH                0x00000001

#define _RSR_LOC_POSITION              0x00000002
#define _RSR_LOC_MASK                  0x00000001
#define _RSR_LOC_LENGTH                0x00000001

#define _RSR_SRST_POSITION             0x00000001
#define _RSR_SRST_MASK                 0x00000001
#define _RSR_SRST_LENGTH               0x00000001

#define _RSR_SRSTP_POSITION            0x00000000
#define _RSR_SRSTP_MASK                0x00000001
#define _RSR_SRSTP_LENGTH              0x00000001

#define _PLLCR_PLLEN_POSITION          0x0000000F
#define _PLLCR_PLLEN_MASK              0x00000001
#define _PLLCR_PLLEN_LENGTH            0x00000001

#define _PLLCR_PLLWP_POSITION          0x0000000E
#define _PLLCR_PLLWP_MASK              0x00000001
#define _PLLCR_PLLWP_LENGTH            0x00000001

#define _PLLCR_PREEN_POSITION          0x0000000D
#define _PLLCR_PREEN_MASK              0x00000001
#define _PLLCR_PREEN_LENGTH            0x00000001

#define _PLLCR_STSIM_POSITION          0x0000000C
#define _PLLCR_STSIM_MASK              0x00000001
#define _PLLCR_STSIM_LENGTH            0x00000001

#define _PLLCR_MF11_POSITION           0x0000000B
#define _PLLCR_MF11_MASK               0x00000001
#define _PLLCR_MF11_LENGTH             0x00000001

#define _PLLCR_MF10_POSITION           0x0000000A
#define _PLLCR_MF10_MASK               0x00000001
#define _PLLCR_MF10_LENGTH             0x00000001

#define _PLLCR_MF9_POSITION            0x00000009
#define _PLLCR_MF9_MASK                0x00000001
#define _PLLCR_MF9_LENGTH              0x00000001

#define _PLLCR_MF8_POSITION            0x00000008
#define _PLLCR_MF8_MASK                0x00000001
#define _PLLCR_MF8_LENGTH              0x00000001

#define _PLLCR_MF7_POSITION            0x00000007
#define _PLLCR_MF7_MASK                0x00000001
#define _PLLCR_MF7_LENGTH              0x00000001

#define _PLLCR_MF6_POSITION            0x00000006
#define _PLLCR_MF6_MASK                0x00000001
#define _PLLCR_MF6_LENGTH              0x00000001

#define _PLLCR_MF5_POSITION            0x00000005
#define _PLLCR_MF5_MASK                0x00000001
#define _PLLCR_MF5_LENGTH              0x00000001

#define _PLLCR_MF4_POSITION            0x00000004
#define _PLLCR_MF4_MASK                0x00000001
#define _PLLCR_MF4_LENGTH              0x00000001

#define _PLLCR_MF3_POSITION            0x00000003
#define _PLLCR_MF3_MASK                0x00000001
#define _PLLCR_MF3_LENGTH              0x00000001

#define _PLLCR_MF2_POSITION            0x00000002
#define _PLLCR_MF2_MASK                0x00000001
#define _PLLCR_MF2_LENGTH              0x00000001

#define _PLLCR_MF1_POSITION            0x00000001
#define _PLLCR_MF1_MASK                0x00000001
#define _PLLCR_MF1_LENGTH              0x00000001

#define _PLLCR_MF0_POSITION            0x00000000
#define _PLLCR_MF0_MASK                0x00000001
#define _PLLCR_MF0_LENGTH              0x00000001

#define _PLLCR_MF_POSITION             0x00000000
#define _PLLCR_MF_MASK                 0x00000FFF
#define _PLLCR_MF_LENGTH               0x0000000C

#define _CDVCR_CDVWP_POSITION          0x0000000F
#define _CDVCR_CDVWP_MASK              0x00000001
#define _CDVCR_CDVWP_LENGTH            0x00000001

#define _CDVCR_DFSY1_POSITION          0x0000000E
#define _CDVCR_DFSY1_MASK              0x00000001
#define _CDVCR_DFSY1_LENGTH            0x00000001

#define _CDVCR_DFSY0_POSITION          0x0000000D
#define _CDVCR_DFSY0_MASK              0x00000001
#define _CDVCR_DFSY0_LENGTH            0x00000001

#define _CDVCR_DFSY_POSITION           0x0000000D
#define _CDVCR_DFSY_MASK               0x00000003
#define _CDVCR_DFSY_LENGTH             0x00000002

#define _CDVCR_DFTM1_POSITION          0x0000000C
#define _CDVCR_DFTM1_MASK              0x00000001
#define _CDVCR_DFTM1_LENGTH            0x00000001

#define _CDVCR_DFTM0_POSITION          0x0000000B
#define _CDVCR_DFTM0_MASK              0x00000001
#define _CDVCR_DFTM0_LENGTH            0x00000001

#define _CDVCR_DFTM_POSITION           0x0000000B
#define _CDVCR_DFTM_MASK               0x00000003
#define _CDVCR_DFTM_LENGTH             0x00000002

#define _CDVCR_INTEN2_POSITION         0x0000000A
#define _CDVCR_INTEN2_MASK             0x00000001
#define _CDVCR_INTEN2_LENGTH           0x00000001

#define _CDVCR_INTEN1_POSITION         0x00000009
#define _CDVCR_INTEN1_MASK             0x00000001
#define _CDVCR_INTEN1_LENGTH           0x00000001

#define _CDVCR_INTEN0_POSITION         0x00000008
#define _CDVCR_INTEN0_MASK             0x00000001
#define _CDVCR_INTEN0_LENGTH           0x00000001

#define _CDVCR_INTEN_POSITION          0x00000008
#define _CDVCR_INTEN_MASK              0x00000007
#define _CDVCR_INTEN_LENGTH            0x00000003

#define _CDVCR_RRQEN_POSITION          0x00000007
#define _CDVCR_RRQEN_MASK              0x00000001
#define _CDVCR_RRQEN_LENGTH            0x00000001

#define _CDVCR_DFNL2_POSITION          0x00000006
#define _CDVCR_DFNL2_MASK              0x00000001
#define _CDVCR_DFNL2_LENGTH            0x00000001

#define _CDVCR_DFNL1_POSITION          0x00000005
#define _CDVCR_DFNL1_MASK              0x00000001
#define _CDVCR_DFNL1_LENGTH            0x00000001

#define _CDVCR_DFNL0_POSITION          0x00000004
#define _CDVCR_DFNL0_MASK              0x00000001
#define _CDVCR_DFNL0_LENGTH            0x00000001

#define _CDVCR_DFNL_POSITION           0x00000004
#define _CDVCR_DFNL_MASK               0x00000007
#define _CDVCR_DFNL_LENGTH             0x00000003

#define _CDVCR_DFNH2_POSITION          0x00000003
#define _CDVCR_DFNH2_MASK              0x00000001
#define _CDVCR_DFNH2_LENGTH            0x00000001

#define _CDVCR_DFNH1_POSITION          0x00000002
#define _CDVCR_DFNH1_MASK              0x00000001
#define _CDVCR_DFNH1_LENGTH            0x00000001

#define _CDVCR_DFNH0_POSITION          0x00000001
#define _CDVCR_DFNH0_MASK              0x00000001
#define _CDVCR_DFNH0_LENGTH            0x00000001

#define _CDVCR_DFNH_POSITION           0x00000001
#define _CDVCR_DFNH_MASK               0x00000007
#define _CDVCR_DFNH_LENGTH             0x00000003

#define _CDVCR_CSRC_POSITION           0x00000000
#define _CDVCR_CSRC_MASK               0x00000001
#define _CDVCR_CSRC_LENGTH             0x00000001

#define _SYPCR_SWE_POSITION            0x00000007
#define _SYPCR_SWE_MASK                0x00000001
#define _SYPCR_SWE_LENGTH              0x00000001

#define _SYPCR_SWRI_POSITION           0x00000006
#define _SYPCR_SWRI_MASK               0x00000001
#define _SYPCR_SWRI_LENGTH             0x00000001

#define _SYPCR_SWT1_POSITION           0x00000005
#define _SYPCR_SWT1_MASK               0x00000001
#define _SYPCR_SWT1_LENGTH             0x00000001

#define _SYPCR_SWT0_POSITION           0x00000004
#define _SYPCR_SWT0_MASK               0x00000001
#define _SYPCR_SWT0_LENGTH             0x00000001

#define _SYPCR_SWT_POSITION            0x00000004
#define _SYPCR_SWT_MASK                0x00000003
#define _SYPCR_SWT_LENGTH              0x00000002

#define _SYPCR_DBFE_POSITION           0x00000003
#define _SYPCR_DBFE_MASK               0x00000001
#define _SYPCR_DBFE_LENGTH             0x00000001

#define _SYPCR_BME_POSITION            0x00000002
#define _SYPCR_BME_MASK                0x00000001
#define _SYPCR_BME_LENGTH              0x00000001

#define _SYPCR_BMT1_POSITION           0x00000001
#define _SYPCR_BMT1_MASK               0x00000001
#define _SYPCR_BMT1_LENGTH             0x00000001

#define _SYPCR_BMT0_POSITION           0x00000000
#define _SYPCR_BMT0_MASK               0x00000001
#define _SYPCR_BMT0_LENGTH             0x00000001

#define _SYPCR_BMT_POSITION            0x00000000
#define _SYPCR_BMT_MASK                0x00000003
#define _SYPCR_BMT_LENGTH              0x00000002

#define _PICR_PIRQL2_POSITION          0x0000000A
#define _PICR_PIRQL2_MASK              0x00000001
#define _PICR_PIRQL2_LENGTH            0x00000001

#define _PICR_PIRQL1_POSITION          0x00000009
#define _PICR_PIRQL1_MASK              0x00000001
#define _PICR_PIRQL1_LENGTH            0x00000001

#define _PICR_PIRQL0_POSITION          0x00000008
#define _PICR_PIRQL0_MASK              0x00000001
#define _PICR_PIRQL0_LENGTH            0x00000001

#define _PICR_PIRQL_POSITION           0x00000008
#define _PICR_PIRQL_MASK               0x00000007
#define _PICR_PIRQL_LENGTH             0x00000003

#define _PICR_PIV7_POSITION            0x00000007
#define _PICR_PIV7_MASK                0x00000001
#define _PICR_PIV7_LENGTH              0x00000001

#define _PICR_PIV6_POSITION            0x00000006
#define _PICR_PIV6_MASK                0x00000001
#define _PICR_PIV6_LENGTH              0x00000001

#define _PICR_PIV5_POSITION            0x00000005
#define _PICR_PIV5_MASK                0x00000001
#define _PICR_PIV5_LENGTH              0x00000001

#define _PICR_PIV4_POSITION            0x00000004
#define _PICR_PIV4_MASK                0x00000001
#define _PICR_PIV4_LENGTH              0x00000001

#define _PICR_PIV3_POSITION            0x00000003
#define _PICR_PIV3_MASK                0x00000001
#define _PICR_PIV3_LENGTH              0x00000001

#define _PICR_PIV2_POSITION            0x00000002
#define _PICR_PIV2_MASK                0x00000001
#define _PICR_PIV2_LENGTH              0x00000001

#define _PICR_PIV1_POSITION            0x00000001
#define _PICR_PIV1_MASK                0x00000001
#define _PICR_PIV1_LENGTH              0x00000001

#define _PICR_PIV0_POSITION            0x00000000
#define _PICR_PIV0_MASK                0x00000001
#define _PICR_PIV0_LENGTH              0x00000001

#define _PICR_PIV_POSITION             0x00000000
#define _PICR_PIV_MASK                 0x000000FF
#define _PICR_PIV_LENGTH               0x00000008

#define _PITR_SWP_POSITION             0x00000009
#define _PITR_SWP_MASK                 0x00000001
#define _PITR_SWP_LENGTH               0x00000001

#define _PITR_PTP_POSITION             0x00000008
#define _PITR_PTP_MASK                 0x00000001
#define _PITR_PTP_LENGTH               0x00000001

#define _PITR_CTR7_POSITION            0x00000007
#define _PITR_CTR7_MASK                0x00000001
#define _PITR_CTR7_LENGTH              0x00000001

#define _PITR_CTR6_POSITION            0x00000006
#define _PITR_CTR6_MASK                0x00000001
#define _PITR_CTR6_LENGTH              0x00000001

#define _PITR_CTR5_POSITION            0x00000005
#define _PITR_CTR5_MASK                0x00000001
#define _PITR_CTR5_LENGTH              0x00000001

#define _PITR_CTR4_POSITION            0x00000004
#define _PITR_CTR4_MASK                0x00000001
#define _PITR_CTR4_LENGTH              0x00000001

#define _PITR_CTR3_POSITION            0x00000003
#define _PITR_CTR3_MASK                0x00000001
#define _PITR_CTR3_LENGTH              0x00000001

#define _PITR_CTR2_POSITION            0x00000002
#define _PITR_CTR2_MASK                0x00000001
#define _PITR_CTR2_LENGTH              0x00000001

#define _PITR_CTR1_POSITION            0x00000001
#define _PITR_CTR1_MASK                0x00000001
#define _PITR_CTR1_LENGTH              0x00000001

#define _PITR_CTR0_POSITION            0x00000000
#define _PITR_CTR0_MASK                0x00000001
#define _PITR_CTR0_LENGTH              0x00000001

#define _PITR_CTR_POSITION             0x00000000
#define _PITR_CTR_MASK                 0x000000FF
#define _PITR_CTR_LENGTH               0x00000008

#define _BKCR_BAS_POSITION             0x00000013
#define _BKCR_BAS_MASK                 0x00000001
#define _BKCR_BAS_LENGTH               0x00000001

#define _BKCR_BUSS_POSITION            0x00000012
#define _BKCR_BUSS_MASK                0x00000001
#define _BKCR_BUSS_LENGTH              0x00000001

#define _BKCR_RW1_POSITION             0x00000011
#define _BKCR_RW1_MASK                 0x00000001
#define _BKCR_RW1_LENGTH               0x00000001

#define _BKCR_RW0_POSITION             0x00000010
#define _BKCR_RW0_MASK                 0x00000001
#define _BKCR_RW0_LENGTH               0x00000001

#define _BKCR_RW_POSITION              0x00000010
#define _BKCR_RW_MASK                  0x00000003
#define _BKCR_RW_LENGTH                0x00000002

#define _BKCR_SIZM_POSITION            0x0000000F
#define _BKCR_SIZM_MASK                0x00000001
#define _BKCR_SIZM_LENGTH              0x00000001

#define _BKCR_SIZ1_POSITION            0x0000000E
#define _BKCR_SIZ1_MASK                0x00000001
#define _BKCR_SIZ1_LENGTH              0x00000001

#define _BKCR_SIZ0_POSITION            0x0000000D
#define _BKCR_SIZ0_MASK                0x00000001
#define _BKCR_SIZ0_LENGTH              0x00000001

#define _BKCR_SIZ_POSITION             0x0000000D
#define _BKCR_SIZ_MASK                 0x00000003
#define _BKCR_SIZ_LENGTH               0x00000002

#define _BKCR_NEG_POSITION             0x0000000C
#define _BKCR_NEG_MASK                 0x00000001
#define _BKCR_NEG_LENGTH               0x00000001

#define _BKCR_MA1_POSITION             0x0000000B
#define _BKCR_MA1_MASK                 0x00000001
#define _BKCR_MA1_LENGTH               0x00000001

#define _BKCR_MA0_POSITION             0x0000000A
#define _BKCR_MA0_MASK                 0x00000001
#define _BKCR_MA0_LENGTH               0x00000001

#define _BKCR_MA_POSITION              0x0000000A
#define _BKCR_MA_MASK                  0x00000003
#define _BKCR_MA_LENGTH                0x00000002

#define _BKCR_AS8_POSITION             0x00000009
#define _BKCR_AS8_MASK                 0x00000001
#define _BKCR_AS8_LENGTH               0x00000001

#define _BKCR_AS7_POSITION             0x00000008
#define _BKCR_AS7_MASK                 0x00000001
#define _BKCR_AS7_LENGTH               0x00000001

#define _BKCR_AS6_POSITION             0x00000007
#define _BKCR_AS6_MASK                 0x00000001
#define _BKCR_AS6_LENGTH               0x00000001

#define _BKCR_AS5_POSITION             0x00000006
#define _BKCR_AS5_MASK                 0x00000001
#define _BKCR_AS5_LENGTH               0x00000001

#define _BKCR_AS4_POSITION             0x00000005
#define _BKCR_AS4_MASK                 0x00000001
#define _BKCR_AS4_LENGTH               0x00000001

#define _BKCR_AS3_POSITION             0x00000004
#define _BKCR_AS3_MASK                 0x00000001
#define _BKCR_AS3_LENGTH               0x00000001

#define _BKCR_AS2_POSITION             0x00000003
#define _BKCR_AS2_MASK                 0x00000001
#define _BKCR_AS2_LENGTH               0x00000001

#define _BKCR_AS1_POSITION             0x00000002
#define _BKCR_AS1_MASK                 0x00000001
#define _BKCR_AS1_LENGTH               0x00000001

#define _BKCR_AS0_POSITION             0x00000001
#define _BKCR_AS0_MASK                 0x00000001
#define _BKCR_AS0_LENGTH               0x00000001

#define _BKCR_AS_POSITION              0x00000001
#define _BKCR_AS_MASK                  0x000001FF
#define _BKCR_AS_LENGTH                0x00000009

#define _BKCR_V_POSITION               0x00000000
#define _BKCR_V_MASK                   0x00000001
#define _BKCR_V_LENGTH                 0x00000001

#define _GMR_RCNT7_POSITION            0x0000001F
#define _GMR_RCNT7_MASK                0x00000001
#define _GMR_RCNT7_LENGTH              0x00000001

#define _GMR_RCNT6_POSITION            0x0000001E
#define _GMR_RCNT6_MASK                0x00000001
#define _GMR_RCNT6_LENGTH              0x00000001

#define _GMR_RCNT5_POSITION            0x0000001D
#define _GMR_RCNT5_MASK                0x00000001
#define _GMR_RCNT5_LENGTH              0x00000001

#define _GMR_RCNT4_POSITION            0x0000001C
#define _GMR_RCNT4_MASK                0x00000001
#define _GMR_RCNT4_LENGTH              0x00000001

#define _GMR_RCNT3_POSITION            0x0000001B
#define _GMR_RCNT3_MASK                0x00000001
#define _GMR_RCNT3_LENGTH              0x00000001

#define _GMR_RCNT2_POSITION            0x0000001A
#define _GMR_RCNT2_MASK                0x00000001
#define _GMR_RCNT2_LENGTH              0x00000001

#define _GMR_RCNT1_POSITION            0x00000019
#define _GMR_RCNT1_MASK                0x00000001
#define _GMR_RCNT1_LENGTH              0x00000001

#define _GMR_RCNT0_POSITION            0x00000018
#define _GMR_RCNT0_MASK                0x00000001
#define _GMR_RCNT0_LENGTH              0x00000001

#define _GMR_RCNT_POSITION             0x00000018
#define _GMR_RCNT_MASK                 0x000000FF
#define _GMR_RCNT_LENGTH               0x00000008

#define _GMR_RFEN_POSITION             0x00000017
#define _GMR_RFEN_MASK                 0x00000001
#define _GMR_RFEN_LENGTH               0x00000001

#define _GMR_RCYC1_POSITION            0x00000016
#define _GMR_RCYC1_MASK                0x00000001
#define _GMR_RCYC1_LENGTH              0x00000001

#define _GMR_RCYC0_POSITION            0x00000015
#define _GMR_RCYC0_MASK                0x00000001
#define _GMR_RCYC0_LENGTH              0x00000001

#define _GMR_RCYC_POSITION             0x00000015
#define _GMR_RCYC_MASK                 0x00000003
#define _GMR_RCYC_LENGTH               0x00000002

#define _GMR_PGS2_POSITION             0x00000014
#define _GMR_PGS2_MASK                 0x00000001
#define _GMR_PGS2_LENGTH               0x00000001

#define _GMR_PGS1_POSITION             0x00000013
#define _GMR_PGS1_MASK                 0x00000001
#define _GMR_PGS1_LENGTH               0x00000001

#define _GMR_PGS0_POSITION             0x00000012
#define _GMR_PGS0_MASK                 0x00000001
#define _GMR_PGS0_LENGTH               0x00000001

#define _GMR_PGS_POSITION              0x00000012
#define _GMR_PGS_MASK                  0x00000007
#define _GMR_PGS_LENGTH                0x00000003

#define _GMR_DPS1_POSITION             0x00000011
#define _GMR_DPS1_MASK                 0x00000001
#define _GMR_DPS1_LENGTH               0x00000001

#define _GMR_DPS0_POSITION             0x00000010
#define _GMR_DPS0_MASK                 0x00000001
#define _GMR_DPS0_LENGTH               0x00000001

#define _GMR_DPS_POSITION              0x00000010
#define _GMR_DPS_MASK                  0x00000003
#define _GMR_DPS_LENGTH                0x00000002

#define _GMR_WBT40_POSITION            0x0000000F
#define _GMR_WBT40_MASK                0x00000001
#define _GMR_WBT40_LENGTH              0x00000001

#define _GMR_WBTQ_POSITION             0x0000000E
#define _GMR_WBTQ_MASK                 0x00000001
#define _GMR_WBTQ_LENGTH               0x00000001

#define _GMR_SYNC_POSITION             0x0000000D
#define _GMR_SYNC_MASK                 0x00000001
#define _GMR_SYNC_LENGTH               0x00000001

#define _GMR_EMWS_POSITION             0x0000000C
#define _GMR_EMWS_MASK                 0x00000001
#define _GMR_EMWS_LENGTH               0x00000001

#define _GMR_OPAR_POSITION             0x0000000B
#define _GMR_OPAR_MASK                 0x00000001
#define _GMR_OPAR_LENGTH               0x00000001

#define _GMR_PBEE_POSITION             0x0000000A
#define _GMR_PBEE_MASK                 0x00000001
#define _GMR_PBEE_LENGTH               0x00000001

#define _GMR_TSS40_POSITION            0x00000009
#define _GMR_TSS40_MASK                0x00000001
#define _GMR_TSS40_LENGTH              0x00000001

#define _GMR_NCS_POSITION              0x00000008
#define _GMR_NCS_MASK                  0x00000001
#define _GMR_NCS_LENGTH                0x00000001

#define _GMR_DWQ_POSITION              0x00000007
#define _GMR_DWQ_MASK                  0x00000001
#define _GMR_DWQ_LENGTH                0x00000001

#define _GMR_W40_POSITION              0x00000006
#define _GMR_W40_MASK                  0x00000001
#define _GMR_W40_LENGTH                0x00000001

#define _GMR_GAMX_POSITION             0x00000005
#define _GMR_GAMX_MASK                 0x00000001
#define _GMR_GAMX_LENGTH               0x00000001

#define _MSTAT_WPER_POSITION           0x00000008
#define _MSTAT_WPER_MASK               0x00000001
#define _MSTAT_WPER_LENGTH             0x00000001

#define _MSTAT_PER7_POSITION           0x00000007
#define _MSTAT_PER7_MASK               0x00000001
#define _MSTAT_PER7_LENGTH             0x00000001

#define _MSTAT_PER6_POSITION           0x00000006
#define _MSTAT_PER6_MASK               0x00000001
#define _MSTAT_PER6_LENGTH             0x00000001

#define _MSTAT_PER5_POSITION           0x00000005
#define _MSTAT_PER5_MASK               0x00000001
#define _MSTAT_PER5_LENGTH             0x00000001

#define _MSTAT_PER4_POSITION           0x00000004
#define _MSTAT_PER4_MASK               0x00000001
#define _MSTAT_PER4_LENGTH             0x00000001

#define _MSTAT_PER3_POSITION           0x00000003
#define _MSTAT_PER3_MASK               0x00000001
#define _MSTAT_PER3_LENGTH             0x00000001

#define _MSTAT_PER2_POSITION           0x00000002
#define _MSTAT_PER2_MASK               0x00000001
#define _MSTAT_PER2_LENGTH             0x00000001

#define _MSTAT_PER1_POSITION           0x00000001
#define _MSTAT_PER1_MASK               0x00000001
#define _MSTAT_PER1_LENGTH             0x00000001

#define _MSTAT_PER0_POSITION           0x00000000
#define _MSTAT_PER0_MASK               0x00000001
#define _MSTAT_PER0_LENGTH             0x00000001

#define _MSTAT_PER_POSITION            0x00000000
#define _MSTAT_PER_MASK                0x000000FF
#define _MSTAT_PER_LENGTH              0x00000008

#define _BR0_BA31_POSITION             0x0000001F
#define _BR0_BA31_MASK                 0x00000001
#define _BR0_BA31_LENGTH               0x00000001

#define _BR0_BA30_POSITION             0x0000001E
#define _BR0_BA30_MASK                 0x00000001
#define _BR0_BA30_LENGTH               0x00000001

#define _BR0_BA29_POSITION             0x0000001D
#define _BR0_BA29_MASK                 0x00000001
#define _BR0_BA29_LENGTH               0x00000001

#define _BR0_BA28_POSITION             0x0000001C
#define _BR0_BA28_MASK                 0x00000001
#define _BR0_BA28_LENGTH               0x00000001

#define _BR0_BA27_POSITION             0x0000001B
#define _BR0_BA27_MASK                 0x00000001
#define _BR0_BA27_LENGTH               0x00000001

#define _BR0_BA26_POSITION             0x0000001A
#define _BR0_BA26_MASK                 0x00000001
#define _BR0_BA26_LENGTH               0x00000001

#define _BR0_BA25_POSITION             0x00000019
#define _BR0_BA25_MASK                 0x00000001
#define _BR0_BA25_LENGTH               0x00000001

#define _BR0_BA24_POSITION             0x00000018
#define _BR0_BA24_MASK                 0x00000001
#define _BR0_BA24_LENGTH               0x00000001

#define _BR0_BA23_POSITION             0x00000017
#define _BR0_BA23_MASK                 0x00000001
#define _BR0_BA23_LENGTH               0x00000001

#define _BR0_BA22_POSITION             0x00000016
#define _BR0_BA22_MASK                 0x00000001
#define _BR0_BA22_LENGTH               0x00000001

#define _BR0_BA21_POSITION             0x00000015
#define _BR0_BA21_MASK                 0x00000001
#define _BR0_BA21_LENGTH               0x00000001

#define _BR0_BA20_POSITION             0x00000014
#define _BR0_BA20_MASK                 0x00000001
#define _BR0_BA20_LENGTH               0x00000001

#define _BR0_BA19_POSITION             0x00000013
#define _BR0_BA19_MASK                 0x00000001
#define _BR0_BA19_LENGTH               0x00000001

#define _BR0_BA18_POSITION             0x00000012
#define _BR0_BA18_MASK                 0x00000001
#define _BR0_BA18_LENGTH               0x00000001

#define _BR0_BA17_POSITION             0x00000011
#define _BR0_BA17_MASK                 0x00000001
#define _BR0_BA17_LENGTH               0x00000001

#define _BR0_BA16_POSITION             0x00000010
#define _BR0_BA16_MASK                 0x00000001
#define _BR0_BA16_LENGTH               0x00000001

#define _BR0_BA15_POSITION             0x0000000F
#define _BR0_BA15_MASK                 0x00000001
#define _BR0_BA15_LENGTH               0x00000001

#define _BR0_BA14_POSITION             0x0000000E
#define _BR0_BA14_MASK                 0x00000001
#define _BR0_BA14_LENGTH               0x00000001

#define _BR0_BA13_POSITION             0x0000000D
#define _BR0_BA13_MASK                 0x00000001
#define _BR0_BA13_LENGTH               0x00000001

#define _BR0_BA12_POSITION             0x0000000C
#define _BR0_BA12_MASK                 0x00000001
#define _BR0_BA12_LENGTH               0x00000001

#define _BR0_BA11_POSITION             0x0000000B
#define _BR0_BA11_MASK                 0x00000001
#define _BR0_BA11_LENGTH               0x00000001

#define _BR0_BA_POSITION               0x0000000B
#define _BR0_BA_MASK                   0x001FFFFF
#define _BR0_BA_LENGTH                 0x00000015

#define _BR0_FC3_POSITION              0x0000000A
#define _BR0_FC3_MASK                  0x00000001
#define _BR0_FC3_LENGTH                0x00000001

#define _BR0_FC2_POSITION              0x00000009
#define _BR0_FC2_MASK                  0x00000001
#define _BR0_FC2_LENGTH                0x00000001

#define _BR0_FC1_POSITION              0x00000008
#define _BR0_FC1_MASK                  0x00000001
#define _BR0_FC1_LENGTH                0x00000001

#define _BR0_FC0_POSITION              0x00000007
#define _BR0_FC0_MASK                  0x00000001
#define _BR0_FC0_LENGTH                0x00000001

#define _BR0_FC_POSITION               0x00000007
#define _BR0_FC_MASK                   0x0000000F
#define _BR0_FC_LENGTH                 0x00000004

#define _BR0_TRLXQ_POSITION            0x00000006
#define _BR0_TRLXQ_MASK                0x00000001
#define _BR0_TRLXQ_LENGTH              0x00000001

#define _BR0_BACK40_POSITION           0x00000005
#define _BR0_BACK40_MASK               0x00000001
#define _BR0_BACK40_LENGTH             0x00000001

#define _BR0_CSNT40_POSITION           0x00000004
#define _BR0_CSNT40_MASK               0x00000001
#define _BR0_CSNT40_LENGTH             0x00000001

#define _BR0_CSNTQ_POSITION            0x00000003
#define _BR0_CSNTQ_MASK                0x00000001
#define _BR0_CSNTQ_LENGTH              0x00000001

#define _BR0_PAREN_POSITION            0x00000002
#define _BR0_PAREN_MASK                0x00000001
#define _BR0_PAREN_LENGTH              0x00000001

#define _BR0_WP_POSITION               0x00000001
#define _BR0_WP_MASK                   0x00000001
#define _BR0_WP_LENGTH                 0x00000001

#define _BR0_V_POSITION                0x00000000
#define _BR0_V_MASK                    0x00000001
#define _BR0_V_LENGTH                  0x00000001

#define _BR1_BA31_POSITION             0x0000001F
#define _BR1_BA31_MASK                 0x00000001
#define _BR1_BA31_LENGTH               0x00000001

#define _BR1_BA30_POSITION             0x0000001E
#define _BR1_BA30_MASK                 0x00000001
#define _BR1_BA30_LENGTH               0x00000001

#define _BR1_BA29_POSITION             0x0000001D
#define _BR1_BA29_MASK                 0x00000001
#define _BR1_BA29_LENGTH               0x00000001

#define _BR1_BA28_POSITION             0x0000001C
#define _BR1_BA28_MASK                 0x00000001
#define _BR1_BA28_LENGTH               0x00000001

#define _BR1_BA27_POSITION             0x0000001B
#define _BR1_BA27_MASK                 0x00000001
#define _BR1_BA27_LENGTH               0x00000001

#define _BR1_BA26_POSITION             0x0000001A
#define _BR1_BA26_MASK                 0x00000001
#define _BR1_BA26_LENGTH               0x00000001

#define _BR1_BA25_POSITION             0x00000019
#define _BR1_BA25_MASK                 0x00000001
#define _BR1_BA25_LENGTH               0x00000001

#define _BR1_BA24_POSITION             0x00000018
#define _BR1_BA24_MASK                 0x00000001
#define _BR1_BA24_LENGTH               0x00000001

#define _BR1_BA23_POSITION             0x00000017
#define _BR1_BA23_MASK                 0x00000001
#define _BR1_BA23_LENGTH               0x00000001

#define _BR1_BA22_POSITION             0x00000016
#define _BR1_BA22_MASK                 0x00000001
#define _BR1_BA22_LENGTH               0x00000001

#define _BR1_BA21_POSITION             0x00000015
#define _BR1_BA21_MASK                 0x00000001
#define _BR1_BA21_LENGTH               0x00000001

#define _BR1_BA20_POSITION             0x00000014
#define _BR1_BA20_MASK                 0x00000001
#define _BR1_BA20_LENGTH               0x00000001

#define _BR1_BA19_POSITION             0x00000013
#define _BR1_BA19_MASK                 0x00000001
#define _BR1_BA19_LENGTH               0x00000001

#define _BR1_BA18_POSITION             0x00000012
#define _BR1_BA18_MASK                 0x00000001
#define _BR1_BA18_LENGTH               0x00000001

#define _BR1_BA17_POSITION             0x00000011
#define _BR1_BA17_MASK                 0x00000001
#define _BR1_BA17_LENGTH               0x00000001

#define _BR1_BA16_POSITION             0x00000010
#define _BR1_BA16_MASK                 0x00000001
#define _BR1_BA16_LENGTH               0x00000001

#define _BR1_BA15_POSITION             0x0000000F
#define _BR1_BA15_MASK                 0x00000001
#define _BR1_BA15_LENGTH               0x00000001

#define _BR1_BA14_POSITION             0x0000000E
#define _BR1_BA14_MASK                 0x00000001
#define _BR1_BA14_LENGTH               0x00000001

#define _BR1_BA13_POSITION             0x0000000D
#define _BR1_BA13_MASK                 0x00000001
#define _BR1_BA13_LENGTH               0x00000001

#define _BR1_BA12_POSITION             0x0000000C
#define _BR1_BA12_MASK                 0x00000001
#define _BR1_BA12_LENGTH               0x00000001

#define _BR1_BA11_POSITION             0x0000000B
#define _BR1_BA11_MASK                 0x00000001
#define _BR1_BA11_LENGTH               0x00000001

#define _BR1_BA_POSITION               0x0000000B
#define _BR1_BA_MASK                   0x001FFFFF
#define _BR1_BA_LENGTH                 0x00000015

#define _BR1_FC3_POSITION              0x0000000A
#define _BR1_FC3_MASK                  0x00000001
#define _BR1_FC3_LENGTH                0x00000001

#define _BR1_FC2_POSITION              0x00000009
#define _BR1_FC2_MASK                  0x00000001
#define _BR1_FC2_LENGTH                0x00000001

#define _BR1_FC1_POSITION              0x00000008
#define _BR1_FC1_MASK                  0x00000001
#define _BR1_FC1_LENGTH                0x00000001

#define _BR1_FC0_POSITION              0x00000007
#define _BR1_FC0_MASK                  0x00000001
#define _BR1_FC0_LENGTH                0x00000001

#define _BR1_FC_POSITION               0x00000007
#define _BR1_FC_MASK                   0x0000000F
#define _BR1_FC_LENGTH                 0x00000004

#define _BR1_TRLXQ_POSITION            0x00000006
#define _BR1_TRLXQ_MASK                0x00000001
#define _BR1_TRLXQ_LENGTH              0x00000001

#define _BR1_BACK40_POSITION           0x00000005
#define _BR1_BACK40_MASK               0x00000001
#define _BR1_BACK40_LENGTH             0x00000001

#define _BR1_CSNT40_POSITION           0x00000004
#define _BR1_CSNT40_MASK               0x00000001
#define _BR1_CSNT40_LENGTH             0x00000001

#define _BR1_CSNTQ_POSITION            0x00000003
#define _BR1_CSNTQ_MASK                0x00000001
#define _BR1_CSNTQ_LENGTH              0x00000001

#define _BR1_PAREN_POSITION            0x00000002
#define _BR1_PAREN_MASK                0x00000001
#define _BR1_PAREN_LENGTH              0x00000001

#define _BR1_WP_POSITION               0x00000001
#define _BR1_WP_MASK                   0x00000001
#define _BR1_WP_LENGTH                 0x00000001

#define _BR1_V_POSITION                0x00000000
#define _BR1_V_MASK                    0x00000001
#define _BR1_V_LENGTH                  0x00000001

#define _BR2_BA31_POSITION             0x0000001F
#define _BR2_BA31_MASK                 0x00000001
#define _BR2_BA31_LENGTH               0x00000001

#define _BR2_BA30_POSITION             0x0000001E
#define _BR2_BA30_MASK                 0x00000001
#define _BR2_BA30_LENGTH               0x00000001

#define _BR2_BA29_POSITION             0x0000001D
#define _BR2_BA29_MASK                 0x00000001
#define _BR2_BA29_LENGTH               0x00000001

#define _BR2_BA28_POSITION             0x0000001C
#define _BR2_BA28_MASK                 0x00000001
#define _BR2_BA28_LENGTH               0x00000001

#define _BR2_BA27_POSITION             0x0000001B
#define _BR2_BA27_MASK                 0x00000001
#define _BR2_BA27_LENGTH               0x00000001

#define _BR2_BA26_POSITION             0x0000001A
#define _BR2_BA26_MASK                 0x00000001
#define _BR2_BA26_LENGTH               0x00000001

#define _BR2_BA25_POSITION             0x00000019
#define _BR2_BA25_MASK                 0x00000001
#define _BR2_BA25_LENGTH               0x00000001

#define _BR2_BA24_POSITION             0x00000018
#define _BR2_BA24_MASK                 0x00000001
#define _BR2_BA24_LENGTH               0x00000001

#define _BR2_BA23_POSITION             0x00000017
#define _BR2_BA23_MASK                 0x00000001
#define _BR2_BA23_LENGTH               0x00000001

#define _BR2_BA22_POSITION             0x00000016
#define _BR2_BA22_MASK                 0x00000001
#define _BR2_BA22_LENGTH               0x00000001

#define _BR2_BA21_POSITION             0x00000015
#define _BR2_BA21_MASK                 0x00000001
#define _BR2_BA21_LENGTH               0x00000001

#define _BR2_BA20_POSITION             0x00000014
#define _BR2_BA20_MASK                 0x00000001
#define _BR2_BA20_LENGTH               0x00000001

#define _BR2_BA19_POSITION             0x00000013
#define _BR2_BA19_MASK                 0x00000001
#define _BR2_BA19_LENGTH               0x00000001

#define _BR2_BA18_POSITION             0x00000012
#define _BR2_BA18_MASK                 0x00000001
#define _BR2_BA18_LENGTH               0x00000001

#define _BR2_BA17_POSITION             0x00000011
#define _BR2_BA17_MASK                 0x00000001
#define _BR2_BA17_LENGTH               0x00000001

#define _BR2_BA16_POSITION             0x00000010
#define _BR2_BA16_MASK                 0x00000001
#define _BR2_BA16_LENGTH               0x00000001

#define _BR2_BA15_POSITION             0x0000000F
#define _BR2_BA15_MASK                 0x00000001
#define _BR2_BA15_LENGTH               0x00000001

#define _BR2_BA14_POSITION             0x0000000E
#define _BR2_BA14_MASK                 0x00000001
#define _BR2_BA14_LENGTH               0x00000001

#define _BR2_BA13_POSITION             0x0000000D
#define _BR2_BA13_MASK                 0x00000001
#define _BR2_BA13_LENGTH               0x00000001

#define _BR2_BA12_POSITION             0x0000000C
#define _BR2_BA12_MASK                 0x00000001
#define _BR2_BA12_LENGTH               0x00000001

#define _BR2_BA11_POSITION             0x0000000B
#define _BR2_BA11_MASK                 0x00000001
#define _BR2_BA11_LENGTH               0x00000001

#define _BR2_BA_POSITION               0x0000000B
#define _BR2_BA_MASK                   0x001FFFFF
#define _BR2_BA_LENGTH                 0x00000015

#define _BR2_FC3_POSITION              0x0000000A
#define _BR2_FC3_MASK                  0x00000001
#define _BR2_FC3_LENGTH                0x00000001

#define _BR2_FC2_POSITION              0x00000009
#define _BR2_FC2_MASK                  0x00000001
#define _BR2_FC2_LENGTH                0x00000001

#define _BR2_FC1_POSITION              0x00000008
#define _BR2_FC1_MASK                  0x00000001
#define _BR2_FC1_LENGTH                0x00000001

#define _BR2_FC0_POSITION              0x00000007
#define _BR2_FC0_MASK                  0x00000001
#define _BR2_FC0_LENGTH                0x00000001

#define _BR2_FC_POSITION               0x00000007
#define _BR2_FC_MASK                   0x0000000F
#define _BR2_FC_LENGTH                 0x00000004

#define _BR2_TRLXQ_POSITION            0x00000006
#define _BR2_TRLXQ_MASK                0x00000001
#define _BR2_TRLXQ_LENGTH              0x00000001

#define _BR2_BACK40_POSITION           0x00000005
#define _BR2_BACK40_MASK               0x00000001
#define _BR2_BACK40_LENGTH             0x00000001

#define _BR2_CSNT40_POSITION           0x00000004
#define _BR2_CSNT40_MASK               0x00000001
#define _BR2_CSNT40_LENGTH             0x00000001

#define _BR2_CSNTQ_POSITION            0x00000003
#define _BR2_CSNTQ_MASK                0x00000001
#define _BR2_CSNTQ_LENGTH              0x00000001

#define _BR2_PAREN_POSITION            0x00000002
#define _BR2_PAREN_MASK                0x00000001
#define _BR2_PAREN_LENGTH              0x00000001

#define _BR2_WP_POSITION               0x00000001
#define _BR2_WP_MASK                   0x00000001
#define _BR2_WP_LENGTH                 0x00000001

#define _BR2_V_POSITION                0x00000000
#define _BR2_V_MASK                    0x00000001
#define _BR2_V_LENGTH                  0x00000001

#define _BR3_BA31_POSITION             0x0000001F
#define _BR3_BA31_MASK                 0x00000001
#define _BR3_BA31_LENGTH               0x00000001

#define _BR3_BA30_POSITION             0x0000001E
#define _BR3_BA30_MASK                 0x00000001
#define _BR3_BA30_LENGTH               0x00000001

#define _BR3_BA29_POSITION             0x0000001D
#define _BR3_BA29_MASK                 0x00000001
#define _BR3_BA29_LENGTH               0x00000001

#define _BR3_BA28_POSITION             0x0000001C
#define _BR3_BA28_MASK                 0x00000001
#define _BR3_BA28_LENGTH               0x00000001

#define _BR3_BA27_POSITION             0x0000001B
#define _BR3_BA27_MASK                 0x00000001
#define _BR3_BA27_LENGTH               0x00000001

#define _BR3_BA26_POSITION             0x0000001A
#define _BR3_BA26_MASK                 0x00000001
#define _BR3_BA26_LENGTH               0x00000001

#define _BR3_BA25_POSITION             0x00000019
#define _BR3_BA25_MASK                 0x00000001
#define _BR3_BA25_LENGTH               0x00000001

#define _BR3_BA24_POSITION             0x00000018
#define _BR3_BA24_MASK                 0x00000001
#define _BR3_BA24_LENGTH               0x00000001

#define _BR3_BA23_POSITION             0x00000017
#define _BR3_BA23_MASK                 0x00000001
#define _BR3_BA23_LENGTH               0x00000001

#define _BR3_BA22_POSITION             0x00000016
#define _BR3_BA22_MASK                 0x00000001
#define _BR3_BA22_LENGTH               0x00000001

#define _BR3_BA21_POSITION             0x00000015
#define _BR3_BA21_MASK                 0x00000001
#define _BR3_BA21_LENGTH               0x00000001

#define _BR3_BA20_POSITION             0x00000014
#define _BR3_BA20_MASK                 0x00000001
#define _BR3_BA20_LENGTH               0x00000001

#define _BR3_BA19_POSITION             0x00000013
#define _BR3_BA19_MASK                 0x00000001
#define _BR3_BA19_LENGTH               0x00000001

#define _BR3_BA18_POSITION             0x00000012
#define _BR3_BA18_MASK                 0x00000001
#define _BR3_BA18_LENGTH               0x00000001

#define _BR3_BA17_POSITION             0x00000011
#define _BR3_BA17_MASK                 0x00000001
#define _BR3_BA17_LENGTH               0x00000001

#define _BR3_BA16_POSITION             0x00000010
#define _BR3_BA16_MASK                 0x00000001
#define _BR3_BA16_LENGTH               0x00000001

#define _BR3_BA15_POSITION             0x0000000F
#define _BR3_BA15_MASK                 0x00000001
#define _BR3_BA15_LENGTH               0x00000001

#define _BR3_BA14_POSITION             0x0000000E
#define _BR3_BA14_MASK                 0x00000001
#define _BR3_BA14_LENGTH               0x00000001

#define _BR3_BA13_POSITION             0x0000000D
#define _BR3_BA13_MASK                 0x00000001
#define _BR3_BA13_LENGTH               0x00000001

#define _BR3_BA12_POSITION             0x0000000C
#define _BR3_BA12_MASK                 0x00000001
#define _BR3_BA12_LENGTH               0x00000001

#define _BR3_BA11_POSITION             0x0000000B
#define _BR3_BA11_MASK                 0x00000001
#define _BR3_BA11_LENGTH               0x00000001

#define _BR3_BA_POSITION               0x0000000B
#define _BR3_BA_MASK                   0x001FFFFF
#define _BR3_BA_LENGTH                 0x00000015

#define _BR3_FC3_POSITION              0x0000000A
#define _BR3_FC3_MASK                  0x00000001
#define _BR3_FC3_LENGTH                0x00000001

#define _BR3_FC2_POSITION              0x00000009
#define _BR3_FC2_MASK                  0x00000001
#define _BR3_FC2_LENGTH                0x00000001

#define _BR3_FC1_POSITION              0x00000008
#define _BR3_FC1_MASK                  0x00000001
#define _BR3_FC1_LENGTH                0x00000001

#define _BR3_FC0_POSITION              0x00000007
#define _BR3_FC0_MASK                  0x00000001
#define _BR3_FC0_LENGTH                0x00000001

#define _BR3_FC_POSITION               0x00000007
#define _BR3_FC_MASK                   0x0000000F
#define _BR3_FC_LENGTH                 0x00000004

#define _BR3_TRLXQ_POSITION            0x00000006
#define _BR3_TRLXQ_MASK                0x00000001
#define _BR3_TRLXQ_LENGTH              0x00000001

#define _BR3_BACK40_POSITION           0x00000005
#define _BR3_BACK40_MASK               0x00000001
#define _BR3_BACK40_LENGTH             0x00000001

#define _BR3_CSNT40_POSITION           0x00000004
#define _BR3_CSNT40_MASK               0x00000001
#define _BR3_CSNT40_LENGTH             0x00000001

#define _BR3_CSNTQ_POSITION            0x00000003
#define _BR3_CSNTQ_MASK                0x00000001
#define _BR3_CSNTQ_LENGTH              0x00000001

#define _BR3_PAREN_POSITION            0x00000002
#define _BR3_PAREN_MASK                0x00000001
#define _BR3_PAREN_LENGTH              0x00000001

#define _BR3_WP_POSITION               0x00000001
#define _BR3_WP_MASK                   0x00000001
#define _BR3_WP_LENGTH                 0x00000001

#define _BR3_V_POSITION                0x00000000
#define _BR3_V_MASK                    0x00000001
#define _BR3_V_LENGTH                  0x00000001

#define _BR4_BA31_POSITION             0x0000001F
#define _BR4_BA31_MASK                 0x00000001
#define _BR4_BA31_LENGTH               0x00000001

#define _BR4_BA30_POSITION             0x0000001E
#define _BR4_BA30_MASK                 0x00000001
#define _BR4_BA30_LENGTH               0x00000001

#define _BR4_BA29_POSITION             0x0000001D
#define _BR4_BA29_MASK                 0x00000001
#define _BR4_BA29_LENGTH               0x00000001

#define _BR4_BA28_POSITION             0x0000001C
#define _BR4_BA28_MASK                 0x00000001
#define _BR4_BA28_LENGTH               0x00000001

#define _BR4_BA27_POSITION             0x0000001B
#define _BR4_BA27_MASK                 0x00000001
#define _BR4_BA27_LENGTH               0x00000001

#define _BR4_BA26_POSITION             0x0000001A
#define _BR4_BA26_MASK                 0x00000001
#define _BR4_BA26_LENGTH               0x00000001

#define _BR4_BA25_POSITION             0x00000019
#define _BR4_BA25_MASK                 0x00000001
#define _BR4_BA25_LENGTH               0x00000001

#define _BR4_BA24_POSITION             0x00000018
#define _BR4_BA24_MASK                 0x00000001
#define _BR4_BA24_LENGTH               0x00000001

#define _BR4_BA23_POSITION             0x00000017
#define _BR4_BA23_MASK                 0x00000001
#define _BR4_BA23_LENGTH               0x00000001

#define _BR4_BA22_POSITION             0x00000016
#define _BR4_BA22_MASK                 0x00000001
#define _BR4_BA22_LENGTH               0x00000001

#define _BR4_BA21_POSITION             0x00000015
#define _BR4_BA21_MASK                 0x00000001
#define _BR4_BA21_LENGTH               0x00000001

#define _BR4_BA20_POSITION             0x00000014
#define _BR4_BA20_MASK                 0x00000001
#define _BR4_BA20_LENGTH               0x00000001

#define _BR4_BA19_POSITION             0x00000013
#define _BR4_BA19_MASK                 0x00000001
#define _BR4_BA19_LENGTH               0x00000001

#define _BR4_BA18_POSITION             0x00000012
#define _BR4_BA18_MASK                 0x00000001
#define _BR4_BA18_LENGTH               0x00000001

#define _BR4_BA17_POSITION             0x00000011
#define _BR4_BA17_MASK                 0x00000001
#define _BR4_BA17_LENGTH               0x00000001

#define _BR4_BA16_POSITION             0x00000010
#define _BR4_BA16_MASK                 0x00000001
#define _BR4_BA16_LENGTH               0x00000001

#define _BR4_BA15_POSITION             0x0000000F
#define _BR4_BA15_MASK                 0x00000001
#define _BR4_BA15_LENGTH               0x00000001

#define _BR4_BA14_POSITION             0x0000000E
#define _BR4_BA14_MASK                 0x00000001
#define _BR4_BA14_LENGTH               0x00000001

#define _BR4_BA13_POSITION             0x0000000D
#define _BR4_BA13_MASK                 0x00000001
#define _BR4_BA13_LENGTH               0x00000001

#define _BR4_BA12_POSITION             0x0000000C
#define _BR4_BA12_MASK                 0x00000001
#define _BR4_BA12_LENGTH               0x00000001

#define _BR4_BA11_POSITION             0x0000000B
#define _BR4_BA11_MASK                 0x00000001
#define _BR4_BA11_LENGTH               0x00000001

#define _BR4_BA_POSITION               0x0000000B
#define _BR4_BA_MASK                   0x001FFFFF
#define _BR4_BA_LENGTH                 0x00000015

#define _BR4_FC3_POSITION              0x0000000A
#define _BR4_FC3_MASK                  0x00000001
#define _BR4_FC3_LENGTH                0x00000001

#define _BR4_FC2_POSITION              0x00000009
#define _BR4_FC2_MASK                  0x00000001
#define _BR4_FC2_LENGTH                0x00000001

#define _BR4_FC1_POSITION              0x00000008
#define _BR4_FC1_MASK                  0x00000001
#define _BR4_FC1_LENGTH                0x00000001

#define _BR4_FC0_POSITION              0x00000007
#define _BR4_FC0_MASK                  0x00000001
#define _BR4_FC0_LENGTH                0x00000001

#define _BR4_FC_POSITION               0x00000007
#define _BR4_FC_MASK                   0x0000000F
#define _BR4_FC_LENGTH                 0x00000004

#define _BR4_TRLXQ_POSITION            0x00000006
#define _BR4_TRLXQ_MASK                0x00000001
#define _BR4_TRLXQ_LENGTH              0x00000001

#define _BR4_BACK40_POSITION           0x00000005
#define _BR4_BACK40_MASK               0x00000001
#define _BR4_BACK40_LENGTH             0x00000001

#define _BR4_CSNT40_POSITION           0x00000004
#define _BR4_CSNT40_MASK               0x00000001
#define _BR4_CSNT40_LENGTH             0x00000001

#define _BR4_CSNTQ_POSITION            0x00000003
#define _BR4_CSNTQ_MASK                0x00000001
#define _BR4_CSNTQ_LENGTH              0x00000001

#define _BR4_PAREN_POSITION            0x00000002
#define _BR4_PAREN_MASK                0x00000001
#define _BR4_PAREN_LENGTH              0x00000001

#define _BR4_WP_POSITION               0x00000001
#define _BR4_WP_MASK                   0x00000001
#define _BR4_WP_LENGTH                 0x00000001

#define _BR4_V_POSITION                0x00000000
#define _BR4_V_MASK                    0x00000001
#define _BR4_V_LENGTH                  0x00000001

#define _BR5_BA31_POSITION             0x0000001F
#define _BR5_BA31_MASK                 0x00000001
#define _BR5_BA31_LENGTH               0x00000001

#define _BR5_BA30_POSITION             0x0000001E
#define _BR5_BA30_MASK                 0x00000001
#define _BR5_BA30_LENGTH               0x00000001

#define _BR5_BA29_POSITION             0x0000001D
#define _BR5_BA29_MASK                 0x00000001
#define _BR5_BA29_LENGTH               0x00000001

#define _BR5_BA28_POSITION             0x0000001C
#define _BR5_BA28_MASK                 0x00000001
#define _BR5_BA28_LENGTH               0x00000001

#define _BR5_BA27_POSITION             0x0000001B
#define _BR5_BA27_MASK                 0x00000001
#define _BR5_BA27_LENGTH               0x00000001

#define _BR5_BA26_POSITION             0x0000001A
#define _BR5_BA26_MASK                 0x00000001
#define _BR5_BA26_LENGTH               0x00000001

#define _BR5_BA25_POSITION             0x00000019
#define _BR5_BA25_MASK                 0x00000001
#define _BR5_BA25_LENGTH               0x00000001

#define _BR5_BA24_POSITION             0x00000018
#define _BR5_BA24_MASK                 0x00000001
#define _BR5_BA24_LENGTH               0x00000001

#define _BR5_BA23_POSITION             0x00000017
#define _BR5_BA23_MASK                 0x00000001
#define _BR5_BA23_LENGTH               0x00000001

#define _BR5_BA22_POSITION             0x00000016
#define _BR5_BA22_MASK                 0x00000001
#define _BR5_BA22_LENGTH               0x00000001

#define _BR5_BA21_POSITION             0x00000015
#define _BR5_BA21_MASK                 0x00000001
#define _BR5_BA21_LENGTH               0x00000001

#define _BR5_BA20_POSITION             0x00000014
#define _BR5_BA20_MASK                 0x00000001
#define _BR5_BA20_LENGTH               0x00000001

#define _BR5_BA19_POSITION             0x00000013
#define _BR5_BA19_MASK                 0x00000001
#define _BR5_BA19_LENGTH               0x00000001

#define _BR5_BA18_POSITION             0x00000012
#define _BR5_BA18_MASK                 0x00000001
#define _BR5_BA18_LENGTH               0x00000001

#define _BR5_BA17_POSITION             0x00000011
#define _BR5_BA17_MASK                 0x00000001
#define _BR5_BA17_LENGTH               0x00000001

#define _BR5_BA16_POSITION             0x00000010
#define _BR5_BA16_MASK                 0x00000001
#define _BR5_BA16_LENGTH               0x00000001

#define _BR5_BA15_POSITION             0x0000000F
#define _BR5_BA15_MASK                 0x00000001
#define _BR5_BA15_LENGTH               0x00000001

#define _BR5_BA14_POSITION             0x0000000E
#define _BR5_BA14_MASK                 0x00000001
#define _BR5_BA14_LENGTH               0x00000001

#define _BR5_BA13_POSITION             0x0000000D
#define _BR5_BA13_MASK                 0x00000001
#define _BR5_BA13_LENGTH               0x00000001

#define _BR5_BA12_POSITION             0x0000000C
#define _BR5_BA12_MASK                 0x00000001
#define _BR5_BA12_LENGTH               0x00000001

#define _BR5_BA11_POSITION             0x0000000B
#define _BR5_BA11_MASK                 0x00000001
#define _BR5_BA11_LENGTH               0x00000001

#define _BR5_BA_POSITION               0x0000000B
#define _BR5_BA_MASK                   0x001FFFFF
#define _BR5_BA_LENGTH                 0x00000015

#define _BR5_FC3_POSITION              0x0000000A
#define _BR5_FC3_MASK                  0x00000001
#define _BR5_FC3_LENGTH                0x00000001

#define _BR5_FC2_POSITION              0x00000009
#define _BR5_FC2_MASK                  0x00000001
#define _BR5_FC2_LENGTH                0x00000001

#define _BR5_FC1_POSITION              0x00000008
#define _BR5_FC1_MASK                  0x00000001
#define _BR5_FC1_LENGTH                0x00000001

#define _BR5_FC0_POSITION              0x00000007
#define _BR5_FC0_MASK                  0x00000001
#define _BR5_FC0_LENGTH                0x00000001

#define _BR5_FC_POSITION               0x00000007
#define _BR5_FC_MASK                   0x0000000F
#define _BR5_FC_LENGTH                 0x00000004

#define _BR5_TRLXQ_POSITION            0x00000006
#define _BR5_TRLXQ_MASK                0x00000001
#define _BR5_TRLXQ_LENGTH              0x00000001

#define _BR5_BACK40_POSITION           0x00000005
#define _BR5_BACK40_MASK               0x00000001
#define _BR5_BACK40_LENGTH             0x00000001

#define _BR5_CSNT40_POSITION           0x00000004
#define _BR5_CSNT40_MASK               0x00000001
#define _BR5_CSNT40_LENGTH             0x00000001

#define _BR5_CSNTQ_POSITION            0x00000003
#define _BR5_CSNTQ_MASK                0x00000001
#define _BR5_CSNTQ_LENGTH              0x00000001

#define _BR5_PAREN_POSITION            0x00000002
#define _BR5_PAREN_MASK                0x00000001
#define _BR5_PAREN_LENGTH              0x00000001

#define _BR5_WP_POSITION               0x00000001
#define _BR5_WP_MASK                   0x00000001
#define _BR5_WP_LENGTH                 0x00000001

#define _BR5_V_POSITION                0x00000000
#define _BR5_V_MASK                    0x00000001
#define _BR5_V_LENGTH                  0x00000001

#define _BR6_BA31_POSITION             0x0000001F
#define _BR6_BA31_MASK                 0x00000001
#define _BR6_BA31_LENGTH               0x00000001

#define _BR6_BA30_POSITION             0x0000001E
#define _BR6_BA30_MASK                 0x00000001
#define _BR6_BA30_LENGTH               0x00000001

#define _BR6_BA29_POSITION             0x0000001D
#define _BR6_BA29_MASK                 0x00000001
#define _BR6_BA29_LENGTH               0x00000001

#define _BR6_BA28_POSITION             0x0000001C
#define _BR6_BA28_MASK                 0x00000001
#define _BR6_BA28_LENGTH               0x00000001

#define _BR6_BA27_POSITION             0x0000001B
#define _BR6_BA27_MASK                 0x00000001
#define _BR6_BA27_LENGTH               0x00000001

#define _BR6_BA26_POSITION             0x0000001A
#define _BR6_BA26_MASK                 0x00000001
#define _BR6_BA26_LENGTH               0x00000001

#define _BR6_BA25_POSITION             0x00000019
#define _BR6_BA25_MASK                 0x00000001
#define _BR6_BA25_LENGTH               0x00000001

#define _BR6_BA24_POSITION             0x00000018
#define _BR6_BA24_MASK                 0x00000001
#define _BR6_BA24_LENGTH               0x00000001

#define _BR6_BA23_POSITION             0x00000017
#define _BR6_BA23_MASK                 0x00000001
#define _BR6_BA23_LENGTH               0x00000001

#define _BR6_BA22_POSITION             0x00000016
#define _BR6_BA22_MASK                 0x00000001
#define _BR6_BA22_LENGTH               0x00000001

#define _BR6_BA21_POSITION             0x00000015
#define _BR6_BA21_MASK                 0x00000001
#define _BR6_BA21_LENGTH               0x00000001

#define _BR6_BA20_POSITION             0x00000014
#define _BR6_BA20_MASK                 0x00000001
#define _BR6_BA20_LENGTH               0x00000001

#define _BR6_BA19_POSITION             0x00000013
#define _BR6_BA19_MASK                 0x00000001
#define _BR6_BA19_LENGTH               0x00000001

#define _BR6_BA18_POSITION             0x00000012
#define _BR6_BA18_MASK                 0x00000001
#define _BR6_BA18_LENGTH               0x00000001

#define _BR6_BA17_POSITION             0x00000011
#define _BR6_BA17_MASK                 0x00000001
#define _BR6_BA17_LENGTH               0x00000001

#define _BR6_BA16_POSITION             0x00000010
#define _BR6_BA16_MASK                 0x00000001
#define _BR6_BA16_LENGTH               0x00000001

#define _BR6_BA15_POSITION             0x0000000F
#define _BR6_BA15_MASK                 0x00000001
#define _BR6_BA15_LENGTH               0x00000001

#define _BR6_BA14_POSITION             0x0000000E
#define _BR6_BA14_MASK                 0x00000001
#define _BR6_BA14_LENGTH               0x00000001

#define _BR6_BA13_POSITION             0x0000000D
#define _BR6_BA13_MASK                 0x00000001
#define _BR6_BA13_LENGTH               0x00000001

#define _BR6_BA12_POSITION             0x0000000C
#define _BR6_BA12_MASK                 0x00000001
#define _BR6_BA12_LENGTH               0x00000001

#define _BR6_BA11_POSITION             0x0000000B
#define _BR6_BA11_MASK                 0x00000001
#define _BR6_BA11_LENGTH               0x00000001

#define _BR6_BA_POSITION               0x0000000B
#define _BR6_BA_MASK                   0x001FFFFF
#define _BR6_BA_LENGTH                 0x00000015

#define _BR6_FC3_POSITION              0x0000000A
#define _BR6_FC3_MASK                  0x00000001
#define _BR6_FC3_LENGTH                0x00000001

#define _BR6_FC2_POSITION              0x00000009
#define _BR6_FC2_MASK                  0x00000001
#define _BR6_FC2_LENGTH                0x00000001

#define _BR6_FC1_POSITION              0x00000008
#define _BR6_FC1_MASK                  0x00000001
#define _BR6_FC1_LENGTH                0x00000001

#define _BR6_FC0_POSITION              0x00000007
#define _BR6_FC0_MASK                  0x00000001
#define _BR6_FC0_LENGTH                0x00000001

#define _BR6_FC_POSITION               0x00000007
#define _BR6_FC_MASK                   0x0000000F
#define _BR6_FC_LENGTH                 0x00000004

#define _BR6_TRLXQ_POSITION            0x00000006
#define _BR6_TRLXQ_MASK                0x00000001
#define _BR6_TRLXQ_LENGTH              0x00000001

#define _BR6_BACK40_POSITION           0x00000005
#define _BR6_BACK40_MASK               0x00000001
#define _BR6_BACK40_LENGTH             0x00000001

#define _BR6_CSNT40_POSITION           0x00000004
#define _BR6_CSNT40_MASK               0x00000001
#define _BR6_CSNT40_LENGTH             0x00000001

#define _BR6_CSNTQ_POSITION            0x00000003
#define _BR6_CSNTQ_MASK                0x00000001
#define _BR6_CSNTQ_LENGTH              0x00000001

#define _BR6_PAREN_POSITION            0x00000002
#define _BR6_PAREN_MASK                0x00000001
#define _BR6_PAREN_LENGTH              0x00000001

#define _BR6_WP_POSITION               0x00000001
#define _BR6_WP_MASK                   0x00000001
#define _BR6_WP_LENGTH                 0x00000001

#define _BR6_V_POSITION                0x00000000
#define _BR6_V_MASK                    0x00000001
#define _BR6_V_LENGTH                  0x00000001

#define _BR7_BA31_POSITION             0x0000001F
#define _BR7_BA31_MASK                 0x00000001
#define _BR7_BA31_LENGTH               0x00000001

#define _BR7_BA30_POSITION             0x0000001E
#define _BR7_BA30_MASK                 0x00000001
#define _BR7_BA30_LENGTH               0x00000001

#define _BR7_BA29_POSITION             0x0000001D
#define _BR7_BA29_MASK                 0x00000001
#define _BR7_BA29_LENGTH               0x00000001

#define _BR7_BA28_POSITION             0x0000001C
#define _BR7_BA28_MASK                 0x00000001
#define _BR7_BA28_LENGTH               0x00000001

#define _BR7_BA27_POSITION             0x0000001B
#define _BR7_BA27_MASK                 0x00000001
#define _BR7_BA27_LENGTH               0x00000001

#define _BR7_BA26_POSITION             0x0000001A
#define _BR7_BA26_MASK                 0x00000001
#define _BR7_BA26_LENGTH               0x00000001

#define _BR7_BA25_POSITION             0x00000019
#define _BR7_BA25_MASK                 0x00000001
#define _BR7_BA25_LENGTH               0x00000001

#define _BR7_BA24_POSITION             0x00000018
#define _BR7_BA24_MASK                 0x00000001
#define _BR7_BA24_LENGTH               0x00000001

#define _BR7_BA23_POSITION             0x00000017
#define _BR7_BA23_MASK                 0x00000001
#define _BR7_BA23_LENGTH               0x00000001

#define _BR7_BA22_POSITION             0x00000016
#define _BR7_BA22_MASK                 0x00000001
#define _BR7_BA22_LENGTH               0x00000001

#define _BR7_BA21_POSITION             0x00000015
#define _BR7_BA21_MASK                 0x00000001
#define _BR7_BA21_LENGTH               0x00000001

#define _BR7_BA20_POSITION             0x00000014
#define _BR7_BA20_MASK                 0x00000001
#define _BR7_BA20_LENGTH               0x00000001

#define _BR7_BA19_POSITION             0x00000013
#define _BR7_BA19_MASK                 0x00000001
#define _BR7_BA19_LENGTH               0x00000001

#define _BR7_BA18_POSITION             0x00000012
#define _BR7_BA18_MASK                 0x00000001
#define _BR7_BA18_LENGTH               0x00000001

#define _BR7_BA17_POSITION             0x00000011
#define _BR7_BA17_MASK                 0x00000001
#define _BR7_BA17_LENGTH               0x00000001

#define _BR7_BA16_POSITION             0x00000010
#define _BR7_BA16_MASK                 0x00000001
#define _BR7_BA16_LENGTH               0x00000001

#define _BR7_BA15_POSITION             0x0000000F
#define _BR7_BA15_MASK                 0x00000001
#define _BR7_BA15_LENGTH               0x00000001

#define _BR7_BA14_POSITION             0x0000000E
#define _BR7_BA14_MASK                 0x00000001
#define _BR7_BA14_LENGTH               0x00000001

#define _BR7_BA13_POSITION             0x0000000D
#define _BR7_BA13_MASK                 0x00000001
#define _BR7_BA13_LENGTH               0x00000001

#define _BR7_BA12_POSITION             0x0000000C
#define _BR7_BA12_MASK                 0x00000001
#define _BR7_BA12_LENGTH               0x00000001

#define _BR7_BA11_POSITION             0x0000000B
#define _BR7_BA11_MASK                 0x00000001
#define _BR7_BA11_LENGTH               0x00000001

#define _BR7_BA_POSITION               0x0000000B
#define _BR7_BA_MASK                   0x001FFFFF
#define _BR7_BA_LENGTH                 0x00000015

#define _BR7_FC3_POSITION              0x0000000A
#define _BR7_FC3_MASK                  0x00000001
#define _BR7_FC3_LENGTH                0x00000001

#define _BR7_FC2_POSITION              0x00000009
#define _BR7_FC2_MASK                  0x00000001
#define _BR7_FC2_LENGTH                0x00000001

#define _BR7_FC1_POSITION              0x00000008
#define _BR7_FC1_MASK                  0x00000001
#define _BR7_FC1_LENGTH                0x00000001

#define _BR7_FC0_POSITION              0x00000007
#define _BR7_FC0_MASK                  0x00000001
#define _BR7_FC0_LENGTH                0x00000001

#define _BR7_FC_POSITION               0x00000007
#define _BR7_FC_MASK                   0x0000000F
#define _BR7_FC_LENGTH                 0x00000004

#define _BR7_TRLXQ_POSITION            0x00000006
#define _BR7_TRLXQ_MASK                0x00000001
#define _BR7_TRLXQ_LENGTH              0x00000001

#define _BR7_BACK40_POSITION           0x00000005
#define _BR7_BACK40_MASK               0x00000001
#define _BR7_BACK40_LENGTH             0x00000001

#define _BR7_CSNT40_POSITION           0x00000004
#define _BR7_CSNT40_MASK               0x00000001
#define _BR7_CSNT40_LENGTH             0x00000001

#define _BR7_CSNTQ_POSITION            0x00000003
#define _BR7_CSNTQ_MASK                0x00000001
#define _BR7_CSNTQ_LENGTH              0x00000001

#define _BR7_PAREN_POSITION            0x00000002
#define _BR7_PAREN_MASK                0x00000001
#define _BR7_PAREN_LENGTH              0x00000001

#define _BR7_WP_POSITION               0x00000001
#define _BR7_WP_MASK                   0x00000001
#define _BR7_WP_LENGTH                 0x00000001

#define _BR7_V_POSITION                0x00000000
#define _BR7_V_MASK                    0x00000001
#define _BR7_V_LENGTH                  0x00000001

#define _OR0_TCYC3_POSITION            0x0000001F
#define _OR0_TCYC3_MASK                0x00000001
#define _OR0_TCYC3_LENGTH              0x00000001

#define _OR0_TCYC2_POSITION            0x0000001E
#define _OR0_TCYC2_MASK                0x00000001
#define _OR0_TCYC2_LENGTH              0x00000001

#define _OR0_TCYC1_POSITION            0x0000001D
#define _OR0_TCYC1_MASK                0x00000001
#define _OR0_TCYC1_LENGTH              0x00000001

#define _OR0_TCYC0_POSITION            0x0000001C
#define _OR0_TCYC0_MASK                0x00000001
#define _OR0_TCYC0_LENGTH              0x00000001

#define _OR0_TCYC_POSITION             0x0000001C
#define _OR0_TCYC_MASK                 0x0000000F
#define _OR0_TCYC_LENGTH               0x00000004

#define _OR0_AM27_POSITION             0x0000001B
#define _OR0_AM27_MASK                 0x00000001
#define _OR0_AM27_LENGTH               0x00000001

#define _OR0_AM26_POSITION             0x0000001A
#define _OR0_AM26_MASK                 0x00000001
#define _OR0_AM26_LENGTH               0x00000001

#define _OR0_AM25_POSITION             0x00000019
#define _OR0_AM25_MASK                 0x00000001
#define _OR0_AM25_LENGTH               0x00000001

#define _OR0_AM24_POSITION             0x00000018
#define _OR0_AM24_MASK                 0x00000001
#define _OR0_AM24_LENGTH               0x00000001

#define _OR0_AM23_POSITION             0x00000017
#define _OR0_AM23_MASK                 0x00000001
#define _OR0_AM23_LENGTH               0x00000001

#define _OR0_AM22_POSITION             0x00000016
#define _OR0_AM22_MASK                 0x00000001
#define _OR0_AM22_LENGTH               0x00000001

#define _OR0_AM21_POSITION             0x00000015
#define _OR0_AM21_MASK                 0x00000001
#define _OR0_AM21_LENGTH               0x00000001

#define _OR0_AM20_POSITION             0x00000014
#define _OR0_AM20_MASK                 0x00000001
#define _OR0_AM20_LENGTH               0x00000001

#define _OR0_AM19_POSITION             0x00000013
#define _OR0_AM19_MASK                 0x00000001
#define _OR0_AM19_LENGTH               0x00000001

#define _OR0_AM18_POSITION             0x00000012
#define _OR0_AM18_MASK                 0x00000001
#define _OR0_AM18_LENGTH               0x00000001

#define _OR0_AM17_POSITION             0x00000011
#define _OR0_AM17_MASK                 0x00000001
#define _OR0_AM17_LENGTH               0x00000001

#define _OR0_AM16_POSITION             0x00000010
#define _OR0_AM16_MASK                 0x00000001
#define _OR0_AM16_LENGTH               0x00000001

#define _OR0_AM15_POSITION             0x0000000F
#define _OR0_AM15_MASK                 0x00000001
#define _OR0_AM15_LENGTH               0x00000001

#define _OR0_AM14_POSITION             0x0000000E
#define _OR0_AM14_MASK                 0x00000001
#define _OR0_AM14_LENGTH               0x00000001

#define _OR0_AM13_POSITION             0x0000000D
#define _OR0_AM13_MASK                 0x00000001
#define _OR0_AM13_LENGTH               0x00000001

#define _OR0_AM12_POSITION             0x0000000C
#define _OR0_AM12_MASK                 0x00000001
#define _OR0_AM12_LENGTH               0x00000001

#define _OR0_AM11_POSITION             0x0000000B
#define _OR0_AM11_MASK                 0x00000001
#define _OR0_AM11_LENGTH               0x00000001

#define _OR0_AM_POSITION               0x0000000B
#define _OR0_AM_MASK                   0x0001FFFF
#define _OR0_AM_LENGTH                 0x00000011

#define _OR0_FCM3_POSITION             0x0000000A
#define _OR0_FCM3_MASK                 0x00000001
#define _OR0_FCM3_LENGTH               0x00000001

#define _OR0_FCM2_POSITION             0x00000009
#define _OR0_FCM2_MASK                 0x00000001
#define _OR0_FCM2_LENGTH               0x00000001

#define _OR0_FCM1_POSITION             0x00000008
#define _OR0_FCM1_MASK                 0x00000001
#define _OR0_FCM1_LENGTH               0x00000001

#define _OR0_FCM0_POSITION             0x00000007
#define _OR0_FCM0_MASK                 0x00000001
#define _OR0_FCM0_LENGTH               0x00000001

#define _OR0_FCM_POSITION              0x00000007
#define _OR0_FCM_MASK                  0x0000000F
#define _OR0_FCM_LENGTH                0x00000004

#define _OR0_BCYC1_POSITION            0x00000006
#define _OR0_BCYC1_MASK                0x00000001
#define _OR0_BCYC1_LENGTH              0x00000001

#define _OR0_BCYC0_POSITION            0x00000005
#define _OR0_BCYC0_MASK                0x00000001
#define _OR0_BCYC0_LENGTH              0x00000001

#define _OR0_BCYC_POSITION             0x00000005
#define _OR0_BCYC_MASK                 0x00000003
#define _OR0_BCYC_LENGTH               0x00000002

#define _OR0_PGME_POSITION             0x00000003
#define _OR0_PGME_MASK                 0x00000001
#define _OR0_PGME_LENGTH               0x00000001

#define _OR0_SPS1_POSITION             0x00000002
#define _OR0_SPS1_MASK                 0x00000001
#define _OR0_SPS1_LENGTH               0x00000001

#define _OR0_SPS0_POSITION             0x00000001
#define _OR0_SPS0_MASK                 0x00000001
#define _OR0_SPS0_LENGTH               0x00000001

#define _OR0_SPS_POSITION              0x00000001
#define _OR0_SPS_MASK                  0x00000003
#define _OR0_SPS_LENGTH                0x00000002

#define _OR0_DSSEL_POSITION            0x00000000
#define _OR0_DSSEL_MASK                0x00000001
#define _OR0_DSSEL_LENGTH              0x00000001

#define _OR1_TCYC3_POSITION            0x0000001F
#define _OR1_TCYC3_MASK                0x00000001
#define _OR1_TCYC3_LENGTH              0x00000001

#define _OR1_TCYC2_POSITION            0x0000001E
#define _OR1_TCYC2_MASK                0x00000001
#define _OR1_TCYC2_LENGTH              0x00000001

#define _OR1_TCYC1_POSITION            0x0000001D
#define _OR1_TCYC1_MASK                0x00000001
#define _OR1_TCYC1_LENGTH              0x00000001

#define _OR1_TCYC0_POSITION            0x0000001C
#define _OR1_TCYC0_MASK                0x00000001
#define _OR1_TCYC0_LENGTH              0x00000001

#define _OR1_TCYC_POSITION             0x0000001C
#define _OR1_TCYC_MASK                 0x0000000F
#define _OR1_TCYC_LENGTH               0x00000004

#define _OR1_AM27_POSITION             0x0000001B
#define _OR1_AM27_MASK                 0x00000001
#define _OR1_AM27_LENGTH               0x00000001

#define _OR1_AM26_POSITION             0x0000001A
#define _OR1_AM26_MASK                 0x00000001
#define _OR1_AM26_LENGTH               0x00000001

#define _OR1_AM25_POSITION             0x00000019
#define _OR1_AM25_MASK                 0x00000001
#define _OR1_AM25_LENGTH               0x00000001

#define _OR1_AM24_POSITION             0x00000018
#define _OR1_AM24_MASK                 0x00000001
#define _OR1_AM24_LENGTH               0x00000001

#define _OR1_AM23_POSITION             0x00000017
#define _OR1_AM23_MASK                 0x00000001
#define _OR1_AM23_LENGTH               0x00000001

#define _OR1_AM22_POSITION             0x00000016
#define _OR1_AM22_MASK                 0x00000001
#define _OR1_AM22_LENGTH               0x00000001

#define _OR1_AM21_POSITION             0x00000015
#define _OR1_AM21_MASK                 0x00000001
#define _OR1_AM21_LENGTH               0x00000001

#define _OR1_AM20_POSITION             0x00000014
#define _OR1_AM20_MASK                 0x00000001
#define _OR1_AM20_LENGTH               0x00000001

#define _OR1_AM19_POSITION             0x00000013
#define _OR1_AM19_MASK                 0x00000001
#define _OR1_AM19_LENGTH               0x00000001

#define _OR1_AM18_POSITION             0x00000012
#define _OR1_AM18_MASK                 0x00000001
#define _OR1_AM18_LENGTH               0x00000001

#define _OR1_AM17_POSITION             0x00000011
#define _OR1_AM17_MASK                 0x00000001
#define _OR1_AM17_LENGTH               0x00000001

#define _OR1_AM16_POSITION             0x00000010
#define _OR1_AM16_MASK                 0x00000001
#define _OR1_AM16_LENGTH               0x00000001

#define _OR1_AM15_POSITION             0x0000000F
#define _OR1_AM15_MASK                 0x00000001
#define _OR1_AM15_LENGTH               0x00000001

#define _OR1_AM14_POSITION             0x0000000E
#define _OR1_AM14_MASK                 0x00000001
#define _OR1_AM14_LENGTH               0x00000001

#define _OR1_AM13_POSITION             0x0000000D
#define _OR1_AM13_MASK                 0x00000001
#define _OR1_AM13_LENGTH               0x00000001

#define _OR1_AM12_POSITION             0x0000000C
#define _OR1_AM12_MASK                 0x00000001
#define _OR1_AM12_LENGTH               0x00000001

#define _OR1_AM11_POSITION             0x0000000B
#define _OR1_AM11_MASK                 0x00000001
#define _OR1_AM11_LENGTH               0x00000001

#define _OR1_AM_POSITION               0x0000000B
#define _OR1_AM_MASK                   0x0001FFFF
#define _OR1_AM_LENGTH                 0x00000011

#define _OR1_FCM3_POSITION             0x0000000A
#define _OR1_FCM3_MASK                 0x00000001
#define _OR1_FCM3_LENGTH               0x00000001

#define _OR1_FCM2_POSITION             0x00000009
#define _OR1_FCM2_MASK                 0x00000001
#define _OR1_FCM2_LENGTH               0x00000001

#define _OR1_FCM1_POSITION             0x00000008
#define _OR1_FCM1_MASK                 0x00000001
#define _OR1_FCM1_LENGTH               0x00000001

#define _OR1_FCM0_POSITION             0x00000007
#define _OR1_FCM0_MASK                 0x00000001
#define _OR1_FCM0_LENGTH               0x00000001

#define _OR1_FCM_POSITION              0x00000007
#define _OR1_FCM_MASK                  0x0000000F
#define _OR1_FCM_LENGTH                0x00000004

#define _OR1_BCYC1_POSITION            0x00000006
#define _OR1_BCYC1_MASK                0x00000001
#define _OR1_BCYC1_LENGTH              0x00000001

#define _OR1_BCYC0_POSITION            0x00000005
#define _OR1_BCYC0_MASK                0x00000001
#define _OR1_BCYC0_LENGTH              0x00000001

#define _OR1_BCYC_POSITION             0x00000005
#define _OR1_BCYC_MASK                 0x00000003
#define _OR1_BCYC_LENGTH               0x00000002

#define _OR1_PGME_POSITION             0x00000003
#define _OR1_PGME_MASK                 0x00000001
#define _OR1_PGME_LENGTH               0x00000001

#define _OR1_SPS1_POSITION             0x00000002
#define _OR1_SPS1_MASK                 0x00000001
#define _OR1_SPS1_LENGTH               0x00000001

#define _OR1_SPS0_POSITION             0x00000001
#define _OR1_SPS0_MASK                 0x00000001
#define _OR1_SPS0_LENGTH               0x00000001

#define _OR1_SPS_POSITION              0x00000001
#define _OR1_SPS_MASK                  0x00000003
#define _OR1_SPS_LENGTH                0x00000002

#define _OR1_DSSEL_POSITION            0x00000000
#define _OR1_DSSEL_MASK                0x00000001
#define _OR1_DSSEL_LENGTH              0x00000001

#define _OR2_TCYC3_POSITION            0x0000001F
#define _OR2_TCYC3_MASK                0x00000001
#define _OR2_TCYC3_LENGTH              0x00000001

#define _OR2_TCYC2_POSITION            0x0000001E
#define _OR2_TCYC2_MASK                0x00000001
#define _OR2_TCYC2_LENGTH              0x00000001

#define _OR2_TCYC1_POSITION            0x0000001D
#define _OR2_TCYC1_MASK                0x00000001
#define _OR2_TCYC1_LENGTH              0x00000001

#define _OR2_TCYC0_POSITION            0x0000001C
#define _OR2_TCYC0_MASK                0x00000001
#define _OR2_TCYC0_LENGTH              0x00000001

#define _OR2_TCYC_POSITION             0x0000001C
#define _OR2_TCYC_MASK                 0x0000000F
#define _OR2_TCYC_LENGTH               0x00000004

#define _OR2_AM27_POSITION             0x0000001B
#define _OR2_AM27_MASK                 0x00000001
#define _OR2_AM27_LENGTH               0x00000001

#define _OR2_AM26_POSITION             0x0000001A
#define _OR2_AM26_MASK                 0x00000001
#define _OR2_AM26_LENGTH               0x00000001

#define _OR2_AM25_POSITION             0x00000019
#define _OR2_AM25_MASK                 0x00000001
#define _OR2_AM25_LENGTH               0x00000001

#define _OR2_AM24_POSITION             0x00000018
#define _OR2_AM24_MASK                 0x00000001
#define _OR2_AM24_LENGTH               0x00000001

#define _OR2_AM23_POSITION             0x00000017
#define _OR2_AM23_MASK                 0x00000001
#define _OR2_AM23_LENGTH               0x00000001

#define _OR2_AM22_POSITION             0x00000016
#define _OR2_AM22_MASK                 0x00000001
#define _OR2_AM22_LENGTH               0x00000001

#define _OR2_AM21_POSITION             0x00000015
#define _OR2_AM21_MASK                 0x00000001
#define _OR2_AM21_LENGTH               0x00000001

#define _OR2_AM20_POSITION             0x00000014
#define _OR2_AM20_MASK                 0x00000001
#define _OR2_AM20_LENGTH               0x00000001

#define _OR2_AM19_POSITION             0x00000013
#define _OR2_AM19_MASK                 0x00000001
#define _OR2_AM19_LENGTH               0x00000001

#define _OR2_AM18_POSITION             0x00000012
#define _OR2_AM18_MASK                 0x00000001
#define _OR2_AM18_LENGTH               0x00000001

#define _OR2_AM17_POSITION             0x00000011
#define _OR2_AM17_MASK                 0x00000001
#define _OR2_AM17_LENGTH               0x00000001

#define _OR2_AM16_POSITION             0x00000010
#define _OR2_AM16_MASK                 0x00000001
#define _OR2_AM16_LENGTH               0x00000001

#define _OR2_AM15_POSITION             0x0000000F
#define _OR2_AM15_MASK                 0x00000001
#define _OR2_AM15_LENGTH               0x00000001

#define _OR2_AM14_POSITION             0x0000000E
#define _OR2_AM14_MASK                 0x00000001
#define _OR2_AM14_LENGTH               0x00000001

#define _OR2_AM13_POSITION             0x0000000D
#define _OR2_AM13_MASK                 0x00000001
#define _OR2_AM13_LENGTH               0x00000001

#define _OR2_AM12_POSITION             0x0000000C
#define _OR2_AM12_MASK                 0x00000001
#define _OR2_AM12_LENGTH               0x00000001

#define _OR2_AM11_POSITION             0x0000000B
#define _OR2_AM11_MASK                 0x00000001
#define _OR2_AM11_LENGTH               0x00000001

#define _OR2_AM_POSITION               0x0000000B
#define _OR2_AM_MASK                   0x0001FFFF
#define _OR2_AM_LENGTH                 0x00000011

#define _OR2_FCM3_POSITION             0x0000000A
#define _OR2_FCM3_MASK                 0x00000001
#define _OR2_FCM3_LENGTH               0x00000001

#define _OR2_FCM2_POSITION             0x00000009
#define _OR2_FCM2_MASK                 0x00000001
#define _OR2_FCM2_LENGTH               0x00000001

#define _OR2_FCM1_POSITION             0x00000008
#define _OR2_FCM1_MASK                 0x00000001
#define _OR2_FCM1_LENGTH               0x00000001

#define _OR2_FCM0_POSITION             0x00000007
#define _OR2_FCM0_MASK                 0x00000001
#define _OR2_FCM0_LENGTH               0x00000001

#define _OR2_FCM_POSITION              0x00000007
#define _OR2_FCM_MASK                  0x0000000F
#define _OR2_FCM_LENGTH                0x00000004

#define _OR2_BCYC1_POSITION            0x00000006
#define _OR2_BCYC1_MASK                0x00000001
#define _OR2_BCYC1_LENGTH              0x00000001

#define _OR2_BCYC0_POSITION            0x00000005
#define _OR2_BCYC0_MASK                0x00000001
#define _OR2_BCYC0_LENGTH              0x00000001

#define _OR2_BCYC_POSITION             0x00000005
#define _OR2_BCYC_MASK                 0x00000003
#define _OR2_BCYC_LENGTH               0x00000002

#define _OR2_PGME_POSITION             0x00000003
#define _OR2_PGME_MASK                 0x00000001
#define _OR2_PGME_LENGTH               0x00000001

#define _OR2_SPS1_POSITION             0x00000002
#define _OR2_SPS1_MASK                 0x00000001
#define _OR2_SPS1_LENGTH               0x00000001

#define _OR2_SPS0_POSITION             0x00000001
#define _OR2_SPS0_MASK                 0x00000001
#define _OR2_SPS0_LENGTH               0x00000001

#define _OR2_SPS_POSITION              0x00000001
#define _OR2_SPS_MASK                  0x00000003
#define _OR2_SPS_LENGTH                0x00000002

#define _OR2_DSSEL_POSITION            0x00000000
#define _OR2_DSSEL_MASK                0x00000001
#define _OR2_DSSEL_LENGTH              0x00000001

#define _OR3_TCYC3_POSITION            0x0000001F
#define _OR3_TCYC3_MASK                0x00000001
#define _OR3_TCYC3_LENGTH              0x00000001

#define _OR3_TCYC2_POSITION            0x0000001E
#define _OR3_TCYC2_MASK                0x00000001
#define _OR3_TCYC2_LENGTH              0x00000001

#define _OR3_TCYC1_POSITION            0x0000001D
#define _OR3_TCYC1_MASK                0x00000001
#define _OR3_TCYC1_LENGTH              0x00000001

#define _OR3_TCYC0_POSITION            0x0000001C
#define _OR3_TCYC0_MASK                0x00000001
#define _OR3_TCYC0_LENGTH              0x00000001

#define _OR3_TCYC_POSITION             0x0000001C
#define _OR3_TCYC_MASK                 0x0000000F
#define _OR3_TCYC_LENGTH               0x00000004

#define _OR3_AM27_POSITION             0x0000001B
#define _OR3_AM27_MASK                 0x00000001
#define _OR3_AM27_LENGTH               0x00000001

#define _OR3_AM26_POSITION             0x0000001A
#define _OR3_AM26_MASK                 0x00000001
#define _OR3_AM26_LENGTH               0x00000001

#define _OR3_AM25_POSITION             0x00000019
#define _OR3_AM25_MASK                 0x00000001
#define _OR3_AM25_LENGTH               0x00000001

#define _OR3_AM24_POSITION             0x00000018
#define _OR3_AM24_MASK                 0x00000001
#define _OR3_AM24_LENGTH               0x00000001

#define _OR3_AM23_POSITION             0x00000017
#define _OR3_AM23_MASK                 0x00000001
#define _OR3_AM23_LENGTH               0x00000001

#define _OR3_AM22_POSITION             0x00000016
#define _OR3_AM22_MASK                 0x00000001
#define _OR3_AM22_LENGTH               0x00000001

#define _OR3_AM21_POSITION             0x00000015
#define _OR3_AM21_MASK                 0x00000001
#define _OR3_AM21_LENGTH               0x00000001

#define _OR3_AM20_POSITION             0x00000014
#define _OR3_AM20_MASK                 0x00000001
#define _OR3_AM20_LENGTH               0x00000001

#define _OR3_AM19_POSITION             0x00000013
#define _OR3_AM19_MASK                 0x00000001
#define _OR3_AM19_LENGTH               0x00000001

#define _OR3_AM18_POSITION             0x00000012
#define _OR3_AM18_MASK                 0x00000001
#define _OR3_AM18_LENGTH               0x00000001

#define _OR3_AM17_POSITION             0x00000011
#define _OR3_AM17_MASK                 0x00000001
#define _OR3_AM17_LENGTH               0x00000001

#define _OR3_AM16_POSITION             0x00000010
#define _OR3_AM16_MASK                 0x00000001
#define _OR3_AM16_LENGTH               0x00000001

#define _OR3_AM15_POSITION             0x0000000F
#define _OR3_AM15_MASK                 0x00000001
#define _OR3_AM15_LENGTH               0x00000001

#define _OR3_AM14_POSITION             0x0000000E
#define _OR3_AM14_MASK                 0x00000001
#define _OR3_AM14_LENGTH               0x00000001

#define _OR3_AM13_POSITION             0x0000000D
#define _OR3_AM13_MASK                 0x00000001
#define _OR3_AM13_LENGTH               0x00000001

#define _OR3_AM12_POSITION             0x0000000C
#define _OR3_AM12_MASK                 0x00000001
#define _OR3_AM12_LENGTH               0x00000001

#define _OR3_AM11_POSITION             0x0000000B
#define _OR3_AM11_MASK                 0x00000001
#define _OR3_AM11_LENGTH               0x00000001

#define _OR3_AM_POSITION               0x0000000B
#define _OR3_AM_MASK                   0x0001FFFF
#define _OR3_AM_LENGTH                 0x00000011

#define _OR3_FCM3_POSITION             0x0000000A
#define _OR3_FCM3_MASK                 0x00000001
#define _OR3_FCM3_LENGTH               0x00000001

#define _OR3_FCM2_POSITION             0x00000009
#define _OR3_FCM2_MASK                 0x00000001
#define _OR3_FCM2_LENGTH               0x00000001

#define _OR3_FCM1_POSITION             0x00000008
#define _OR3_FCM1_MASK                 0x00000001
#define _OR3_FCM1_LENGTH               0x00000001

#define _OR3_FCM0_POSITION             0x00000007
#define _OR3_FCM0_MASK                 0x00000001
#define _OR3_FCM0_LENGTH               0x00000001

#define _OR3_FCM_POSITION              0x00000007
#define _OR3_FCM_MASK                  0x0000000F
#define _OR3_FCM_LENGTH                0x00000004

#define _OR3_BCYC1_POSITION            0x00000006
#define _OR3_BCYC1_MASK                0x00000001
#define _OR3_BCYC1_LENGTH              0x00000001

#define _OR3_BCYC0_POSITION            0x00000005
#define _OR3_BCYC0_MASK                0x00000001
#define _OR3_BCYC0_LENGTH              0x00000001

#define _OR3_BCYC_POSITION             0x00000005
#define _OR3_BCYC_MASK                 0x00000003
#define _OR3_BCYC_LENGTH               0x00000002

#define _OR3_PGME_POSITION             0x00000003
#define _OR3_PGME_MASK                 0x00000001
#define _OR3_PGME_LENGTH               0x00000001

#define _OR3_SPS1_POSITION             0x00000002
#define _OR3_SPS1_MASK                 0x00000001
#define _OR3_SPS1_LENGTH               0x00000001

#define _OR3_SPS0_POSITION             0x00000001
#define _OR3_SPS0_MASK                 0x00000001
#define _OR3_SPS0_LENGTH               0x00000001

#define _OR3_SPS_POSITION              0x00000001
#define _OR3_SPS_MASK                  0x00000003
#define _OR3_SPS_LENGTH                0x00000002

#define _OR3_DSSEL_POSITION            0x00000000
#define _OR3_DSSEL_MASK                0x00000001
#define _OR3_DSSEL_LENGTH              0x00000001

#define _OR4_TCYC3_POSITION            0x0000001F
#define _OR4_TCYC3_MASK                0x00000001
#define _OR4_TCYC3_LENGTH              0x00000001

#define _OR4_TCYC2_POSITION            0x0000001E
#define _OR4_TCYC2_MASK                0x00000001
#define _OR4_TCYC2_LENGTH              0x00000001

#define _OR4_TCYC1_POSITION            0x0000001D
#define _OR4_TCYC1_MASK                0x00000001
#define _OR4_TCYC1_LENGTH              0x00000001

#define _OR4_TCYC0_POSITION            0x0000001C
#define _OR4_TCYC0_MASK                0x00000001
#define _OR4_TCYC0_LENGTH              0x00000001

#define _OR4_TCYC_POSITION             0x0000001C
#define _OR4_TCYC_MASK                 0x0000000F
#define _OR4_TCYC_LENGTH               0x00000004

#define _OR4_AM27_POSITION             0x0000001B
#define _OR4_AM27_MASK                 0x00000001
#define _OR4_AM27_LENGTH               0x00000001

#define _OR4_AM26_POSITION             0x0000001A
#define _OR4_AM26_MASK                 0x00000001
#define _OR4_AM26_LENGTH               0x00000001

#define _OR4_AM25_POSITION             0x00000019
#define _OR4_AM25_MASK                 0x00000001
#define _OR4_AM25_LENGTH               0x00000001

#define _OR4_AM24_POSITION             0x00000018
#define _OR4_AM24_MASK                 0x00000001
#define _OR4_AM24_LENGTH               0x00000001

#define _OR4_AM23_POSITION             0x00000017
#define _OR4_AM23_MASK                 0x00000001
#define _OR4_AM23_LENGTH               0x00000001

#define _OR4_AM22_POSITION             0x00000016
#define _OR4_AM22_MASK                 0x00000001
#define _OR4_AM22_LENGTH               0x00000001

#define _OR4_AM21_POSITION             0x00000015
#define _OR4_AM21_MASK                 0x00000001
#define _OR4_AM21_LENGTH               0x00000001

#define _OR4_AM20_POSITION             0x00000014
#define _OR4_AM20_MASK                 0x00000001
#define _OR4_AM20_LENGTH               0x00000001

#define _OR4_AM19_POSITION             0x00000013
#define _OR4_AM19_MASK                 0x00000001
#define _OR4_AM19_LENGTH               0x00000001

#define _OR4_AM18_POSITION             0x00000012
#define _OR4_AM18_MASK                 0x00000001
#define _OR4_AM18_LENGTH               0x00000001

#define _OR4_AM17_POSITION             0x00000011
#define _OR4_AM17_MASK                 0x00000001
#define _OR4_AM17_LENGTH               0x00000001

#define _OR4_AM16_POSITION             0x00000010
#define _OR4_AM16_MASK                 0x00000001
#define _OR4_AM16_LENGTH               0x00000001

#define _OR4_AM15_POSITION             0x0000000F
#define _OR4_AM15_MASK                 0x00000001
#define _OR4_AM15_LENGTH               0x00000001

#define _OR4_AM14_POSITION             0x0000000E
#define _OR4_AM14_MASK                 0x00000001
#define _OR4_AM14_LENGTH               0x00000001

#define _OR4_AM13_POSITION             0x0000000D
#define _OR4_AM13_MASK                 0x00000001
#define _OR4_AM13_LENGTH               0x00000001

#define _OR4_AM12_POSITION             0x0000000C
#define _OR4_AM12_MASK                 0x00000001
#define _OR4_AM12_LENGTH               0x00000001

#define _OR4_AM11_POSITION             0x0000000B
#define _OR4_AM11_MASK                 0x00000001
#define _OR4_AM11_LENGTH               0x00000001

#define _OR4_AM_POSITION               0x0000000B
#define _OR4_AM_MASK                   0x0001FFFF
#define _OR4_AM_LENGTH                 0x00000011

#define _OR4_FCM3_POSITION             0x0000000A
#define _OR4_FCM3_MASK                 0x00000001
#define _OR4_FCM3_LENGTH               0x00000001

#define _OR4_FCM2_POSITION             0x00000009
#define _OR4_FCM2_MASK                 0x00000001
#define _OR4_FCM2_LENGTH               0x00000001

#define _OR4_FCM1_POSITION             0x00000008
#define _OR4_FCM1_MASK                 0x00000001
#define _OR4_FCM1_LENGTH               0x00000001

#define _OR4_FCM0_POSITION             0x00000007
#define _OR4_FCM0_MASK                 0x00000001
#define _OR4_FCM0_LENGTH               0x00000001

#define _OR4_FCM_POSITION              0x00000007
#define _OR4_FCM_MASK                  0x0000000F
#define _OR4_FCM_LENGTH                0x00000004

#define _OR4_BCYC1_POSITION            0x00000006
#define _OR4_BCYC1_MASK                0x00000001
#define _OR4_BCYC1_LENGTH              0x00000001

#define _OR4_BCYC0_POSITION            0x00000005
#define _OR4_BCYC0_MASK                0x00000001
#define _OR4_BCYC0_LENGTH              0x00000001

#define _OR4_BCYC_POSITION             0x00000005
#define _OR4_BCYC_MASK                 0x00000003
#define _OR4_BCYC_LENGTH               0x00000002

#define _OR4_PGME_POSITION             0x00000003
#define _OR4_PGME_MASK                 0x00000001
#define _OR4_PGME_LENGTH               0x00000001

#define _OR4_SPS1_POSITION             0x00000002
#define _OR4_SPS1_MASK                 0x00000001
#define _OR4_SPS1_LENGTH               0x00000001

#define _OR4_SPS0_POSITION             0x00000001
#define _OR4_SPS0_MASK                 0x00000001
#define _OR4_SPS0_LENGTH               0x00000001

#define _OR4_SPS_POSITION              0x00000001
#define _OR4_SPS_MASK                  0x00000003
#define _OR4_SPS_LENGTH                0x00000002

#define _OR4_DSSEL_POSITION            0x00000000
#define _OR4_DSSEL_MASK                0x00000001
#define _OR4_DSSEL_LENGTH              0x00000001

#define _OR5_TCYC3_POSITION            0x0000001F
#define _OR5_TCYC3_MASK                0x00000001
#define _OR5_TCYC3_LENGTH              0x00000001

#define _OR5_TCYC2_POSITION            0x0000001E
#define _OR5_TCYC2_MASK                0x00000001
#define _OR5_TCYC2_LENGTH              0x00000001

#define _OR5_TCYC1_POSITION            0x0000001D
#define _OR5_TCYC1_MASK                0x00000001
#define _OR5_TCYC1_LENGTH              0x00000001

#define _OR5_TCYC0_POSITION            0x0000001C
#define _OR5_TCYC0_MASK                0x00000001
#define _OR5_TCYC0_LENGTH              0x00000001

#define _OR5_TCYC_POSITION             0x0000001C
#define _OR5_TCYC_MASK                 0x0000000F
#define _OR5_TCYC_LENGTH               0x00000004

#define _OR5_AM27_POSITION             0x0000001B
#define _OR5_AM27_MASK                 0x00000001
#define _OR5_AM27_LENGTH               0x00000001

#define _OR5_AM26_POSITION             0x0000001A
#define _OR5_AM26_MASK                 0x00000001
#define _OR5_AM26_LENGTH               0x00000001

#define _OR5_AM25_POSITION             0x00000019
#define _OR5_AM25_MASK                 0x00000001
#define _OR5_AM25_LENGTH               0x00000001

#define _OR5_AM24_POSITION             0x00000018
#define _OR5_AM24_MASK                 0x00000001
#define _OR5_AM24_LENGTH               0x00000001

#define _OR5_AM23_POSITION             0x00000017
#define _OR5_AM23_MASK                 0x00000001
#define _OR5_AM23_LENGTH               0x00000001

#define _OR5_AM22_POSITION             0x00000016
#define _OR5_AM22_MASK                 0x00000001
#define _OR5_AM22_LENGTH               0x00000001

#define _OR5_AM21_POSITION             0x00000015
#define _OR5_AM21_MASK                 0x00000001
#define _OR5_AM21_LENGTH               0x00000001

#define _OR5_AM20_POSITION             0x00000014
#define _OR5_AM20_MASK                 0x00000001
#define _OR5_AM20_LENGTH               0x00000001

#define _OR5_AM19_POSITION             0x00000013
#define _OR5_AM19_MASK                 0x00000001
#define _OR5_AM19_LENGTH               0x00000001

#define _OR5_AM18_POSITION             0x00000012
#define _OR5_AM18_MASK                 0x00000001
#define _OR5_AM18_LENGTH               0x00000001

#define _OR5_AM17_POSITION             0x00000011
#define _OR5_AM17_MASK                 0x00000001
#define _OR5_AM17_LENGTH               0x00000001

#define _OR5_AM16_POSITION             0x00000010
#define _OR5_AM16_MASK                 0x00000001
#define _OR5_AM16_LENGTH               0x00000001

#define _OR5_AM15_POSITION             0x0000000F
#define _OR5_AM15_MASK                 0x00000001
#define _OR5_AM15_LENGTH               0x00000001

#define _OR5_AM14_POSITION             0x0000000E
#define _OR5_AM14_MASK                 0x00000001
#define _OR5_AM14_LENGTH               0x00000001

#define _OR5_AM13_POSITION             0x0000000D
#define _OR5_AM13_MASK                 0x00000001
#define _OR5_AM13_LENGTH               0x00000001

#define _OR5_AM12_POSITION             0x0000000C
#define _OR5_AM12_MASK                 0x00000001
#define _OR5_AM12_LENGTH               0x00000001

#define _OR5_AM11_POSITION             0x0000000B
#define _OR5_AM11_MASK                 0x00000001
#define _OR5_AM11_LENGTH               0x00000001

#define _OR5_AM_POSITION               0x0000000B
#define _OR5_AM_MASK                   0x0001FFFF
#define _OR5_AM_LENGTH                 0x00000011

#define _OR5_FCM3_POSITION             0x0000000A
#define _OR5_FCM3_MASK                 0x00000001
#define _OR5_FCM3_LENGTH               0x00000001

#define _OR5_FCM2_POSITION             0x00000009
#define _OR5_FCM2_MASK                 0x00000001
#define _OR5_FCM2_LENGTH               0x00000001

#define _OR5_FCM1_POSITION             0x00000008
#define _OR5_FCM1_MASK                 0x00000001
#define _OR5_FCM1_LENGTH               0x00000001

#define _OR5_FCM0_POSITION             0x00000007
#define _OR5_FCM0_MASK                 0x00000001
#define _OR5_FCM0_LENGTH               0x00000001

#define _OR5_FCM_POSITION              0x00000007
#define _OR5_FCM_MASK                  0x0000000F
#define _OR5_FCM_LENGTH                0x00000004

#define _OR5_BCYC1_POSITION            0x00000006
#define _OR5_BCYC1_MASK                0x00000001
#define _OR5_BCYC1_LENGTH              0x00000001

#define _OR5_BCYC0_POSITION            0x00000005
#define _OR5_BCYC0_MASK                0x00000001
#define _OR5_BCYC0_LENGTH              0x00000001

#define _OR5_BCYC_POSITION             0x00000005
#define _OR5_BCYC_MASK                 0x00000003
#define _OR5_BCYC_LENGTH               0x00000002

#define _OR5_PGME_POSITION             0x00000003
#define _OR5_PGME_MASK                 0x00000001
#define _OR5_PGME_LENGTH               0x00000001

#define _OR5_SPS1_POSITION             0x00000002
#define _OR5_SPS1_MASK                 0x00000001
#define _OR5_SPS1_LENGTH               0x00000001

#define _OR5_SPS0_POSITION             0x00000001
#define _OR5_SPS0_MASK                 0x00000001
#define _OR5_SPS0_LENGTH               0x00000001

#define _OR5_SPS_POSITION              0x00000001
#define _OR5_SPS_MASK                  0x00000003
#define _OR5_SPS_LENGTH                0x00000002

#define _OR5_DSSEL_POSITION            0x00000000
#define _OR5_DSSEL_MASK                0x00000001
#define _OR5_DSSEL_LENGTH              0x00000001

#define _OR6_TCYC3_POSITION            0x0000001F
#define _OR6_TCYC3_MASK                0x00000001
#define _OR6_TCYC3_LENGTH              0x00000001

#define _OR6_TCYC2_POSITION            0x0000001E
#define _OR6_TCYC2_MASK                0x00000001
#define _OR6_TCYC2_LENGTH              0x00000001

#define _OR6_TCYC1_POSITION            0x0000001D
#define _OR6_TCYC1_MASK                0x00000001
#define _OR6_TCYC1_LENGTH              0x00000001

#define _OR6_TCYC0_POSITION            0x0000001C
#define _OR6_TCYC0_MASK                0x00000001
#define _OR6_TCYC0_LENGTH              0x00000001

#define _OR6_TCYC_POSITION             0x0000001C
#define _OR6_TCYC_MASK                 0x0000000F
#define _OR6_TCYC_LENGTH               0x00000004

#define _OR6_AM27_POSITION             0x0000001B
#define _OR6_AM27_MASK                 0x00000001
#define _OR6_AM27_LENGTH               0x00000001

#define _OR6_AM26_POSITION             0x0000001A
#define _OR6_AM26_MASK                 0x00000001
#define _OR6_AM26_LENGTH               0x00000001

#define _OR6_AM25_POSITION             0x00000019
#define _OR6_AM25_MASK                 0x00000001
#define _OR6_AM25_LENGTH               0x00000001

#define _OR6_AM24_POSITION             0x00000018
#define _OR6_AM24_MASK                 0x00000001
#define _OR6_AM24_LENGTH               0x00000001

#define _OR6_AM23_POSITION             0x00000017
#define _OR6_AM23_MASK                 0x00000001
#define _OR6_AM23_LENGTH               0x00000001

#define _OR6_AM22_POSITION             0x00000016
#define _OR6_AM22_MASK                 0x00000001
#define _OR6_AM22_LENGTH               0x00000001

#define _OR6_AM21_POSITION             0x00000015
#define _OR6_AM21_MASK                 0x00000001
#define _OR6_AM21_LENGTH               0x00000001

#define _OR6_AM20_POSITION             0x00000014
#define _OR6_AM20_MASK                 0x00000001
#define _OR6_AM20_LENGTH               0x00000001

#define _OR6_AM19_POSITION             0x00000013
#define _OR6_AM19_MASK                 0x00000001
#define _OR6_AM19_LENGTH               0x00000001

#define _OR6_AM18_POSITION             0x00000012
#define _OR6_AM18_MASK                 0x00000001
#define _OR6_AM18_LENGTH               0x00000001

#define _OR6_AM17_POSITION             0x00000011
#define _OR6_AM17_MASK                 0x00000001
#define _OR6_AM17_LENGTH               0x00000001

#define _OR6_AM16_POSITION             0x00000010
#define _OR6_AM16_MASK                 0x00000001
#define _OR6_AM16_LENGTH               0x00000001

#define _OR6_AM15_POSITION             0x0000000F
#define _OR6_AM15_MASK                 0x00000001
#define _OR6_AM15_LENGTH               0x00000001

#define _OR6_AM14_POSITION             0x0000000E
#define _OR6_AM14_MASK                 0x00000001
#define _OR6_AM14_LENGTH               0x00000001

#define _OR6_AM13_POSITION             0x0000000D
#define _OR6_AM13_MASK                 0x00000001
#define _OR6_AM13_LENGTH               0x00000001

#define _OR6_AM12_POSITION             0x0000000C
#define _OR6_AM12_MASK                 0x00000001
#define _OR6_AM12_LENGTH               0x00000001

#define _OR6_AM11_POSITION             0x0000000B
#define _OR6_AM11_MASK                 0x00000001
#define _OR6_AM11_LENGTH               0x00000001

#define _OR6_AM_POSITION               0x0000000B
#define _OR6_AM_MASK                   0x0001FFFF
#define _OR6_AM_LENGTH                 0x00000011

#define _OR6_FCM3_POSITION             0x0000000A
#define _OR6_FCM3_MASK                 0x00000001
#define _OR6_FCM3_LENGTH               0x00000001

#define _OR6_FCM2_POSITION             0x00000009
#define _OR6_FCM2_MASK                 0x00000001
#define _OR6_FCM2_LENGTH               0x00000001

#define _OR6_FCM1_POSITION             0x00000008
#define _OR6_FCM1_MASK                 0x00000001
#define _OR6_FCM1_LENGTH               0x00000001

#define _OR6_FCM0_POSITION             0x00000007
#define _OR6_FCM0_MASK                 0x00000001
#define _OR6_FCM0_LENGTH               0x00000001

#define _OR6_FCM_POSITION              0x00000007
#define _OR6_FCM_MASK                  0x0000000F
#define _OR6_FCM_LENGTH                0x00000004

#define _OR6_BCYC1_POSITION            0x00000006
#define _OR6_BCYC1_MASK                0x00000001
#define _OR6_BCYC1_LENGTH              0x00000001

#define _OR6_BCYC0_POSITION            0x00000005
#define _OR6_BCYC0_MASK                0x00000001
#define _OR6_BCYC0_LENGTH              0x00000001

#define _OR6_BCYC_POSITION             0x00000005
#define _OR6_BCYC_MASK                 0x00000003
#define _OR6_BCYC_LENGTH               0x00000002

#define _OR6_PGME_POSITION             0x00000003
#define _OR6_PGME_MASK                 0x00000001
#define _OR6_PGME_LENGTH               0x00000001

#define _OR6_SPS1_POSITION             0x00000002
#define _OR6_SPS1_MASK                 0x00000001
#define _OR6_SPS1_LENGTH               0x00000001

#define _OR6_SPS0_POSITION             0x00000001
#define _OR6_SPS0_MASK                 0x00000001
#define _OR6_SPS0_LENGTH               0x00000001

#define _OR6_SPS_POSITION              0x00000001
#define _OR6_SPS_MASK                  0x00000003
#define _OR6_SPS_LENGTH                0x00000002

#define _OR6_DSSEL_POSITION            0x00000000
#define _OR6_DSSEL_MASK                0x00000001
#define _OR6_DSSEL_LENGTH              0x00000001

#define _OR7_TCYC3_POSITION            0x0000001F
#define _OR7_TCYC3_MASK                0x00000001
#define _OR7_TCYC3_LENGTH              0x00000001

#define _OR7_TCYC2_POSITION            0x0000001E
#define _OR7_TCYC2_MASK                0x00000001
#define _OR7_TCYC2_LENGTH              0x00000001

#define _OR7_TCYC1_POSITION            0x0000001D
#define _OR7_TCYC1_MASK                0x00000001
#define _OR7_TCYC1_LENGTH              0x00000001

#define _OR7_TCYC0_POSITION            0x0000001C
#define _OR7_TCYC0_MASK                0x00000001
#define _OR7_TCYC0_LENGTH              0x00000001

#define _OR7_TCYC_POSITION             0x0000001C
#define _OR7_TCYC_MASK                 0x0000000F
#define _OR7_TCYC_LENGTH               0x00000004

#define _OR7_AM27_POSITION             0x0000001B
#define _OR7_AM27_MASK                 0x00000001
#define _OR7_AM27_LENGTH               0x00000001

#define _OR7_AM26_POSITION             0x0000001A
#define _OR7_AM26_MASK                 0x00000001
#define _OR7_AM26_LENGTH               0x00000001

#define _OR7_AM25_POSITION             0x00000019
#define _OR7_AM25_MASK                 0x00000001
#define _OR7_AM25_LENGTH               0x00000001

#define _OR7_AM24_POSITION             0x00000018
#define _OR7_AM24_MASK                 0x00000001
#define _OR7_AM24_LENGTH               0x00000001

#define _OR7_AM23_POSITION             0x00000017
#define _OR7_AM23_MASK                 0x00000001
#define _OR7_AM23_LENGTH               0x00000001

#define _OR7_AM22_POSITION             0x00000016
#define _OR7_AM22_MASK                 0x00000001
#define _OR7_AM22_LENGTH               0x00000001

#define _OR7_AM21_POSITION             0x00000015
#define _OR7_AM21_MASK                 0x00000001
#define _OR7_AM21_LENGTH               0x00000001

#define _OR7_AM20_POSITION             0x00000014
#define _OR7_AM20_MASK                 0x00000001
#define _OR7_AM20_LENGTH               0x00000001

#define _OR7_AM19_POSITION             0x00000013
#define _OR7_AM19_MASK                 0x00000001
#define _OR7_AM19_LENGTH               0x00000001

#define _OR7_AM18_POSITION             0x00000012
#define _OR7_AM18_MASK                 0x00000001
#define _OR7_AM18_LENGTH               0x00000001

#define _OR7_AM17_POSITION             0x00000011
#define _OR7_AM17_MASK                 0x00000001
#define _OR7_AM17_LENGTH               0x00000001

#define _OR7_AM16_POSITION             0x00000010
#define _OR7_AM16_MASK                 0x00000001
#define _OR7_AM16_LENGTH               0x00000001

#define _OR7_AM15_POSITION             0x0000000F
#define _OR7_AM15_MASK                 0x00000001
#define _OR7_AM15_LENGTH               0x00000001

#define _OR7_AM14_POSITION             0x0000000E
#define _OR7_AM14_MASK                 0x00000001
#define _OR7_AM14_LENGTH               0x00000001

#define _OR7_AM13_POSITION             0x0000000D
#define _OR7_AM13_MASK                 0x00000001
#define _OR7_AM13_LENGTH               0x00000001

#define _OR7_AM12_POSITION             0x0000000C
#define _OR7_AM12_MASK                 0x00000001
#define _OR7_AM12_LENGTH               0x00000001

#define _OR7_AM11_POSITION             0x0000000B
#define _OR7_AM11_MASK                 0x00000001
#define _OR7_AM11_LENGTH               0x00000001

#define _OR7_AM_POSITION               0x0000000B
#define _OR7_AM_MASK                   0x0001FFFF
#define _OR7_AM_LENGTH                 0x00000011

#define _OR7_FCM3_POSITION             0x0000000A
#define _OR7_FCM3_MASK                 0x00000001
#define _OR7_FCM3_LENGTH               0x00000001

#define _OR7_FCM2_POSITION             0x00000009
#define _OR7_FCM2_MASK                 0x00000001
#define _OR7_FCM2_LENGTH               0x00000001

#define _OR7_FCM1_POSITION             0x00000008
#define _OR7_FCM1_MASK                 0x00000001
#define _OR7_FCM1_LENGTH               0x00000001

#define _OR7_FCM0_POSITION             0x00000007
#define _OR7_FCM0_MASK                 0x00000001
#define _OR7_FCM0_LENGTH               0x00000001

#define _OR7_FCM_POSITION              0x00000007
#define _OR7_FCM_MASK                  0x0000000F
#define _OR7_FCM_LENGTH                0x00000004

#define _OR7_BCYC1_POSITION            0x00000006
#define _OR7_BCYC1_MASK                0x00000001
#define _OR7_BCYC1_LENGTH              0x00000001

#define _OR7_BCYC0_POSITION            0x00000005
#define _OR7_BCYC0_MASK                0x00000001
#define _OR7_BCYC0_LENGTH              0x00000001

#define _OR7_BCYC_POSITION             0x00000005
#define _OR7_BCYC_MASK                 0x00000003
#define _OR7_BCYC_LENGTH               0x00000002

#define _OR7_PGME_POSITION             0x00000003
#define _OR7_PGME_MASK                 0x00000001
#define _OR7_PGME_LENGTH               0x00000001

#define _OR7_SPS1_POSITION             0x00000002
#define _OR7_SPS1_MASK                 0x00000001
#define _OR7_SPS1_LENGTH               0x00000001

#define _OR7_SPS0_POSITION             0x00000001
#define _OR7_SPS0_MASK                 0x00000001
#define _OR7_SPS0_LENGTH               0x00000001

#define _OR7_SPS_POSITION              0x00000001
#define _OR7_SPS_MASK                  0x00000003
#define _OR7_SPS_LENGTH                0x00000002

#define _OR7_DSSEL_POSITION            0x00000000
#define _OR7_DSSEL_MASK                0x00000001
#define _OR7_DSSEL_LENGTH              0x00000001

#define _ICCR_STP_POSITION             0x0000000F
#define _ICCR_STP_MASK                 0x00000001
#define _ICCR_STP_LENGTH               0x00000001

#define _ICCR_FRZ1_POSITION            0x0000000E
#define _ICCR_FRZ1_MASK                0x00000001
#define _ICCR_FRZ1_LENGTH              0x00000001

#define _ICCR_FRZ0_POSITION            0x0000000D
#define _ICCR_FRZ0_MASK                0x00000001
#define _ICCR_FRZ0_LENGTH              0x00000001

#define _ICCR_FRZ_POSITION             0x0000000D
#define _ICCR_FRZ_MASK                 0x00000003
#define _ICCR_FRZ_LENGTH               0x00000002

#define _ICCR_ARBP1_POSITION           0x0000000C
#define _ICCR_ARBP1_MASK               0x00000001
#define _ICCR_ARBP1_LENGTH             0x00000001

#define _ICCR_ARBP0_POSITION           0x0000000B
#define _ICCR_ARBP0_MASK               0x00000001
#define _ICCR_ARBP0_LENGTH             0x00000001

#define _ICCR_ARBP_POSITION            0x0000000B
#define _ICCR_ARBP_MASK                0x00000003
#define _ICCR_ARBP_LENGTH              0x00000002

#define _ICCR_ISM2_POSITION            0x0000000A
#define _ICCR_ISM2_MASK                0x00000001
#define _ICCR_ISM2_LENGTH              0x00000001

#define _ICCR_ISM1_POSITION            0x00000009
#define _ICCR_ISM1_MASK                0x00000001
#define _ICCR_ISM1_LENGTH              0x00000001

#define _ICCR_ISM0_POSITION            0x00000008
#define _ICCR_ISM0_MASK                0x00000001
#define _ICCR_ISM0_LENGTH              0x00000001

#define _ICCR_ISM_POSITION             0x00000008
#define _ICCR_ISM_MASK                 0x00000007
#define _ICCR_ISM_LENGTH               0x00000003

#define _ICCR_IAID2_POSITION           0x00000006
#define _ICCR_IAID2_MASK               0x00000001
#define _ICCR_IAID2_LENGTH             0x00000001

#define _ICCR_IAID1_POSITION           0x00000005
#define _ICCR_IAID1_MASK               0x00000001
#define _ICCR_IAID1_LENGTH             0x00000001

#define _ICCR_IAID0_POSITION           0x00000004
#define _ICCR_IAID0_MASK               0x00000001
#define _ICCR_IAID0_LENGTH             0x00000001

#define _ICCR_IAID_POSITION            0x00000004
#define _ICCR_IAID_MASK                0x00000007
#define _ICCR_IAID_LENGTH              0x00000003

#define _CMR1_ECO_POSITION             0x0000000F
#define _CMR1_ECO_MASK                 0x00000001
#define _CMR1_ECO_LENGTH               0x00000001

#define _CMR1_SRM_POSITION             0x0000000E
#define _CMR1_SRM_MASK                 0x00000001
#define _CMR1_SRM_LENGTH               0x00000001

#define _CMR1_SD_POSITION              0x0000000D
#define _CMR1_SD_MASK                  0x00000001
#define _CMR1_SD_LENGTH                0x00000001

#define _CMR1_RCI_POSITION             0x0000000C
#define _CMR1_RCI_MASK                 0x00000001
#define _CMR1_RCI_LENGTH               0x00000001

#define _CMR1_REQG1_POSITION           0x0000000B
#define _CMR1_REQG1_MASK               0x00000001
#define _CMR1_REQG1_LENGTH             0x00000001

#define _CMR1_REQG0_POSITION           0x0000000A
#define _CMR1_REQG0_MASK               0x00000001
#define _CMR1_REQG0_LENGTH             0x00000001

#define _CMR1_REQG_POSITION            0x0000000A
#define _CMR1_REQG_MASK                0x00000003
#define _CMR1_REQG_LENGTH              0x00000002

#define _CMR1_SAPI_POSITION            0x00000009
#define _CMR1_SAPI_MASK                0x00000001
#define _CMR1_SAPI_LENGTH              0x00000001

#define _CMR1_DAPI_POSITION            0x00000008
#define _CMR1_DAPI_MASK                0x00000001
#define _CMR1_DAPI_LENGTH              0x00000001

#define _CMR1_SSIZE1_POSITION          0x00000007
#define _CMR1_SSIZE1_MASK              0x00000001
#define _CMR1_SSIZE1_LENGTH            0x00000001

#define _CMR1_SSIZE0_POSITION          0x00000006
#define _CMR1_SSIZE0_MASK              0x00000001
#define _CMR1_SSIZE0_LENGTH            0x00000001

#define _CMR1_SSIZE_POSITION           0x00000006
#define _CMR1_SSIZE_MASK               0x00000003
#define _CMR1_SSIZE_LENGTH             0x00000002

#define _CMR1_DSIZE1_POSITION          0x00000005
#define _CMR1_DSIZE1_MASK              0x00000001
#define _CMR1_DSIZE1_LENGTH            0x00000001

#define _CMR1_DSIZE0_POSITION          0x00000004
#define _CMR1_DSIZE0_MASK              0x00000001
#define _CMR1_DSIZE0_LENGTH            0x00000001

#define _CMR1_DSIZE_POSITION           0x00000004
#define _CMR1_DSIZE_MASK               0x00000003
#define _CMR1_DSIZE_LENGTH             0x00000002

#define _CMR1_BT1_POSITION             0x00000003
#define _CMR1_BT1_MASK                 0x00000001
#define _CMR1_BT1_LENGTH               0x00000001

#define _CMR1_BT0_POSITION             0x00000002
#define _CMR1_BT0_MASK                 0x00000001
#define _CMR1_BT0_LENGTH               0x00000001

#define _CMR1_BT_POSITION              0x00000002
#define _CMR1_BT_MASK                  0x00000003
#define _CMR1_BT_LENGTH                0x00000002

#define _CMR1_RST_POSITION             0x00000001
#define _CMR1_RST_MASK                 0x00000001
#define _CMR1_RST_LENGTH               0x00000001

#define _CMR1_STR_POSITION             0x00000000
#define _CMR1_STR_MASK                 0x00000001
#define _CMR1_STR_LENGTH               0x00000001

#define _CMR2_ECO_POSITION             0x0000000F
#define _CMR2_ECO_MASK                 0x00000001
#define _CMR2_ECO_LENGTH               0x00000001

#define _CMR2_SRM_POSITION             0x0000000E
#define _CMR2_SRM_MASK                 0x00000001
#define _CMR2_SRM_LENGTH               0x00000001

#define _CMR2_SD_POSITION              0x0000000D
#define _CMR2_SD_MASK                  0x00000001
#define _CMR2_SD_LENGTH                0x00000001

#define _CMR2_RCI_POSITION             0x0000000C
#define _CMR2_RCI_MASK                 0x00000001
#define _CMR2_RCI_LENGTH               0x00000001

#define _CMR2_REQG1_POSITION           0x0000000B
#define _CMR2_REQG1_MASK               0x00000001
#define _CMR2_REQG1_LENGTH             0x00000001

#define _CMR2_REQG0_POSITION           0x0000000A
#define _CMR2_REQG0_MASK               0x00000001
#define _CMR2_REQG0_LENGTH             0x00000001

#define _CMR2_REQG_POSITION            0x0000000A
#define _CMR2_REQG_MASK                0x00000003
#define _CMR2_REQG_LENGTH              0x00000002

#define _CMR2_SAPI_POSITION            0x00000009
#define _CMR2_SAPI_MASK                0x00000001
#define _CMR2_SAPI_LENGTH              0x00000001

#define _CMR2_DAPI_POSITION            0x00000008
#define _CMR2_DAPI_MASK                0x00000001
#define _CMR2_DAPI_LENGTH              0x00000001

#define _CMR2_SSIZE1_POSITION          0x00000007
#define _CMR2_SSIZE1_MASK              0x00000001
#define _CMR2_SSIZE1_LENGTH            0x00000001

#define _CMR2_SSIZE0_POSITION          0x00000006
#define _CMR2_SSIZE0_MASK              0x00000001
#define _CMR2_SSIZE0_LENGTH            0x00000001

#define _CMR2_SSIZE_POSITION           0x00000006
#define _CMR2_SSIZE_MASK               0x00000003
#define _CMR2_SSIZE_LENGTH             0x00000002

#define _CMR2_DSIZE1_POSITION          0x00000005
#define _CMR2_DSIZE1_MASK              0x00000001
#define _CMR2_DSIZE1_LENGTH            0x00000001

#define _CMR2_DSIZE0_POSITION          0x00000004
#define _CMR2_DSIZE0_MASK              0x00000001
#define _CMR2_DSIZE0_LENGTH            0x00000001

#define _CMR2_DSIZE_POSITION           0x00000004
#define _CMR2_DSIZE_MASK               0x00000003
#define _CMR2_DSIZE_LENGTH             0x00000002

#define _CMR2_BT1_POSITION             0x00000003
#define _CMR2_BT1_MASK                 0x00000001
#define _CMR2_BT1_LENGTH               0x00000001

#define _CMR2_BT0_POSITION             0x00000002
#define _CMR2_BT0_MASK                 0x00000001
#define _CMR2_BT0_LENGTH               0x00000001

#define _CMR2_BT_POSITION              0x00000002
#define _CMR2_BT_MASK                  0x00000003
#define _CMR2_BT_LENGTH                0x00000002

#define _CMR2_RST_POSITION             0x00000001
#define _CMR2_RST_MASK                 0x00000001
#define _CMR2_RST_LENGTH               0x00000001

#define _CMR2_STR_POSITION             0x00000000
#define _CMR2_STR_MASK                 0x00000001
#define _CMR2_STR_LENGTH               0x00000001

#define _FCR1_DFC3_POSITION            0x00000007
#define _FCR1_DFC3_MASK                0x00000001
#define _FCR1_DFC3_LENGTH              0x00000001

#define _FCR1_DFC2_POSITION            0x00000006
#define _FCR1_DFC2_MASK                0x00000001
#define _FCR1_DFC2_LENGTH              0x00000001

#define _FCR1_DFC1_POSITION            0x00000005
#define _FCR1_DFC1_MASK                0x00000001
#define _FCR1_DFC1_LENGTH              0x00000001

#define _FCR1_DFC0_POSITION            0x00000004
#define _FCR1_DFC0_MASK                0x00000001
#define _FCR1_DFC0_LENGTH              0x00000001

#define _FCR1_DFC_POSITION             0x00000004
#define _FCR1_DFC_MASK                 0x0000000F
#define _FCR1_DFC_LENGTH               0x00000004

#define _FCR1_SFC3_POSITION            0x00000003
#define _FCR1_SFC3_MASK                0x00000001
#define _FCR1_SFC3_LENGTH              0x00000001

#define _FCR1_SFC2_POSITION            0x00000002
#define _FCR1_SFC2_MASK                0x00000001
#define _FCR1_SFC2_LENGTH              0x00000001

#define _FCR1_SFC1_POSITION            0x00000001
#define _FCR1_SFC1_MASK                0x00000001
#define _FCR1_SFC1_LENGTH              0x00000001

#define _FCR1_SFC0_POSITION            0x00000000
#define _FCR1_SFC0_MASK                0x00000001
#define _FCR1_SFC0_LENGTH              0x00000001

#define _FCR1_SFC_POSITION             0x00000000
#define _FCR1_SFC_MASK                 0x0000000F
#define _FCR1_SFC_LENGTH               0x00000004

#define _FCR2_DFC3_POSITION            0x00000007
#define _FCR2_DFC3_MASK                0x00000001
#define _FCR2_DFC3_LENGTH              0x00000001

#define _FCR2_DFC2_POSITION            0x00000006
#define _FCR2_DFC2_MASK                0x00000001
#define _FCR2_DFC2_LENGTH              0x00000001

#define _FCR2_DFC1_POSITION            0x00000005
#define _FCR2_DFC1_MASK                0x00000001
#define _FCR2_DFC1_LENGTH              0x00000001

#define _FCR2_DFC0_POSITION            0x00000004
#define _FCR2_DFC0_MASK                0x00000001
#define _FCR2_DFC0_LENGTH              0x00000001

#define _FCR2_DFC_POSITION             0x00000004
#define _FCR2_DFC_MASK                 0x0000000F
#define _FCR2_DFC_LENGTH               0x00000004

#define _FCR2_SFC3_POSITION            0x00000003
#define _FCR2_SFC3_MASK                0x00000001
#define _FCR2_SFC3_LENGTH              0x00000001

#define _FCR2_SFC2_POSITION            0x00000002
#define _FCR2_SFC2_MASK                0x00000001
#define _FCR2_SFC2_LENGTH              0x00000001

#define _FCR2_SFC1_POSITION            0x00000001
#define _FCR2_SFC1_MASK                0x00000001
#define _FCR2_SFC1_LENGTH              0x00000001

#define _FCR2_SFC0_POSITION            0x00000000
#define _FCR2_SFC0_MASK                0x00000001
#define _FCR2_SFC0_LENGTH              0x00000001

#define _FCR2_SFC_POSITION             0x00000000
#define _FCR2_SFC_MASK                 0x0000000F
#define _FCR2_SFC_LENGTH               0x00000004

#define _CMAR1_AD_POSITION             0x00000005
#define _CMAR1_AD_MASK                 0x00000001
#define _CMAR1_AD_LENGTH               0x00000001

#define _CMAR1_BRKP_POSITION           0x00000004
#define _CMAR1_BRKP_MASK               0x00000001
#define _CMAR1_BRKP_LENGTH             0x00000001

#define _CMAR1_OB_POSITION             0x00000003
#define _CMAR1_OB_MASK                 0x00000001
#define _CMAR1_OB_LENGTH               0x00000001

#define _CMAR1_BES_POSITION            0x00000002
#define _CMAR1_BES_MASK                0x00000001
#define _CMAR1_BES_LENGTH              0x00000001

#define _CMAR1_BED_POSITION            0x00000001
#define _CMAR1_BED_MASK                0x00000001
#define _CMAR1_BED_LENGTH              0x00000001

#define _CMAR1_DONE_POSITION           0x00000000
#define _CMAR1_DONE_MASK               0x00000001
#define _CMAR1_DONE_LENGTH             0x00000001

#define _CMAR2_AD_POSITION             0x00000005
#define _CMAR2_AD_MASK                 0x00000001
#define _CMAR2_AD_LENGTH               0x00000001

#define _CMAR2_BRKP_POSITION           0x00000004
#define _CMAR2_BRKP_MASK               0x00000001
#define _CMAR2_BRKP_LENGTH             0x00000001

#define _CMAR2_OB_POSITION             0x00000003
#define _CMAR2_OB_MASK                 0x00000001
#define _CMAR2_OB_LENGTH               0x00000001

#define _CMAR2_BES_POSITION            0x00000002
#define _CMAR2_BES_MASK                0x00000001
#define _CMAR2_BES_LENGTH              0x00000001

#define _CMAR2_BED_POSITION            0x00000001
#define _CMAR2_BED_MASK                0x00000001
#define _CMAR2_BED_LENGTH              0x00000001

#define _CMAR2_DONE_POSITION           0x00000000
#define _CMAR2_DONE_MASK               0x00000001
#define _CMAR2_DONE_LENGTH             0x00000001

#define _CSR1_AD_POSITION              0x00000005
#define _CSR1_AD_MASK                  0x00000001
#define _CSR1_AD_LENGTH                0x00000001

#define _CSR1_BRKP_POSITION            0x00000004
#define _CSR1_BRKP_MASK                0x00000001
#define _CSR1_BRKP_LENGTH              0x00000001

#define _CSR1_OB_POSITION              0x00000003
#define _CSR1_OB_MASK                  0x00000001
#define _CSR1_OB_LENGTH                0x00000001

#define _CSR1_BES_POSITION             0x00000002
#define _CSR1_BES_MASK                 0x00000001
#define _CSR1_BES_LENGTH               0x00000001

#define _CSR1_BED_POSITION             0x00000001
#define _CSR1_BED_MASK                 0x00000001
#define _CSR1_BED_LENGTH               0x00000001

#define _CSR1_DONE_POSITION            0x00000000
#define _CSR1_DONE_MASK                0x00000001
#define _CSR1_DONE_LENGTH              0x00000001

#define _CSR2_AD_POSITION              0x00000005
#define _CSR2_AD_MASK                  0x00000001
#define _CSR2_AD_LENGTH                0x00000001

#define _CSR2_BRKP_POSITION            0x00000004
#define _CSR2_BRKP_MASK                0x00000001
#define _CSR2_BRKP_LENGTH              0x00000001

#define _CSR2_OB_POSITION              0x00000003
#define _CSR2_OB_MASK                  0x00000001
#define _CSR2_OB_LENGTH                0x00000001

#define _CSR2_BES_POSITION             0x00000002
#define _CSR2_BES_MASK                 0x00000001
#define _CSR2_BES_LENGTH               0x00000001

#define _CSR2_BED_POSITION             0x00000001
#define _CSR2_BED_MASK                 0x00000001
#define _CSR2_BED_LENGTH               0x00000001

#define _CSR2_DONE_POSITION            0x00000000
#define _CSR2_DONE_MASK                0x00000001
#define _CSR2_DONE_LENGTH              0x00000001

#define _SDSR_RINT_POSITION            0x00000002
#define _SDSR_RINT_MASK                0x00000001
#define _SDSR_RINT_LENGTH              0x00000001

#define _SDSR_SBER_POSITION            0x00000001
#define _SDSR_SBER_MASK                0x00000001
#define _SDSR_SBER_LENGTH              0x00000001

#define _SDSR_SBKP_POSITION            0x00000000
#define _SDSR_SBKP_MASK                0x00000001
#define _SDSR_SBKP_LENGTH              0x00000001

#define _SDCR_FRZ1_POSITION            0x0000000E
#define _SDCR_FRZ1_MASK                0x00000001
#define _SDCR_FRZ1_LENGTH              0x00000001

#define _SDCR_FRZ0_POSITION            0x0000000D
#define _SDCR_FRZ0_MASK                0x00000001
#define _SDCR_FRZ0_LENGTH              0x00000001

#define _SDCR_FRZ_POSITION             0x0000000D
#define _SDCR_FRZ_MASK                 0x00000003
#define _SDCR_FRZ_LENGTH               0x00000002

#define _SDCR_SISM2_POSITION           0x0000000A
#define _SDCR_SISM2_MASK               0x00000001
#define _SDCR_SISM2_LENGTH             0x00000001

#define _SDCR_SISM1_POSITION           0x00000009
#define _SDCR_SISM1_MASK               0x00000001
#define _SDCR_SISM1_LENGTH             0x00000001

#define _SDCR_SISM0_POSITION           0x00000008
#define _SDCR_SISM0_MASK               0x00000001
#define _SDCR_SISM0_LENGTH             0x00000001

#define _SDCR_SISM_POSITION            0x00000008
#define _SDCR_SISM_MASK                0x00000007
#define _SDCR_SISM_LENGTH              0x00000003

#define _SDCR_SAID2_POSITION           0x00000006
#define _SDCR_SAID2_MASK               0x00000001
#define _SDCR_SAID2_LENGTH             0x00000001

#define _SDCR_SAID1_POSITION           0x00000005
#define _SDCR_SAID1_MASK               0x00000001
#define _SDCR_SAID1_LENGTH             0x00000001

#define _SDCR_SAID0_POSITION           0x00000004
#define _SDCR_SAID0_MASK               0x00000001
#define _SDCR_SAID0_LENGTH             0x00000001

#define _SDCR_SAID_POSITION            0x00000004
#define _SDCR_SAID_MASK                0x00000007
#define _SDCR_SAID_LENGTH              0x00000003

#define _SDCR_INTE_POSITION            0x00000001
#define _SDCR_INTE_MASK                0x00000001
#define _SDCR_INTE_LENGTH              0x00000001

#define _SDCR_INTB_POSITION            0x00000000
#define _SDCR_INTB_MASK                0x00000001
#define _SDCR_INTB_LENGTH              0x00000001

#define _CICR_SCdP1_POSITION           0x00000017
#define _CICR_SCdP1_MASK               0x00000001
#define _CICR_SCdP1_LENGTH             0x00000001

#define _CICR_SCdP0_POSITION           0x00000016
#define _CICR_SCdP0_MASK               0x00000001
#define _CICR_SCdP0_LENGTH             0x00000001

#define _CICR_SCdP_POSITION            0x00000016
#define _CICR_SCdP_MASK                0x00000003
#define _CICR_SCdP_LENGTH              0x00000002

#define _CICR_SCcP1_POSITION           0x00000015
#define _CICR_SCcP1_MASK               0x00000001
#define _CICR_SCcP1_LENGTH             0x00000001

#define _CICR_SCcP0_POSITION           0x00000014
#define _CICR_SCcP0_MASK               0x00000001
#define _CICR_SCcP0_LENGTH             0x00000001

#define _CICR_SCcP_POSITION            0x00000014
#define _CICR_SCcP_MASK                0x00000003
#define _CICR_SCcP_LENGTH              0x00000002

#define _CICR_SCbP1_POSITION           0x00000013
#define _CICR_SCbP1_MASK               0x00000001
#define _CICR_SCbP1_LENGTH             0x00000001

#define _CICR_SCbP0_POSITION           0x00000012
#define _CICR_SCbP0_MASK               0x00000001
#define _CICR_SCbP0_LENGTH             0x00000001

#define _CICR_SCbP_POSITION            0x00000012
#define _CICR_SCbP_MASK                0x00000003
#define _CICR_SCbP_LENGTH              0x00000002

#define _CICR_SCaP1_POSITION           0x00000011
#define _CICR_SCaP1_MASK               0x00000001
#define _CICR_SCaP1_LENGTH             0x00000001

#define _CICR_SCaP0_POSITION           0x00000010
#define _CICR_SCaP0_MASK               0x00000001
#define _CICR_SCaP0_LENGTH             0x00000001

#define _CICR_SCaP_POSITION            0x00000010
#define _CICR_SCaP_MASK                0x00000003
#define _CICR_SCaP_LENGTH              0x00000002

#define _CICR_IRL2_POSITION            0x0000000F
#define _CICR_IRL2_MASK                0x00000001
#define _CICR_IRL2_LENGTH              0x00000001

#define _CICR_IRL1_POSITION            0x0000000E
#define _CICR_IRL1_MASK                0x00000001
#define _CICR_IRL1_LENGTH              0x00000001

#define _CICR_IRL0_POSITION            0x0000000D
#define _CICR_IRL0_MASK                0x00000001
#define _CICR_IRL0_LENGTH              0x00000001

#define _CICR_IRL_POSITION             0x0000000D
#define _CICR_IRL_MASK                 0x00000007
#define _CICR_IRL_LENGTH               0x00000003

#define _CICR_HP4_POSITION             0x0000000C
#define _CICR_HP4_MASK                 0x00000001
#define _CICR_HP4_LENGTH               0x00000001

#define _CICR_HP3_POSITION             0x0000000B
#define _CICR_HP3_MASK                 0x00000001
#define _CICR_HP3_LENGTH               0x00000001

#define _CICR_HP2_POSITION             0x0000000A
#define _CICR_HP2_MASK                 0x00000001
#define _CICR_HP2_LENGTH               0x00000001

#define _CICR_HP1_POSITION             0x00000009
#define _CICR_HP1_MASK                 0x00000001
#define _CICR_HP1_LENGTH               0x00000001

#define _CICR_HP0_POSITION             0x00000008
#define _CICR_HP0_MASK                 0x00000001
#define _CICR_HP0_LENGTH               0x00000001

#define _CICR_HP_POSITION              0x00000008
#define _CICR_HP_MASK                  0x0000001F
#define _CICR_HP_LENGTH                0x00000005

#define _CICR_VBA2_POSITION            0x00000007
#define _CICR_VBA2_MASK                0x00000001
#define _CICR_VBA2_LENGTH              0x00000001

#define _CICR_VBA1_POSITION            0x00000006
#define _CICR_VBA1_MASK                0x00000001
#define _CICR_VBA1_LENGTH              0x00000001

#define _CICR_VBA0_POSITION            0x00000005
#define _CICR_VBA0_MASK                0x00000001
#define _CICR_VBA0_LENGTH              0x00000001

#define _CICR_VBA_POSITION             0x00000005
#define _CICR_VBA_MASK                 0x00000007
#define _CICR_VBA_LENGTH               0x00000003

#define _CICR_SPS_POSITION             0x00000000
#define _CICR_SPS_MASK                 0x00000001
#define _CICR_SPS_LENGTH               0x00000001

#define _CIPR_PC0_POSITION             0x0000001F
#define _CIPR_PC0_MASK                 0x00000001
#define _CIPR_PC0_LENGTH               0x00000001

#define _CIPR_SCC1_POSITION            0x0000001E
#define _CIPR_SCC1_MASK                0x00000001
#define _CIPR_SCC1_LENGTH              0x00000001

#define _CIPR_SCC2_POSITION            0x0000001D
#define _CIPR_SCC2_MASK                0x00000001
#define _CIPR_SCC2_LENGTH              0x00000001

#define _CIPR_SCC3_POSITION            0x0000001C
#define _CIPR_SCC3_MASK                0x00000001
#define _CIPR_SCC3_LENGTH              0x00000001

#define _CIPR_SCC4_POSITION            0x0000001B
#define _CIPR_SCC4_MASK                0x00000001
#define _CIPR_SCC4_LENGTH              0x00000001

#define _CIPR_PC1_POSITION             0x0000001A
#define _CIPR_PC1_MASK                 0x00000001
#define _CIPR_PC1_LENGTH               0x00000001

#define _CIPR_TIMER1_POSITION          0x00000019
#define _CIPR_TIMER1_MASK              0x00000001
#define _CIPR_TIMER1_LENGTH            0x00000001

#define _CIPR_PC2_POSITION             0x00000018
#define _CIPR_PC2_MASK                 0x00000001
#define _CIPR_PC2_LENGTH               0x00000001

#define _CIPR_PC3_POSITION             0x00000017
#define _CIPR_PC3_MASK                 0x00000001
#define _CIPR_PC3_LENGTH               0x00000001

#define _CIPR_SDMA_POSITION            0x00000016
#define _CIPR_SDMA_MASK                0x00000001
#define _CIPR_SDMA_LENGTH              0x00000001

#define _CIPR_IDMA1_POSITION           0x00000015
#define _CIPR_IDMA1_MASK               0x00000001
#define _CIPR_IDMA1_LENGTH             0x00000001

#define _CIPR_IDMA2_POSITION           0x00000014
#define _CIPR_IDMA2_MASK               0x00000001
#define _CIPR_IDMA2_LENGTH             0x00000001

#define _CIPR_TIMER2_POSITION          0x00000012
#define _CIPR_TIMER2_MASK              0x00000001
#define _CIPR_TIMER2_LENGTH            0x00000001

#define _CIPR_RTT_POSITION             0x00000011
#define _CIPR_RTT_MASK                 0x00000001
#define _CIPR_RTT_LENGTH               0x00000001

#define _CIPR_PC4_POSITION             0x0000000F
#define _CIPR_PC4_MASK                 0x00000001
#define _CIPR_PC4_LENGTH               0x00000001

#define _CIPR_PC5_POSITION             0x0000000E
#define _CIPR_PC5_MASK                 0x00000001
#define _CIPR_PC5_LENGTH               0x00000001

#define _CIPR_TIMER3_POSITION          0x0000000C
#define _CIPR_TIMER3_MASK              0x00000001
#define _CIPR_TIMER3_LENGTH            0x00000001

#define _CIPR_PC6_POSITION             0x0000000B
#define _CIPR_PC6_MASK                 0x00000001
#define _CIPR_PC6_LENGTH               0x00000001

#define _CIPR_PC7_POSITION             0x0000000A
#define _CIPR_PC7_MASK                 0x00000001
#define _CIPR_PC7_LENGTH               0x00000001

#define _CIPR_PC8_POSITION             0x00000009
#define _CIPR_PC8_MASK                 0x00000001
#define _CIPR_PC8_LENGTH               0x00000001

#define _CIPR_TIMER4_POSITION          0x00000007
#define _CIPR_TIMER4_MASK              0x00000001
#define _CIPR_TIMER4_LENGTH            0x00000001

#define _CIPR_PC9_POSITION             0x00000006
#define _CIPR_PC9_MASK                 0x00000001
#define _CIPR_PC9_LENGTH               0x00000001

#define _CIPR_SPI_POSITION             0x00000005
#define _CIPR_SPI_MASK                 0x00000001
#define _CIPR_SPI_LENGTH               0x00000001

#define _CIPR_SMC1_POSITION            0x00000004
#define _CIPR_SMC1_MASK                0x00000001
#define _CIPR_SMC1_LENGTH              0x00000001

#define _CIPR_SMC2_POSITION            0x00000003
#define _CIPR_SMC2_MASK                0x00000001
#define _CIPR_SMC2_LENGTH              0x00000001

#define _CIPR_PIP_POSITION             0x00000003
#define _CIPR_PIP_MASK                 0x00000001
#define _CIPR_PIP_LENGTH               0x00000001

#define _CIPR_PC10_POSITION            0x00000002
#define _CIPR_PC10_MASK                0x00000001
#define _CIPR_PC10_LENGTH              0x00000001

#define _CIPR_PC11_POSITION            0x00000001
#define _CIPR_PC11_MASK                0x00000001
#define _CIPR_PC11_LENGTH              0x00000001

#define _CIMR_PC0_POSITION             0x0000001F
#define _CIMR_PC0_MASK                 0x00000001
#define _CIMR_PC0_LENGTH               0x00000001

#define _CIMR_SCC1_POSITION            0x0000001E
#define _CIMR_SCC1_MASK                0x00000001
#define _CIMR_SCC1_LENGTH              0x00000001

#define _CIMR_SCC2_POSITION            0x0000001D
#define _CIMR_SCC2_MASK                0x00000001
#define _CIMR_SCC2_LENGTH              0x00000001

#define _CIMR_SCC3_POSITION            0x0000001C
#define _CIMR_SCC3_MASK                0x00000001
#define _CIMR_SCC3_LENGTH              0x00000001

#define _CIMR_SCC4_POSITION            0x0000001B
#define _CIMR_SCC4_MASK                0x00000001
#define _CIMR_SCC4_LENGTH              0x00000001

#define _CIMR_PC1_POSITION             0x0000001A
#define _CIMR_PC1_MASK                 0x00000001
#define _CIMR_PC1_LENGTH               0x00000001

#define _CIMR_TIMER1_POSITION          0x00000019
#define _CIMR_TIMER1_MASK              0x00000001
#define _CIMR_TIMER1_LENGTH            0x00000001

#define _CIMR_PC2_POSITION             0x00000018
#define _CIMR_PC2_MASK                 0x00000001
#define _CIMR_PC2_LENGTH               0x00000001

#define _CIMR_PC3_POSITION             0x00000017
#define _CIMR_PC3_MASK                 0x00000001
#define _CIMR_PC3_LENGTH               0x00000001

#define _CIMR_SDMA_POSITION            0x00000016
#define _CIMR_SDMA_MASK                0x00000001
#define _CIMR_SDMA_LENGTH              0x00000001

#define _CIMR_IDMA1_POSITION           0x00000015
#define _CIMR_IDMA1_MASK               0x00000001
#define _CIMR_IDMA1_LENGTH             0x00000001

#define _CIMR_IDMA2_POSITION           0x00000014
#define _CIMR_IDMA2_MASK               0x00000001
#define _CIMR_IDMA2_LENGTH             0x00000001

#define _CIMR_TIMER2_POSITION          0x00000012
#define _CIMR_TIMER2_MASK              0x00000001
#define _CIMR_TIMER2_LENGTH            0x00000001

#define _CIMR_RTT_POSITION             0x00000011
#define _CIMR_RTT_MASK                 0x00000001
#define _CIMR_RTT_LENGTH               0x00000001

#define _CIMR_PC4_POSITION             0x0000000F
#define _CIMR_PC4_MASK                 0x00000001
#define _CIMR_PC4_LENGTH               0x00000001

#define _CIMR_PC5_POSITION             0x0000000E
#define _CIMR_PC5_MASK                 0x00000001
#define _CIMR_PC5_LENGTH               0x00000001

#define _CIMR_TIMER3_POSITION          0x0000000C
#define _CIMR_TIMER3_MASK              0x00000001
#define _CIMR_TIMER3_LENGTH            0x00000001

#define _CIMR_PC6_POSITION             0x0000000B
#define _CIMR_PC6_MASK                 0x00000001
#define _CIMR_PC6_LENGTH               0x00000001

#define _CIMR_PC7_POSITION             0x0000000A
#define _CIMR_PC7_MASK                 0x00000001
#define _CIMR_PC7_LENGTH               0x00000001

#define _CIMR_PC8_POSITION             0x00000009
#define _CIMR_PC8_MASK                 0x00000001
#define _CIMR_PC8_LENGTH               0x00000001

#define _CIMR_TIMER4_POSITION          0x00000007
#define _CIMR_TIMER4_MASK              0x00000001
#define _CIMR_TIMER4_LENGTH            0x00000001

#define _CIMR_PC9_POSITION             0x00000006
#define _CIMR_PC9_MASK                 0x00000001
#define _CIMR_PC9_LENGTH               0x00000001

#define _CIMR_SPI_POSITION             0x00000005
#define _CIMR_SPI_MASK                 0x00000001
#define _CIMR_SPI_LENGTH               0x00000001

#define _CIMR_SMC1_POSITION            0x00000004
#define _CIMR_SMC1_MASK                0x00000001
#define _CIMR_SMC1_LENGTH              0x00000001

#define _CIMR_SMC2_POSITION            0x00000003
#define _CIMR_SMC2_MASK                0x00000001
#define _CIMR_SMC2_LENGTH              0x00000001

#define _CIMR_PIP_POSITION             0x00000003
#define _CIMR_PIP_MASK                 0x00000001
#define _CIMR_PIP_LENGTH               0x00000001

#define _CIMR_PC10_POSITION            0x00000002
#define _CIMR_PC10_MASK                0x00000001
#define _CIMR_PC10_LENGTH              0x00000001

#define _CIMR_PC11_POSITION            0x00000001
#define _CIMR_PC11_MASK                0x00000001
#define _CIMR_PC11_LENGTH              0x00000001

#define _CISR_PC0_POSITION             0x0000001F
#define _CISR_PC0_MASK                 0x00000001
#define _CISR_PC0_LENGTH               0x00000001

#define _CISR_SCC1_POSITION            0x0000001E
#define _CISR_SCC1_MASK                0x00000001
#define _CISR_SCC1_LENGTH              0x00000001

#define _CISR_SCC2_POSITION            0x0000001D
#define _CISR_SCC2_MASK                0x00000001
#define _CISR_SCC2_LENGTH              0x00000001

#define _CISR_SCC3_POSITION            0x0000001C
#define _CISR_SCC3_MASK                0x00000001
#define _CISR_SCC3_LENGTH              0x00000001

#define _CISR_SCC4_POSITION            0x0000001B
#define _CISR_SCC4_MASK                0x00000001
#define _CISR_SCC4_LENGTH              0x00000001

#define _CISR_PC1_POSITION             0x0000001A
#define _CISR_PC1_MASK                 0x00000001
#define _CISR_PC1_LENGTH               0x00000001

#define _CISR_TIMER1_POSITION          0x00000019
#define _CISR_TIMER1_MASK              0x00000001
#define _CISR_TIMER1_LENGTH            0x00000001

#define _CISR_PC2_POSITION             0x00000018
#define _CISR_PC2_MASK                 0x00000001
#define _CISR_PC2_LENGTH               0x00000001

#define _CISR_PC3_POSITION             0x00000017
#define _CISR_PC3_MASK                 0x00000001
#define _CISR_PC3_LENGTH               0x00000001

#define _CISR_SDMA_POSITION            0x00000016
#define _CISR_SDMA_MASK                0x00000001
#define _CISR_SDMA_LENGTH              0x00000001

#define _CISR_IDMA1_POSITION           0x00000015
#define _CISR_IDMA1_MASK               0x00000001
#define _CISR_IDMA1_LENGTH             0x00000001

#define _CISR_IDMA2_POSITION           0x00000014
#define _CISR_IDMA2_MASK               0x00000001
#define _CISR_IDMA2_LENGTH             0x00000001

#define _CISR_TIMER2_POSITION          0x00000012
#define _CISR_TIMER2_MASK              0x00000001
#define _CISR_TIMER2_LENGTH            0x00000001

#define _CISR_RTT_POSITION             0x00000011
#define _CISR_RTT_MASK                 0x00000001
#define _CISR_RTT_LENGTH               0x00000001

#define _CISR_PC4_POSITION             0x0000000F
#define _CISR_PC4_MASK                 0x00000001
#define _CISR_PC4_LENGTH               0x00000001

#define _CISR_PC5_POSITION             0x0000000E
#define _CISR_PC5_MASK                 0x00000001
#define _CISR_PC5_LENGTH               0x00000001

#define _CISR_TIMER3_POSITION          0x0000000C
#define _CISR_TIMER3_MASK              0x00000001
#define _CISR_TIMER3_LENGTH            0x00000001

#define _CISR_PC6_POSITION             0x0000000B
#define _CISR_PC6_MASK                 0x00000001
#define _CISR_PC6_LENGTH               0x00000001

#define _CISR_PC7_POSITION             0x0000000A
#define _CISR_PC7_MASK                 0x00000001
#define _CISR_PC7_LENGTH               0x00000001

#define _CISR_PC8_POSITION             0x00000009
#define _CISR_PC8_MASK                 0x00000001
#define _CISR_PC8_LENGTH               0x00000001

#define _CISR_TIMER4_POSITION          0x00000007
#define _CISR_TIMER4_MASK              0x00000001
#define _CISR_TIMER4_LENGTH            0x00000001

#define _CISR_PC9_POSITION             0x00000006
#define _CISR_PC9_MASK                 0x00000001
#define _CISR_PC9_LENGTH               0x00000001

#define _CISR_SPI_POSITION             0x00000005
#define _CISR_SPI_MASK                 0x00000001
#define _CISR_SPI_LENGTH               0x00000001

#define _CISR_SMC1_POSITION            0x00000004
#define _CISR_SMC1_MASK                0x00000001
#define _CISR_SMC1_LENGTH              0x00000001

#define _CISR_SMC2_POSITION            0x00000003
#define _CISR_SMC2_MASK                0x00000001
#define _CISR_SMC2_LENGTH              0x00000001

#define _CISR_PIP_POSITION             0x00000003
#define _CISR_PIP_MASK                 0x00000001
#define _CISR_PIP_LENGTH               0x00000001

#define _CISR_PC10_POSITION            0x00000002
#define _CISR_PC10_MASK                0x00000001
#define _CISR_PC10_LENGTH              0x00000001

#define _CISR_PC11_POSITION            0x00000001
#define _CISR_PC11_MASK                0x00000001
#define _CISR_PC11_LENGTH              0x00000001

#define _PADIR_DR15_POSITION           0x0000000F
#define _PADIR_DR15_MASK               0x00000001
#define _PADIR_DR15_LENGTH             0x00000001

#define _PADIR_DR14_POSITION           0x0000000E
#define _PADIR_DR14_MASK               0x00000001
#define _PADIR_DR14_LENGTH             0x00000001

#define _PADIR_DR13_POSITION           0x0000000D
#define _PADIR_DR13_MASK               0x00000001
#define _PADIR_DR13_LENGTH             0x00000001

#define _PADIR_DR12_POSITION           0x0000000C
#define _PADIR_DR12_MASK               0x00000001
#define _PADIR_DR12_LENGTH             0x00000001

#define _PADIR_DR11_POSITION           0x0000000B
#define _PADIR_DR11_MASK               0x00000001
#define _PADIR_DR11_LENGTH             0x00000001

#define _PADIR_DR10_POSITION           0x0000000A
#define _PADIR_DR10_MASK               0x00000001
#define _PADIR_DR10_LENGTH             0x00000001

#define _PADIR_DR9_POSITION            0x00000009
#define _PADIR_DR9_MASK                0x00000001
#define _PADIR_DR9_LENGTH              0x00000001

#define _PADIR_DR8_POSITION            0x00000008
#define _PADIR_DR8_MASK                0x00000001
#define _PADIR_DR8_LENGTH              0x00000001

#define _PADIR_DR7_POSITION            0x00000007
#define _PADIR_DR7_MASK                0x00000001
#define _PADIR_DR7_LENGTH              0x00000001

#define _PADIR_DR6_POSITION            0x00000006
#define _PADIR_DR6_MASK                0x00000001
#define _PADIR_DR6_LENGTH              0x00000001

#define _PADIR_DR5_POSITION            0x00000005
#define _PADIR_DR5_MASK                0x00000001
#define _PADIR_DR5_LENGTH              0x00000001

#define _PADIR_DR4_POSITION            0x00000004
#define _PADIR_DR4_MASK                0x00000001
#define _PADIR_DR4_LENGTH              0x00000001

#define _PADIR_DR3_POSITION            0x00000003
#define _PADIR_DR3_MASK                0x00000001
#define _PADIR_DR3_LENGTH              0x00000001

#define _PADIR_DR2_POSITION            0x00000002
#define _PADIR_DR2_MASK                0x00000001
#define _PADIR_DR2_LENGTH              0x00000001

#define _PADIR_DR1_POSITION            0x00000001
#define _PADIR_DR1_MASK                0x00000001
#define _PADIR_DR1_LENGTH              0x00000001

#define _PADIR_DR0_POSITION            0x00000000
#define _PADIR_DR0_MASK                0x00000001
#define _PADIR_DR0_LENGTH              0x00000001

#define _PAPAR_DD15_POSITION           0x0000000F
#define _PAPAR_DD15_MASK               0x00000001
#define _PAPAR_DD15_LENGTH             0x00000001

#define _PAPAR_DD14_POSITION           0x0000000E
#define _PAPAR_DD14_MASK               0x00000001
#define _PAPAR_DD14_LENGTH             0x00000001

#define _PAPAR_DD13_POSITION           0x0000000D
#define _PAPAR_DD13_MASK               0x00000001
#define _PAPAR_DD13_LENGTH             0x00000001

#define _PAPAR_DD12_POSITION           0x0000000C
#define _PAPAR_DD12_MASK               0x00000001
#define _PAPAR_DD12_LENGTH             0x00000001

#define _PAPAR_DD11_POSITION           0x0000000B
#define _PAPAR_DD11_MASK               0x00000001
#define _PAPAR_DD11_LENGTH             0x00000001

#define _PAPAR_DD10_POSITION           0x0000000A
#define _PAPAR_DD10_MASK               0x00000001
#define _PAPAR_DD10_LENGTH             0x00000001

#define _PAPAR_DD9_POSITION            0x00000009
#define _PAPAR_DD9_MASK                0x00000001
#define _PAPAR_DD9_LENGTH              0x00000001

#define _PAPAR_DD8_POSITION            0x00000008
#define _PAPAR_DD8_MASK                0x00000001
#define _PAPAR_DD8_LENGTH              0x00000001

#define _PAPAR_DD7_POSITION            0x00000007
#define _PAPAR_DD7_MASK                0x00000001
#define _PAPAR_DD7_LENGTH              0x00000001

#define _PAPAR_DD6_POSITION            0x00000006
#define _PAPAR_DD6_MASK                0x00000001
#define _PAPAR_DD6_LENGTH              0x00000001

#define _PAPAR_DD5_POSITION            0x00000005
#define _PAPAR_DD5_MASK                0x00000001
#define _PAPAR_DD5_LENGTH              0x00000001

#define _PAPAR_DD4_POSITION            0x00000004
#define _PAPAR_DD4_MASK                0x00000001
#define _PAPAR_DD4_LENGTH              0x00000001

#define _PAPAR_DD3_POSITION            0x00000003
#define _PAPAR_DD3_MASK                0x00000001
#define _PAPAR_DD3_LENGTH              0x00000001

#define _PAPAR_DD2_POSITION            0x00000002
#define _PAPAR_DD2_MASK                0x00000001
#define _PAPAR_DD2_LENGTH              0x00000001

#define _PAPAR_DD1_POSITION            0x00000001
#define _PAPAR_DD1_MASK                0x00000001
#define _PAPAR_DD1_LENGTH              0x00000001

#define _PAPAR_DD0_POSITION            0x00000000
#define _PAPAR_DD0_MASK                0x00000001
#define _PAPAR_DD0_LENGTH              0x00000001

#define _PAODR_OD7_POSITION            0x00000007
#define _PAODR_OD7_MASK                0x00000001
#define _PAODR_OD7_LENGTH              0x00000001

#define _PAODR_OD6_POSITION            0x00000006
#define _PAODR_OD6_MASK                0x00000001
#define _PAODR_OD6_LENGTH              0x00000001

#define _PAODR_OD5_POSITION            0x00000005
#define _PAODR_OD5_MASK                0x00000001
#define _PAODR_OD5_LENGTH              0x00000001

#define _PAODR_OD4_POSITION            0x00000004
#define _PAODR_OD4_MASK                0x00000001
#define _PAODR_OD4_LENGTH              0x00000001

#define _PAODR_OD3_POSITION            0x00000003
#define _PAODR_OD3_MASK                0x00000001
#define _PAODR_OD3_LENGTH              0x00000001

#define _PAODR_OD1_POSITION            0x00000001
#define _PAODR_OD1_MASK                0x00000001
#define _PAODR_OD1_LENGTH              0x00000001

#define _PADAT_D15_POSITION            0x0000000F
#define _PADAT_D15_MASK                0x00000001
#define _PADAT_D15_LENGTH              0x00000001

#define _PADAT_D14_POSITION            0x0000000E
#define _PADAT_D14_MASK                0x00000001
#define _PADAT_D14_LENGTH              0x00000001

#define _PADAT_D13_POSITION            0x0000000D
#define _PADAT_D13_MASK                0x00000001
#define _PADAT_D13_LENGTH              0x00000001

#define _PADAT_D12_POSITION            0x0000000C
#define _PADAT_D12_MASK                0x00000001
#define _PADAT_D12_LENGTH              0x00000001

#define _PADAT_D11_POSITION            0x0000000B
#define _PADAT_D11_MASK                0x00000001
#define _PADAT_D11_LENGTH              0x00000001

#define _PADAT_D10_POSITION            0x0000000A
#define _PADAT_D10_MASK                0x00000001
#define _PADAT_D10_LENGTH              0x00000001

#define _PADAT_D9_POSITION             0x00000009
#define _PADAT_D9_MASK                 0x00000001
#define _PADAT_D9_LENGTH               0x00000001

#define _PADAT_D8_POSITION             0x00000008
#define _PADAT_D8_MASK                 0x00000001
#define _PADAT_D8_LENGTH               0x00000001

#define _PADAT_D7_POSITION             0x00000007
#define _PADAT_D7_MASK                 0x00000001
#define _PADAT_D7_LENGTH               0x00000001

#define _PADAT_D6_POSITION             0x00000006
#define _PADAT_D6_MASK                 0x00000001
#define _PADAT_D6_LENGTH               0x00000001

#define _PADAT_D5_POSITION             0x00000005
#define _PADAT_D5_MASK                 0x00000001
#define _PADAT_D5_LENGTH               0x00000001

#define _PADAT_D4_POSITION             0x00000004
#define _PADAT_D4_MASK                 0x00000001
#define _PADAT_D4_LENGTH               0x00000001

#define _PADAT_D3_POSITION             0x00000003
#define _PADAT_D3_MASK                 0x00000001
#define _PADAT_D3_LENGTH               0x00000001

#define _PADAT_D2_POSITION             0x00000002
#define _PADAT_D2_MASK                 0x00000001
#define _PADAT_D2_LENGTH               0x00000001

#define _PADAT_D1_POSITION             0x00000001
#define _PADAT_D1_MASK                 0x00000001
#define _PADAT_D1_LENGTH               0x00000001

#define _PADAT_D0_POSITION             0x00000000
#define _PADAT_D0_MASK                 0x00000001
#define _PADAT_D0_LENGTH               0x00000001

#define _PCDIR_DR11_POSITION           0x0000000B
#define _PCDIR_DR11_MASK               0x00000001
#define _PCDIR_DR11_LENGTH             0x00000001

#define _PCDIR_DR10_POSITION           0x0000000A
#define _PCDIR_DR10_MASK               0x00000001
#define _PCDIR_DR10_LENGTH             0x00000001

#define _PCDIR_DR9_POSITION            0x00000009
#define _PCDIR_DR9_MASK                0x00000001
#define _PCDIR_DR9_LENGTH              0x00000001

#define _PCDIR_DR8_POSITION            0x00000008
#define _PCDIR_DR8_MASK                0x00000001
#define _PCDIR_DR8_LENGTH              0x00000001

#define _PCDIR_DR7_POSITION            0x00000007
#define _PCDIR_DR7_MASK                0x00000001
#define _PCDIR_DR7_LENGTH              0x00000001

#define _PCDIR_DR6_POSITION            0x00000006
#define _PCDIR_DR6_MASK                0x00000001
#define _PCDIR_DR6_LENGTH              0x00000001

#define _PCDIR_DR5_POSITION            0x00000005
#define _PCDIR_DR5_MASK                0x00000001
#define _PCDIR_DR5_LENGTH              0x00000001

#define _PCDIR_DR4_POSITION            0x00000004
#define _PCDIR_DR4_MASK                0x00000001
#define _PCDIR_DR4_LENGTH              0x00000001

#define _PCDIR_DR3_POSITION            0x00000003
#define _PCDIR_DR3_MASK                0x00000001
#define _PCDIR_DR3_LENGTH              0x00000001

#define _PCDIR_DR2_POSITION            0x00000002
#define _PCDIR_DR2_MASK                0x00000001
#define _PCDIR_DR2_LENGTH              0x00000001

#define _PCDIR_DR1_POSITION            0x00000001
#define _PCDIR_DR1_MASK                0x00000001
#define _PCDIR_DR1_LENGTH              0x00000001

#define _PCDIR_DR0_POSITION            0x00000000
#define _PCDIR_DR0_MASK                0x00000001
#define _PCDIR_DR0_LENGTH              0x00000001

#define _PCPAR_DD11_POSITION           0x0000000B
#define _PCPAR_DD11_MASK               0x00000001
#define _PCPAR_DD11_LENGTH             0x00000001

#define _PCPAR_DD10_POSITION           0x0000000A
#define _PCPAR_DD10_MASK               0x00000001
#define _PCPAR_DD10_LENGTH             0x00000001

#define _PCPAR_DD9_POSITION            0x00000009
#define _PCPAR_DD9_MASK                0x00000001
#define _PCPAR_DD9_LENGTH              0x00000001

#define _PCPAR_DD8_POSITION            0x00000008
#define _PCPAR_DD8_MASK                0x00000001
#define _PCPAR_DD8_LENGTH              0x00000001

#define _PCPAR_DD7_POSITION            0x00000007
#define _PCPAR_DD7_MASK                0x00000001
#define _PCPAR_DD7_LENGTH              0x00000001

#define _PCPAR_DD6_POSITION            0x00000006
#define _PCPAR_DD6_MASK                0x00000001
#define _PCPAR_DD6_LENGTH              0x00000001

#define _PCPAR_DD5_POSITION            0x00000005
#define _PCPAR_DD5_MASK                0x00000001
#define _PCPAR_DD5_LENGTH              0x00000001

#define _PCPAR_DD4_POSITION            0x00000004
#define _PCPAR_DD4_MASK                0x00000001
#define _PCPAR_DD4_LENGTH              0x00000001

#define _PCPAR_DD3_POSITION            0x00000003
#define _PCPAR_DD3_MASK                0x00000001
#define _PCPAR_DD3_LENGTH              0x00000001

#define _PCPAR_DD2_POSITION            0x00000002
#define _PCPAR_DD2_MASK                0x00000001
#define _PCPAR_DD2_LENGTH              0x00000001

#define _PCPAR_DD1_POSITION            0x00000001
#define _PCPAR_DD1_MASK                0x00000001
#define _PCPAR_DD1_LENGTH              0x00000001

#define _PCPAR_DD0_POSITION            0x00000000
#define _PCPAR_DD0_MASK                0x00000001
#define _PCPAR_DD0_LENGTH              0x00000001

#define _PCSO_CD4_POSITION             0x0000000B
#define _PCSO_CD4_MASK                 0x00000001
#define _PCSO_CD4_LENGTH               0x00000001

#define _PCSO_CTS4_POSITION            0x0000000A
#define _PCSO_CTS4_MASK                0x00000001
#define _PCSO_CTS4_LENGTH              0x00000001

#define _PCSO_CD3_POSITION             0x00000009
#define _PCSO_CD3_MASK                 0x00000001
#define _PCSO_CD3_LENGTH               0x00000001

#define _PCSO_CTS3_POSITION            0x00000008
#define _PCSO_CTS3_MASK                0x00000001
#define _PCSO_CTS3_LENGTH              0x00000001

#define _PCSO_CD2_POSITION             0x00000007
#define _PCSO_CD2_MASK                 0x00000001
#define _PCSO_CD2_LENGTH               0x00000001

#define _PCSO_CTS2_POSITION            0x00000006
#define _PCSO_CTS2_MASK                0x00000001
#define _PCSO_CTS2_LENGTH              0x00000001

#define _PCSO_CD1_POSITION             0x00000005
#define _PCSO_CD1_MASK                 0x00000001
#define _PCSO_CD1_LENGTH               0x00000001

#define _PCSO_CTS1_POSITION            0x00000004
#define _PCSO_CTS1_MASK                0x00000001
#define _PCSO_CTS1_LENGTH              0x00000001

#define _PCDAT_D11_POSITION            0x0000000B
#define _PCDAT_D11_MASK                0x00000001
#define _PCDAT_D11_LENGTH              0x00000001

#define _PCDAT_D10_POSITION            0x0000000A
#define _PCDAT_D10_MASK                0x00000001
#define _PCDAT_D10_LENGTH              0x00000001

#define _PCDAT_D9_POSITION             0x00000009
#define _PCDAT_D9_MASK                 0x00000001
#define _PCDAT_D9_LENGTH               0x00000001

#define _PCDAT_D8_POSITION             0x00000008
#define _PCDAT_D8_MASK                 0x00000001
#define _PCDAT_D8_LENGTH               0x00000001

#define _PCDAT_D7_POSITION             0x00000007
#define _PCDAT_D7_MASK                 0x00000001
#define _PCDAT_D7_LENGTH               0x00000001

#define _PCDAT_D6_POSITION             0x00000006
#define _PCDAT_D6_MASK                 0x00000001
#define _PCDAT_D6_LENGTH               0x00000001

#define _PCDAT_D5_POSITION             0x00000005
#define _PCDAT_D5_MASK                 0x00000001
#define _PCDAT_D5_LENGTH               0x00000001

#define _PCDAT_D4_POSITION             0x00000004
#define _PCDAT_D4_MASK                 0x00000001
#define _PCDAT_D4_LENGTH               0x00000001

#define _PCDAT_D3_POSITION             0x00000003
#define _PCDAT_D3_MASK                 0x00000001
#define _PCDAT_D3_LENGTH               0x00000001

#define _PCDAT_D2_POSITION             0x00000002
#define _PCDAT_D2_MASK                 0x00000001
#define _PCDAT_D2_LENGTH               0x00000001

#define _PCDAT_D1_POSITION             0x00000001
#define _PCDAT_D1_MASK                 0x00000001
#define _PCDAT_D1_LENGTH               0x00000001

#define _PCDAT_D0_POSITION             0x00000000
#define _PCDAT_D0_MASK                 0x00000001
#define _PCDAT_D0_LENGTH               0x00000001

#define _PCINT_EDM11_POSITION          0x0000000B
#define _PCINT_EDM11_MASK              0x00000001
#define _PCINT_EDM11_LENGTH            0x00000001

#define _PCINT_EDM10_POSITION          0x0000000A
#define _PCINT_EDM10_MASK              0x00000001
#define _PCINT_EDM10_LENGTH            0x00000001

#define _PCINT_EDM9_POSITION           0x00000009
#define _PCINT_EDM9_MASK               0x00000001
#define _PCINT_EDM9_LENGTH             0x00000001

#define _PCINT_EDM8_POSITION           0x00000008
#define _PCINT_EDM8_MASK               0x00000001
#define _PCINT_EDM8_LENGTH             0x00000001

#define _PCINT_EDM7_POSITION           0x00000007
#define _PCINT_EDM7_MASK               0x00000001
#define _PCINT_EDM7_LENGTH             0x00000001

#define _PCINT_EDM6_POSITION           0x00000006
#define _PCINT_EDM6_MASK               0x00000001
#define _PCINT_EDM6_LENGTH             0x00000001

#define _PCINT_EDM5_POSITION           0x00000005
#define _PCINT_EDM5_MASK               0x00000001
#define _PCINT_EDM5_LENGTH             0x00000001

#define _PCINT_EDM4_POSITION           0x00000004
#define _PCINT_EDM4_MASK               0x00000001
#define _PCINT_EDM4_LENGTH             0x00000001

#define _PCINT_EDM3_POSITION           0x00000003
#define _PCINT_EDM3_MASK               0x00000001
#define _PCINT_EDM3_LENGTH             0x00000001

#define _PCINT_EDM2_POSITION           0x00000002
#define _PCINT_EDM2_MASK               0x00000001
#define _PCINT_EDM2_LENGTH             0x00000001

#define _PCINT_EDM1_POSITION           0x00000001
#define _PCINT_EDM1_MASK               0x00000001
#define _PCINT_EDM1_LENGTH             0x00000001

#define _PCINT_EDM0_POSITION           0x00000000
#define _PCINT_EDM0_MASK               0x00000001
#define _PCINT_EDM0_LENGTH             0x00000001

#define _TGCR_CAS4_POSITION            0x0000000F
#define _TGCR_CAS4_MASK                0x00000001
#define _TGCR_CAS4_LENGTH              0x00000001

#define _TGCR_FRZ4_POSITION            0x0000000E
#define _TGCR_FRZ4_MASK                0x00000001
#define _TGCR_FRZ4_LENGTH              0x00000001

#define _TGCR_STP4_POSITION            0x0000000D
#define _TGCR_STP4_MASK                0x00000001
#define _TGCR_STP4_LENGTH              0x00000001

#define _TGCR_RST4_POSITION            0x0000000C
#define _TGCR_RST4_MASK                0x00000001
#define _TGCR_RST4_LENGTH              0x00000001

#define _TGCR_GM2_POSITION             0x0000000B
#define _TGCR_GM2_MASK                 0x00000001
#define _TGCR_GM2_LENGTH               0x00000001

#define _TGCR_FRZ3_POSITION            0x0000000A
#define _TGCR_FRZ3_MASK                0x00000001
#define _TGCR_FRZ3_LENGTH              0x00000001

#define _TGCR_STP3_POSITION            0x00000009
#define _TGCR_STP3_MASK                0x00000001
#define _TGCR_STP3_LENGTH              0x00000001

#define _TGCR_RST3_POSITION            0x00000008
#define _TGCR_RST3_MASK                0x00000001
#define _TGCR_RST3_LENGTH              0x00000001

#define _TGCR_CAS2_POSITION            0x00000007
#define _TGCR_CAS2_MASK                0x00000001
#define _TGCR_CAS2_LENGTH              0x00000001

#define _TGCR_FRZ2_POSITION            0x00000006
#define _TGCR_FRZ2_MASK                0x00000001
#define _TGCR_FRZ2_LENGTH              0x00000001

#define _TGCR_STP2_POSITION            0x00000005
#define _TGCR_STP2_MASK                0x00000001
#define _TGCR_STP2_LENGTH              0x00000001

#define _TGCR_RST2_POSITION            0x00000004
#define _TGCR_RST2_MASK                0x00000001
#define _TGCR_RST2_LENGTH              0x00000001

#define _TGCR_GM1_POSITION             0x00000003
#define _TGCR_GM1_MASK                 0x00000001
#define _TGCR_GM1_LENGTH               0x00000001

#define _TGCR_FRZ1_POSITION            0x00000002
#define _TGCR_FRZ1_MASK                0x00000001
#define _TGCR_FRZ1_LENGTH              0x00000001

#define _TGCR_STP1_POSITION            0x00000001
#define _TGCR_STP1_MASK                0x00000001
#define _TGCR_STP1_LENGTH              0x00000001

#define _TGCR_RST1_POSITION            0x00000000
#define _TGCR_RST1_MASK                0x00000001
#define _TGCR_RST1_LENGTH              0x00000001

#define _TMR1_PS7_POSITION             0x0000000F
#define _TMR1_PS7_MASK                 0x00000001
#define _TMR1_PS7_LENGTH               0x00000001

#define _TMR1_PS6_POSITION             0x0000000E
#define _TMR1_PS6_MASK                 0x00000001
#define _TMR1_PS6_LENGTH               0x00000001

#define _TMR1_PS5_POSITION             0x0000000D
#define _TMR1_PS5_MASK                 0x00000001
#define _TMR1_PS5_LENGTH               0x00000001

#define _TMR1_PS4_POSITION             0x0000000C
#define _TMR1_PS4_MASK                 0x00000001
#define _TMR1_PS4_LENGTH               0x00000001

#define _TMR1_PS3_POSITION             0x0000000B
#define _TMR1_PS3_MASK                 0x00000001
#define _TMR1_PS3_LENGTH               0x00000001

#define _TMR1_PS2_POSITION             0x0000000A
#define _TMR1_PS2_MASK                 0x00000001
#define _TMR1_PS2_LENGTH               0x00000001

#define _TMR1_PS1_POSITION             0x00000009
#define _TMR1_PS1_MASK                 0x00000001
#define _TMR1_PS1_LENGTH               0x00000001

#define _TMR1_PS0_POSITION             0x00000008
#define _TMR1_PS0_MASK                 0x00000001
#define _TMR1_PS0_LENGTH               0x00000001

#define _TMR1_PS_POSITION              0x00000008
#define _TMR1_PS_MASK                  0x000000FF
#define _TMR1_PS_LENGTH                0x00000008

#define _TMR1_CE1_POSITION             0x00000007
#define _TMR1_CE1_MASK                 0x00000001
#define _TMR1_CE1_LENGTH               0x00000001

#define _TMR1_CE0_POSITION             0x00000006
#define _TMR1_CE0_MASK                 0x00000001
#define _TMR1_CE0_LENGTH               0x00000001

#define _TMR1_CE_POSITION              0x00000006
#define _TMR1_CE_MASK                  0x00000003
#define _TMR1_CE_LENGTH                0x00000002

#define _TMR1_OM_POSITION              0x00000005
#define _TMR1_OM_MASK                  0x00000001
#define _TMR1_OM_LENGTH                0x00000001

#define _TMR1_ORI_POSITION             0x00000004
#define _TMR1_ORI_MASK                 0x00000001
#define _TMR1_ORI_LENGTH               0x00000001

#define _TMR1_FRR_POSITION             0x00000003
#define _TMR1_FRR_MASK                 0x00000001
#define _TMR1_FRR_LENGTH               0x00000001

#define _TMR1_ICLK1_POSITION           0x00000002
#define _TMR1_ICLK1_MASK               0x00000001
#define _TMR1_ICLK1_LENGTH             0x00000001

#define _TMR1_ICLK0_POSITION           0x00000001
#define _TMR1_ICLK0_MASK               0x00000001
#define _TMR1_ICLK0_LENGTH             0x00000001

#define _TMR1_ICLK_POSITION            0x00000001
#define _TMR1_ICLK_MASK                0x00000003
#define _TMR1_ICLK_LENGTH              0x00000002

#define _TMR1_GE_POSITION              0x00000000
#define _TMR1_GE_MASK                  0x00000001
#define _TMR1_GE_LENGTH                0x00000001

#define _TMR2_PS7_POSITION             0x0000000F
#define _TMR2_PS7_MASK                 0x00000001
#define _TMR2_PS7_LENGTH               0x00000001

#define _TMR2_PS6_POSITION             0x0000000E
#define _TMR2_PS6_MASK                 0x00000001
#define _TMR2_PS6_LENGTH               0x00000001

#define _TMR2_PS5_POSITION             0x0000000D
#define _TMR2_PS5_MASK                 0x00000001
#define _TMR2_PS5_LENGTH               0x00000001

#define _TMR2_PS4_POSITION             0x0000000C
#define _TMR2_PS4_MASK                 0x00000001
#define _TMR2_PS4_LENGTH               0x00000001

#define _TMR2_PS3_POSITION             0x0000000B
#define _TMR2_PS3_MASK                 0x00000001
#define _TMR2_PS3_LENGTH               0x00000001

#define _TMR2_PS2_POSITION             0x0000000A
#define _TMR2_PS2_MASK                 0x00000001
#define _TMR2_PS2_LENGTH               0x00000001

#define _TMR2_PS1_POSITION             0x00000009
#define _TMR2_PS1_MASK                 0x00000001
#define _TMR2_PS1_LENGTH               0x00000001

#define _TMR2_PS0_POSITION             0x00000008
#define _TMR2_PS0_MASK                 0x00000001
#define _TMR2_PS0_LENGTH               0x00000001

#define _TMR2_PS_POSITION              0x00000008
#define _TMR2_PS_MASK                  0x000000FF
#define _TMR2_PS_LENGTH                0x00000008

#define _TMR2_CE1_POSITION             0x00000007
#define _TMR2_CE1_MASK                 0x00000001
#define _TMR2_CE1_LENGTH               0x00000001

#define _TMR2_CE0_POSITION             0x00000006
#define _TMR2_CE0_MASK                 0x00000001
#define _TMR2_CE0_LENGTH               0x00000001

#define _TMR2_CE_POSITION              0x00000006
#define _TMR2_CE_MASK                  0x00000003
#define _TMR2_CE_LENGTH                0x00000002

#define _TMR2_OM_POSITION              0x00000005
#define _TMR2_OM_MASK                  0x00000001
#define _TMR2_OM_LENGTH                0x00000001

#define _TMR2_ORI_POSITION             0x00000004
#define _TMR2_ORI_MASK                 0x00000001
#define _TMR2_ORI_LENGTH               0x00000001

#define _TMR2_FRR_POSITION             0x00000003
#define _TMR2_FRR_MASK                 0x00000001
#define _TMR2_FRR_LENGTH               0x00000001

#define _TMR2_ICLK1_POSITION           0x00000002
#define _TMR2_ICLK1_MASK               0x00000001
#define _TMR2_ICLK1_LENGTH             0x00000001

#define _TMR2_ICLK0_POSITION           0x00000001
#define _TMR2_ICLK0_MASK               0x00000001
#define _TMR2_ICLK0_LENGTH             0x00000001

#define _TMR2_ICLK_POSITION            0x00000001
#define _TMR2_ICLK_MASK                0x00000003
#define _TMR2_ICLK_LENGTH              0x00000002

#define _TMR2_GE_POSITION              0x00000000
#define _TMR2_GE_MASK                  0x00000001
#define _TMR2_GE_LENGTH                0x00000001

#define _TMR3_PS7_POSITION             0x0000000F
#define _TMR3_PS7_MASK                 0x00000001
#define _TMR3_PS7_LENGTH               0x00000001

#define _TMR3_PS6_POSITION             0x0000000E
#define _TMR3_PS6_MASK                 0x00000001
#define _TMR3_PS6_LENGTH               0x00000001

#define _TMR3_PS5_POSITION             0x0000000D
#define _TMR3_PS5_MASK                 0x00000001
#define _TMR3_PS5_LENGTH               0x00000001

#define _TMR3_PS4_POSITION             0x0000000C
#define _TMR3_PS4_MASK                 0x00000001
#define _TMR3_PS4_LENGTH               0x00000001

#define _TMR3_PS3_POSITION             0x0000000B
#define _TMR3_PS3_MASK                 0x00000001
#define _TMR3_PS3_LENGTH               0x00000001

#define _TMR3_PS2_POSITION             0x0000000A
#define _TMR3_PS2_MASK                 0x00000001
#define _TMR3_PS2_LENGTH               0x00000001

#define _TMR3_PS1_POSITION             0x00000009
#define _TMR3_PS1_MASK                 0x00000001
#define _TMR3_PS1_LENGTH               0x00000001

#define _TMR3_PS0_POSITION             0x00000008
#define _TMR3_PS0_MASK                 0x00000001
#define _TMR3_PS0_LENGTH               0x00000001

#define _TMR3_PS_POSITION              0x00000008
#define _TMR3_PS_MASK                  0x000000FF
#define _TMR3_PS_LENGTH                0x00000008

#define _TMR3_CE1_POSITION             0x00000007
#define _TMR3_CE1_MASK                 0x00000001
#define _TMR3_CE1_LENGTH               0x00000001

#define _TMR3_CE0_POSITION             0x00000006
#define _TMR3_CE0_MASK                 0x00000001
#define _TMR3_CE0_LENGTH               0x00000001

#define _TMR3_CE_POSITION              0x00000006
#define _TMR3_CE_MASK                  0x00000003
#define _TMR3_CE_LENGTH                0x00000002

#define _TMR3_OM_POSITION              0x00000005
#define _TMR3_OM_MASK                  0x00000001
#define _TMR3_OM_LENGTH                0x00000001

#define _TMR3_ORI_POSITION             0x00000004
#define _TMR3_ORI_MASK                 0x00000001
#define _TMR3_ORI_LENGTH               0x00000001

#define _TMR3_FRR_POSITION             0x00000003
#define _TMR3_FRR_MASK                 0x00000001
#define _TMR3_FRR_LENGTH               0x00000001

#define _TMR3_ICLK1_POSITION           0x00000002
#define _TMR3_ICLK1_MASK               0x00000001
#define _TMR3_ICLK1_LENGTH             0x00000001

#define _TMR3_ICLK0_POSITION           0x00000001
#define _TMR3_ICLK0_MASK               0x00000001
#define _TMR3_ICLK0_LENGTH             0x00000001

#define _TMR3_ICLK_POSITION            0x00000001
#define _TMR3_ICLK_MASK                0x00000003
#define _TMR3_ICLK_LENGTH              0x00000002

#define _TMR3_GE_POSITION              0x00000000
#define _TMR3_GE_MASK                  0x00000001
#define _TMR3_GE_LENGTH                0x00000001

#define _TMR4_PS7_POSITION             0x0000000F
#define _TMR4_PS7_MASK                 0x00000001
#define _TMR4_PS7_LENGTH               0x00000001

#define _TMR4_PS6_POSITION             0x0000000E
#define _TMR4_PS6_MASK                 0x00000001
#define _TMR4_PS6_LENGTH               0x00000001

#define _TMR4_PS5_POSITION             0x0000000D
#define _TMR4_PS5_MASK                 0x00000001
#define _TMR4_PS5_LENGTH               0x00000001

#define _TMR4_PS4_POSITION             0x0000000C
#define _TMR4_PS4_MASK                 0x00000001
#define _TMR4_PS4_LENGTH               0x00000001

#define _TMR4_PS3_POSITION             0x0000000B
#define _TMR4_PS3_MASK                 0x00000001
#define _TMR4_PS3_LENGTH               0x00000001

#define _TMR4_PS2_POSITION             0x0000000A
#define _TMR4_PS2_MASK                 0x00000001
#define _TMR4_PS2_LENGTH               0x00000001

#define _TMR4_PS1_POSITION             0x00000009
#define _TMR4_PS1_MASK                 0x00000001
#define _TMR4_PS1_LENGTH               0x00000001

#define _TMR4_PS0_POSITION             0x00000008
#define _TMR4_PS0_MASK                 0x00000001
#define _TMR4_PS0_LENGTH               0x00000001

#define _TMR4_PS_POSITION              0x00000008
#define _TMR4_PS_MASK                  0x000000FF
#define _TMR4_PS_LENGTH                0x00000008

#define _TMR4_CE1_POSITION             0x00000007
#define _TMR4_CE1_MASK                 0x00000001
#define _TMR4_CE1_LENGTH               0x00000001

#define _TMR4_CE0_POSITION             0x00000006
#define _TMR4_CE0_MASK                 0x00000001
#define _TMR4_CE0_LENGTH               0x00000001

#define _TMR4_CE_POSITION              0x00000006
#define _TMR4_CE_MASK                  0x00000003
#define _TMR4_CE_LENGTH                0x00000002

#define _TMR4_OM_POSITION              0x00000005
#define _TMR4_OM_MASK                  0x00000001
#define _TMR4_OM_LENGTH                0x00000001

#define _TMR4_ORI_POSITION             0x00000004
#define _TMR4_ORI_MASK                 0x00000001
#define _TMR4_ORI_LENGTH               0x00000001

#define _TMR4_FRR_POSITION             0x00000003
#define _TMR4_FRR_MASK                 0x00000001
#define _TMR4_FRR_LENGTH               0x00000001

#define _TMR4_ICLK1_POSITION           0x00000002
#define _TMR4_ICLK1_MASK               0x00000001
#define _TMR4_ICLK1_LENGTH             0x00000001

#define _TMR4_ICLK0_POSITION           0x00000001
#define _TMR4_ICLK0_MASK               0x00000001
#define _TMR4_ICLK0_LENGTH             0x00000001

#define _TMR4_ICLK_POSITION            0x00000001
#define _TMR4_ICLK_MASK                0x00000003
#define _TMR4_ICLK_LENGTH              0x00000002

#define _TMR4_GE_POSITION              0x00000000
#define _TMR4_GE_MASK                  0x00000001
#define _TMR4_GE_LENGTH                0x00000001

#define _TER1_REF_POSITION             0x00000001
#define _TER1_REF_MASK                 0x00000001
#define _TER1_REF_LENGTH               0x00000001

#define _TER1_CAP_POSITION             0x00000000
#define _TER1_CAP_MASK                 0x00000001
#define _TER1_CAP_LENGTH               0x00000001

#define _TER2_REF_POSITION             0x00000001
#define _TER2_REF_MASK                 0x00000001
#define _TER2_REF_LENGTH               0x00000001

#define _TER2_CAP_POSITION             0x00000000
#define _TER2_CAP_MASK                 0x00000001
#define _TER2_CAP_LENGTH               0x00000001

#define _TER3_REF_POSITION             0x00000001
#define _TER3_REF_MASK                 0x00000001
#define _TER3_REF_LENGTH               0x00000001

#define _TER3_CAP_POSITION             0x00000000
#define _TER3_CAP_MASK                 0x00000001
#define _TER3_CAP_LENGTH               0x00000001

#define _TER4_REF_POSITION             0x00000001
#define _TER4_REF_MASK                 0x00000001
#define _TER4_REF_LENGTH               0x00000001

#define _TER4_CAP_POSITION             0x00000000
#define _TER4_CAP_MASK                 0x00000001
#define _TER4_CAP_LENGTH               0x00000001

#define _CR_RST_POSITION               0x0000000F
#define _CR_RST_MASK                   0x00000001
#define _CR_RST_LENGTH                 0x00000001

#define _CR_OPCODE3_POSITION           0x0000000B
#define _CR_OPCODE3_MASK               0x00000001
#define _CR_OPCODE3_LENGTH             0x00000001

#define _CR_OPCODE2_POSITION           0x0000000A
#define _CR_OPCODE2_MASK               0x00000001
#define _CR_OPCODE2_LENGTH             0x00000001

#define _CR_OPCODE1_POSITION           0x00000009
#define _CR_OPCODE1_MASK               0x00000001
#define _CR_OPCODE1_LENGTH             0x00000001

#define _CR_OPCODE0_POSITION           0x00000008
#define _CR_OPCODE0_MASK               0x00000001
#define _CR_OPCODE0_LENGTH             0x00000001

#define _CR_OPCODE_POSITION            0x00000008
#define _CR_OPCODE_MASK                0x0000000F
#define _CR_OPCODE_LENGTH              0x00000004

#define _CR_CHNUM3_POSITION            0x00000007
#define _CR_CHNUM3_MASK                0x00000001
#define _CR_CHNUM3_LENGTH              0x00000001

#define _CR_CHNUM2_POSITION            0x00000006
#define _CR_CHNUM2_MASK                0x00000001
#define _CR_CHNUM2_LENGTH              0x00000001

#define _CR_CHNUM1_POSITION            0x00000005
#define _CR_CHNUM1_MASK                0x00000001
#define _CR_CHNUM1_LENGTH              0x00000001

#define _CR_CHNUM0_POSITION            0x00000004
#define _CR_CHNUM0_MASK                0x00000001
#define _CR_CHNUM0_LENGTH              0x00000001

#define _CR_CHNUM_POSITION             0x00000004
#define _CR_CHNUM_MASK                 0x0000000F
#define _CR_CHNUM_LENGTH               0x00000004

#define _CR_FLG_POSITION               0x00000000
#define _CR_FLG_MASK                   0x00000001
#define _CR_FLG_LENGTH                 0x00000001

#define _BRGC1_RST_POSITION            0x00000011
#define _BRGC1_RST_MASK                0x00000001
#define _BRGC1_RST_LENGTH              0x00000001

#define _BRGC1_EN_POSITION             0x00000010
#define _BRGC1_EN_MASK                 0x00000001
#define _BRGC1_EN_LENGTH               0x00000001

#define _BRGC1_EXTC1_POSITION          0x0000000F
#define _BRGC1_EXTC1_MASK              0x00000001
#define _BRGC1_EXTC1_LENGTH            0x00000001

#define _BRGC1_EXTC0_POSITION          0x0000000E
#define _BRGC1_EXTC0_MASK              0x00000001
#define _BRGC1_EXTC0_LENGTH            0x00000001

#define _BRGC1_EXTC_POSITION           0x0000000E
#define _BRGC1_EXTC_MASK               0x00000003
#define _BRGC1_EXTC_LENGTH             0x00000002

#define _BRGC1_ATB_POSITION            0x0000000D
#define _BRGC1_ATB_MASK                0x00000001
#define _BRGC1_ATB_LENGTH              0x00000001

#define _BRGC1_CD11_POSITION           0x0000000C
#define _BRGC1_CD11_MASK               0x00000001
#define _BRGC1_CD11_LENGTH             0x00000001

#define _BRGC1_CD10_POSITION           0x0000000B
#define _BRGC1_CD10_MASK               0x00000001
#define _BRGC1_CD10_LENGTH             0x00000001

#define _BRGC1_CD9_POSITION            0x0000000A
#define _BRGC1_CD9_MASK                0x00000001
#define _BRGC1_CD9_LENGTH              0x00000001

#define _BRGC1_CD8_POSITION            0x00000009
#define _BRGC1_CD8_MASK                0x00000001
#define _BRGC1_CD8_LENGTH              0x00000001

#define _BRGC1_CD7_POSITION            0x00000008
#define _BRGC1_CD7_MASK                0x00000001
#define _BRGC1_CD7_LENGTH              0x00000001

#define _BRGC1_CD6_POSITION            0x00000007
#define _BRGC1_CD6_MASK                0x00000001
#define _BRGC1_CD6_LENGTH              0x00000001

#define _BRGC1_CD5_POSITION            0x00000006
#define _BRGC1_CD5_MASK                0x00000001
#define _BRGC1_CD5_LENGTH              0x00000001

#define _BRGC1_CD4_POSITION            0x00000005
#define _BRGC1_CD4_MASK                0x00000001
#define _BRGC1_CD4_LENGTH              0x00000001

#define _BRGC1_CD3_POSITION            0x00000004
#define _BRGC1_CD3_MASK                0x00000001
#define _BRGC1_CD3_LENGTH              0x00000001

#define _BRGC1_CD2_POSITION            0x00000003
#define _BRGC1_CD2_MASK                0x00000001
#define _BRGC1_CD2_LENGTH              0x00000001

#define _BRGC1_CD1_POSITION            0x00000002
#define _BRGC1_CD1_MASK                0x00000001
#define _BRGC1_CD1_LENGTH              0x00000001

#define _BRGC1_CD0_POSITION            0x00000001
#define _BRGC1_CD0_MASK                0x00000001
#define _BRGC1_CD0_LENGTH              0x00000001

#define _BRGC1_CD_POSITION             0x00000001
#define _BRGC1_CD_MASK                 0x00000FFF
#define _BRGC1_CD_LENGTH               0x0000000C

#define _BRGC1_DIV16_POSITION          0x00000000
#define _BRGC1_DIV16_MASK              0x00000001
#define _BRGC1_DIV16_LENGTH            0x00000001

#define _BRGC2_RST_POSITION            0x00000011
#define _BRGC2_RST_MASK                0x00000001
#define _BRGC2_RST_LENGTH              0x00000001

#define _BRGC2_EN_POSITION             0x00000010
#define _BRGC2_EN_MASK                 0x00000001
#define _BRGC2_EN_LENGTH               0x00000001

#define _BRGC2_EXTC1_POSITION          0x0000000F
#define _BRGC2_EXTC1_MASK              0x00000001
#define _BRGC2_EXTC1_LENGTH            0x00000001

#define _BRGC2_EXTC0_POSITION          0x0000000E
#define _BRGC2_EXTC0_MASK              0x00000001
#define _BRGC2_EXTC0_LENGTH            0x00000001

#define _BRGC2_EXTC_POSITION           0x0000000E
#define _BRGC2_EXTC_MASK               0x00000003
#define _BRGC2_EXTC_LENGTH             0x00000002

#define _BRGC2_ATB_POSITION            0x0000000D
#define _BRGC2_ATB_MASK                0x00000001
#define _BRGC2_ATB_LENGTH              0x00000001

#define _BRGC2_CD11_POSITION           0x0000000C
#define _BRGC2_CD11_MASK               0x00000001
#define _BRGC2_CD11_LENGTH             0x00000001

#define _BRGC2_CD10_POSITION           0x0000000B
#define _BRGC2_CD10_MASK               0x00000001
#define _BRGC2_CD10_LENGTH             0x00000001

#define _BRGC2_CD9_POSITION            0x0000000A
#define _BRGC2_CD9_MASK                0x00000001
#define _BRGC2_CD9_LENGTH              0x00000001

#define _BRGC2_CD8_POSITION            0x00000009
#define _BRGC2_CD8_MASK                0x00000001
#define _BRGC2_CD8_LENGTH              0x00000001

#define _BRGC2_CD7_POSITION            0x00000008
#define _BRGC2_CD7_MASK                0x00000001
#define _BRGC2_CD7_LENGTH              0x00000001

#define _BRGC2_CD6_POSITION            0x00000007
#define _BRGC2_CD6_MASK                0x00000001
#define _BRGC2_CD6_LENGTH              0x00000001

#define _BRGC2_CD5_POSITION            0x00000006
#define _BRGC2_CD5_MASK                0x00000001
#define _BRGC2_CD5_LENGTH              0x00000001

#define _BRGC2_CD4_POSITION            0x00000005
#define _BRGC2_CD4_MASK                0x00000001
#define _BRGC2_CD4_LENGTH              0x00000001

#define _BRGC2_CD3_POSITION            0x00000004
#define _BRGC2_CD3_MASK                0x00000001
#define _BRGC2_CD3_LENGTH              0x00000001

#define _BRGC2_CD2_POSITION            0x00000003
#define _BRGC2_CD2_MASK                0x00000001
#define _BRGC2_CD2_LENGTH              0x00000001

#define _BRGC2_CD1_POSITION            0x00000002
#define _BRGC2_CD1_MASK                0x00000001
#define _BRGC2_CD1_LENGTH              0x00000001

#define _BRGC2_CD0_POSITION            0x00000001
#define _BRGC2_CD0_MASK                0x00000001
#define _BRGC2_CD0_LENGTH              0x00000001

#define _BRGC2_CD_POSITION             0x00000001
#define _BRGC2_CD_MASK                 0x00000FFF
#define _BRGC2_CD_LENGTH               0x0000000C

#define _BRGC2_DIV16_POSITION          0x00000000
#define _BRGC2_DIV16_MASK              0x00000001
#define _BRGC2_DIV16_LENGTH            0x00000001

#define _BRGC3_RST_POSITION            0x00000011
#define _BRGC3_RST_MASK                0x00000001
#define _BRGC3_RST_LENGTH              0x00000001

#define _BRGC3_EN_POSITION             0x00000010
#define _BRGC3_EN_MASK                 0x00000001
#define _BRGC3_EN_LENGTH               0x00000001

#define _BRGC3_EXTC1_POSITION          0x0000000F
#define _BRGC3_EXTC1_MASK              0x00000001
#define _BRGC3_EXTC1_LENGTH            0x00000001

#define _BRGC3_EXTC0_POSITION          0x0000000E
#define _BRGC3_EXTC0_MASK              0x00000001
#define _BRGC3_EXTC0_LENGTH            0x00000001

#define _BRGC3_EXTC_POSITION           0x0000000E
#define _BRGC3_EXTC_MASK               0x00000003
#define _BRGC3_EXTC_LENGTH             0x00000002

#define _BRGC3_ATB_POSITION            0x0000000D
#define _BRGC3_ATB_MASK                0x00000001
#define _BRGC3_ATB_LENGTH              0x00000001

#define _BRGC3_CD11_POSITION           0x0000000C
#define _BRGC3_CD11_MASK               0x00000001
#define _BRGC3_CD11_LENGTH             0x00000001

#define _BRGC3_CD10_POSITION           0x0000000B
#define _BRGC3_CD10_MASK               0x00000001
#define _BRGC3_CD10_LENGTH             0x00000001

#define _BRGC3_CD9_POSITION            0x0000000A
#define _BRGC3_CD9_MASK                0x00000001
#define _BRGC3_CD9_LENGTH              0x00000001

#define _BRGC3_CD8_POSITION            0x00000009
#define _BRGC3_CD8_MASK                0x00000001
#define _BRGC3_CD8_LENGTH              0x00000001

#define _BRGC3_CD7_POSITION            0x00000008
#define _BRGC3_CD7_MASK                0x00000001
#define _BRGC3_CD7_LENGTH              0x00000001

#define _BRGC3_CD6_POSITION            0x00000007
#define _BRGC3_CD6_MASK                0x00000001
#define _BRGC3_CD6_LENGTH              0x00000001

#define _BRGC3_CD5_POSITION            0x00000006
#define _BRGC3_CD5_MASK                0x00000001
#define _BRGC3_CD5_LENGTH              0x00000001

#define _BRGC3_CD4_POSITION            0x00000005
#define _BRGC3_CD4_MASK                0x00000001
#define _BRGC3_CD4_LENGTH              0x00000001

#define _BRGC3_CD3_POSITION            0x00000004
#define _BRGC3_CD3_MASK                0x00000001
#define _BRGC3_CD3_LENGTH              0x00000001

#define _BRGC3_CD2_POSITION            0x00000003
#define _BRGC3_CD2_MASK                0x00000001
#define _BRGC3_CD2_LENGTH              0x00000001

#define _BRGC3_CD1_POSITION            0x00000002
#define _BRGC3_CD1_MASK                0x00000001
#define _BRGC3_CD1_LENGTH              0x00000001

#define _BRGC3_CD0_POSITION            0x00000001
#define _BRGC3_CD0_MASK                0x00000001
#define _BRGC3_CD0_LENGTH              0x00000001

#define _BRGC3_CD_POSITION             0x00000001
#define _BRGC3_CD_MASK                 0x00000FFF
#define _BRGC3_CD_LENGTH               0x0000000C

#define _BRGC3_DIV16_POSITION          0x00000000
#define _BRGC3_DIV16_MASK              0x00000001
#define _BRGC3_DIV16_LENGTH            0x00000001

#define _BRGC4_RST_POSITION            0x00000011
#define _BRGC4_RST_MASK                0x00000001
#define _BRGC4_RST_LENGTH              0x00000001

#define _BRGC4_EN_POSITION             0x00000010
#define _BRGC4_EN_MASK                 0x00000001
#define _BRGC4_EN_LENGTH               0x00000001

#define _BRGC4_EXTC1_POSITION          0x0000000F
#define _BRGC4_EXTC1_MASK              0x00000001
#define _BRGC4_EXTC1_LENGTH            0x00000001

#define _BRGC4_EXTC0_POSITION          0x0000000E
#define _BRGC4_EXTC0_MASK              0x00000001
#define _BRGC4_EXTC0_LENGTH            0x00000001

#define _BRGC4_EXTC_POSITION           0x0000000E
#define _BRGC4_EXTC_MASK               0x00000003
#define _BRGC4_EXTC_LENGTH             0x00000002

#define _BRGC4_ATB_POSITION            0x0000000D
#define _BRGC4_ATB_MASK                0x00000001
#define _BRGC4_ATB_LENGTH              0x00000001

#define _BRGC4_CD11_POSITION           0x0000000C
#define _BRGC4_CD11_MASK               0x00000001
#define _BRGC4_CD11_LENGTH             0x00000001

#define _BRGC4_CD10_POSITION           0x0000000B
#define _BRGC4_CD10_MASK               0x00000001
#define _BRGC4_CD10_LENGTH             0x00000001

#define _BRGC4_CD9_POSITION            0x0000000A
#define _BRGC4_CD9_MASK                0x00000001
#define _BRGC4_CD9_LENGTH              0x00000001

#define _BRGC4_CD8_POSITION            0x00000009
#define _BRGC4_CD8_MASK                0x00000001
#define _BRGC4_CD8_LENGTH              0x00000001

#define _BRGC4_CD7_POSITION            0x00000008
#define _BRGC4_CD7_MASK                0x00000001
#define _BRGC4_CD7_LENGTH              0x00000001

#define _BRGC4_CD6_POSITION            0x00000007
#define _BRGC4_CD6_MASK                0x00000001
#define _BRGC4_CD6_LENGTH              0x00000001

#define _BRGC4_CD5_POSITION            0x00000006
#define _BRGC4_CD5_MASK                0x00000001
#define _BRGC4_CD5_LENGTH              0x00000001

#define _BRGC4_CD4_POSITION            0x00000005
#define _BRGC4_CD4_MASK                0x00000001
#define _BRGC4_CD4_LENGTH              0x00000001

#define _BRGC4_CD3_POSITION            0x00000004
#define _BRGC4_CD3_MASK                0x00000001
#define _BRGC4_CD3_LENGTH              0x00000001

#define _BRGC4_CD2_POSITION            0x00000003
#define _BRGC4_CD2_MASK                0x00000001
#define _BRGC4_CD2_LENGTH              0x00000001

#define _BRGC4_CD1_POSITION            0x00000002
#define _BRGC4_CD1_MASK                0x00000001
#define _BRGC4_CD1_LENGTH              0x00000001

#define _BRGC4_CD0_POSITION            0x00000001
#define _BRGC4_CD0_MASK                0x00000001
#define _BRGC4_CD0_LENGTH              0x00000001

#define _BRGC4_CD_POSITION             0x00000001
#define _BRGC4_CD_MASK                 0x00000FFF
#define _BRGC4_CD_LENGTH               0x0000000C

#define _BRGC4_DIV16_POSITION          0x00000000
#define _BRGC4_DIV16_MASK              0x00000001
#define _BRGC4_DIV16_LENGTH            0x00000001

#define _GSMR1L_EDGE1_POSITION         0x0000001E
#define _GSMR1L_EDGE1_MASK             0x00000001
#define _GSMR1L_EDGE1_LENGTH           0x00000001

#define _GSMR1L_EDGE0_POSITION         0x0000001D
#define _GSMR1L_EDGE0_MASK             0x00000001
#define _GSMR1L_EDGE0_LENGTH           0x00000001

#define _GSMR1L_EDGE_POSITION          0x0000001D
#define _GSMR1L_EDGE_MASK              0x00000003
#define _GSMR1L_EDGE_LENGTH            0x00000002

#define _GSMR1L_TCI_POSITION           0x0000001C
#define _GSMR1L_TCI_MASK               0x00000001
#define _GSMR1L_TCI_LENGTH             0x00000001

#define _GSMR1L_TSNC1_POSITION         0x0000001B
#define _GSMR1L_TSNC1_MASK             0x00000001
#define _GSMR1L_TSNC1_LENGTH           0x00000001

#define _GSMR1L_TSNC0_POSITION         0x0000001A
#define _GSMR1L_TSNC0_MASK             0x00000001
#define _GSMR1L_TSNC0_LENGTH           0x00000001

#define _GSMR1L_TSNC_POSITION          0x0000001A
#define _GSMR1L_TSNC_MASK              0x00000003
#define _GSMR1L_TSNC_LENGTH            0x00000002

#define _GSMR1L_RINV_POSITION          0x00000019
#define _GSMR1L_RINV_MASK              0x00000001
#define _GSMR1L_RINV_LENGTH            0x00000001

#define _GSMR1L_TINV_POSITION          0x00000018
#define _GSMR1L_TINV_MASK              0x00000001
#define _GSMR1L_TINV_LENGTH            0x00000001

#define _GSMR1L_TPL2_POSITION          0x00000017
#define _GSMR1L_TPL2_MASK              0x00000001
#define _GSMR1L_TPL2_LENGTH            0x00000001

#define _GSMR1L_TPL1_POSITION          0x00000016
#define _GSMR1L_TPL1_MASK              0x00000001
#define _GSMR1L_TPL1_LENGTH            0x00000001

#define _GSMR1L_TPL0_POSITION          0x00000015
#define _GSMR1L_TPL0_MASK              0x00000001
#define _GSMR1L_TPL0_LENGTH            0x00000001

#define _GSMR1L_TPL_POSITION           0x00000015
#define _GSMR1L_TPL_MASK               0x00000007
#define _GSMR1L_TPL_LENGTH             0x00000003

#define _GSMR1L_TPP1_POSITION          0x00000014
#define _GSMR1L_TPP1_MASK              0x00000001
#define _GSMR1L_TPP1_LENGTH            0x00000001

#define _GSMR1L_TPP0_POSITION          0x00000013
#define _GSMR1L_TPP0_MASK              0x00000001
#define _GSMR1L_TPP0_LENGTH            0x00000001

#define _GSMR1L_TPP_POSITION           0x00000013
#define _GSMR1L_TPP_MASK               0x00000003
#define _GSMR1L_TPP_LENGTH             0x00000002

#define _GSMR1L_TEND_POSITION          0x00000012
#define _GSMR1L_TEND_MASK              0x00000001
#define _GSMR1L_TEND_LENGTH            0x00000001

#define _GSMR1L_TDCR1_POSITION         0x00000011
#define _GSMR1L_TDCR1_MASK             0x00000001
#define _GSMR1L_TDCR1_LENGTH           0x00000001

#define _GSMR1L_TDCR0_POSITION         0x00000010
#define _GSMR1L_TDCR0_MASK             0x00000001
#define _GSMR1L_TDCR0_LENGTH           0x00000001

#define _GSMR1L_TDCR_POSITION          0x00000010
#define _GSMR1L_TDCR_MASK              0x00000003
#define _GSMR1L_TDCR_LENGTH            0x00000002

#define _GSMR1L_RDCR1_POSITION         0x0000000F
#define _GSMR1L_RDCR1_MASK             0x00000001
#define _GSMR1L_RDCR1_LENGTH           0x00000001

#define _GSMR1L_RDCR0_POSITION         0x0000000E
#define _GSMR1L_RDCR0_MASK             0x00000001
#define _GSMR1L_RDCR0_LENGTH           0x00000001

#define _GSMR1L_RDCR_POSITION          0x0000000E
#define _GSMR1L_RDCR_MASK              0x00000003
#define _GSMR1L_RDCR_LENGTH            0x00000002

#define _GSMR1L_RENC2_POSITION         0x0000000D
#define _GSMR1L_RENC2_MASK             0x00000001
#define _GSMR1L_RENC2_LENGTH           0x00000001

#define _GSMR1L_RENC1_POSITION         0x0000000C
#define _GSMR1L_RENC1_MASK             0x00000001
#define _GSMR1L_RENC1_LENGTH           0x00000001

#define _GSMR1L_RENC0_POSITION         0x0000000B
#define _GSMR1L_RENC0_MASK             0x00000001
#define _GSMR1L_RENC0_LENGTH           0x00000001

#define _GSMR1L_RENC_POSITION          0x0000000B
#define _GSMR1L_RENC_MASK              0x00000007
#define _GSMR1L_RENC_LENGTH            0x00000003

#define _GSMR1L_TENC2_POSITION         0x0000000A
#define _GSMR1L_TENC2_MASK             0x00000001
#define _GSMR1L_TENC2_LENGTH           0x00000001

#define _GSMR1L_TENC1_POSITION         0x00000009
#define _GSMR1L_TENC1_MASK             0x00000001
#define _GSMR1L_TENC1_LENGTH           0x00000001

#define _GSMR1L_TENC0_POSITION         0x00000008
#define _GSMR1L_TENC0_MASK             0x00000001
#define _GSMR1L_TENC0_LENGTH           0x00000001

#define _GSMR1L_TENC_POSITION          0x00000008
#define _GSMR1L_TENC_MASK              0x00000007
#define _GSMR1L_TENC_LENGTH            0x00000003

#define _GSMR1L_DIAG1_POSITION         0x00000007
#define _GSMR1L_DIAG1_MASK             0x00000001
#define _GSMR1L_DIAG1_LENGTH           0x00000001

#define _GSMR1L_DIAG0_POSITION         0x00000006
#define _GSMR1L_DIAG0_MASK             0x00000001
#define _GSMR1L_DIAG0_LENGTH           0x00000001

#define _GSMR1L_DIAG_POSITION          0x00000006
#define _GSMR1L_DIAG_MASK              0x00000003
#define _GSMR1L_DIAG_LENGTH            0x00000002

#define _GSMR1L_ENR_POSITION           0x00000005
#define _GSMR1L_ENR_MASK               0x00000001
#define _GSMR1L_ENR_LENGTH             0x00000001

#define _GSMR1L_ENT_POSITION           0x00000004
#define _GSMR1L_ENT_MASK               0x00000001
#define _GSMR1L_ENT_LENGTH             0x00000001

#define _GSMR1L_MODE3_POSITION         0x00000003
#define _GSMR1L_MODE3_MASK             0x00000001
#define _GSMR1L_MODE3_LENGTH           0x00000001

#define _GSMR1L_MODE2_POSITION         0x00000002
#define _GSMR1L_MODE2_MASK             0x00000001
#define _GSMR1L_MODE2_LENGTH           0x00000001

#define _GSMR1L_MODE1_POSITION         0x00000001
#define _GSMR1L_MODE1_MASK             0x00000001
#define _GSMR1L_MODE1_LENGTH           0x00000001

#define _GSMR1L_MODE0_POSITION         0x00000000
#define _GSMR1L_MODE0_MASK             0x00000001
#define _GSMR1L_MODE0_LENGTH           0x00000001

#define _GSMR1L_MODE_POSITION          0x00000000
#define _GSMR1L_MODE_MASK              0x0000000F
#define _GSMR1L_MODE_LENGTH            0x00000004

#define _GSMR2L_EDGE1_POSITION         0x0000001E
#define _GSMR2L_EDGE1_MASK             0x00000001
#define _GSMR2L_EDGE1_LENGTH           0x00000001

#define _GSMR2L_EDGE0_POSITION         0x0000001D
#define _GSMR2L_EDGE0_MASK             0x00000001
#define _GSMR2L_EDGE0_LENGTH           0x00000001

#define _GSMR2L_EDGE_POSITION          0x0000001D
#define _GSMR2L_EDGE_MASK              0x00000003
#define _GSMR2L_EDGE_LENGTH            0x00000002

#define _GSMR2L_TCI_POSITION           0x0000001C
#define _GSMR2L_TCI_MASK               0x00000001
#define _GSMR2L_TCI_LENGTH             0x00000001

#define _GSMR2L_TSNC1_POSITION         0x0000001B
#define _GSMR2L_TSNC1_MASK             0x00000001
#define _GSMR2L_TSNC1_LENGTH           0x00000001

#define _GSMR2L_TSNC0_POSITION         0x0000001A
#define _GSMR2L_TSNC0_MASK             0x00000001
#define _GSMR2L_TSNC0_LENGTH           0x00000001

#define _GSMR2L_TSNC_POSITION          0x0000001A
#define _GSMR2L_TSNC_MASK              0x00000003
#define _GSMR2L_TSNC_LENGTH            0x00000002

#define _GSMR2L_RINV_POSITION          0x00000019
#define _GSMR2L_RINV_MASK              0x00000001
#define _GSMR2L_RINV_LENGTH            0x00000001

#define _GSMR2L_TINV_POSITION          0x00000018
#define _GSMR2L_TINV_MASK              0x00000001
#define _GSMR2L_TINV_LENGTH            0x00000001

#define _GSMR2L_TPL2_POSITION          0x00000017
#define _GSMR2L_TPL2_MASK              0x00000001
#define _GSMR2L_TPL2_LENGTH            0x00000001

#define _GSMR2L_TPL1_POSITION          0x00000016
#define _GSMR2L_TPL1_MASK              0x00000001
#define _GSMR2L_TPL1_LENGTH            0x00000001

#define _GSMR2L_TPL0_POSITION          0x00000015
#define _GSMR2L_TPL0_MASK              0x00000001
#define _GSMR2L_TPL0_LENGTH            0x00000001

#define _GSMR2L_TPL_POSITION           0x00000015
#define _GSMR2L_TPL_MASK               0x00000007
#define _GSMR2L_TPL_LENGTH             0x00000003

#define _GSMR2L_TPP1_POSITION          0x00000014
#define _GSMR2L_TPP1_MASK              0x00000001
#define _GSMR2L_TPP1_LENGTH            0x00000001

#define _GSMR2L_TPP0_POSITION          0x00000013
#define _GSMR2L_TPP0_MASK              0x00000001
#define _GSMR2L_TPP0_LENGTH            0x00000001

#define _GSMR2L_TPP_POSITION           0x00000013
#define _GSMR2L_TPP_MASK               0x00000003
#define _GSMR2L_TPP_LENGTH             0x00000002

#define _GSMR2L_TEND_POSITION          0x00000012
#define _GSMR2L_TEND_MASK              0x00000001
#define _GSMR2L_TEND_LENGTH            0x00000001

#define _GSMR2L_TDCR1_POSITION         0x00000011
#define _GSMR2L_TDCR1_MASK             0x00000001
#define _GSMR2L_TDCR1_LENGTH           0x00000001

#define _GSMR2L_TDCR0_POSITION         0x00000010
#define _GSMR2L_TDCR0_MASK             0x00000001
#define _GSMR2L_TDCR0_LENGTH           0x00000001

#define _GSMR2L_TDCR_POSITION          0x00000010
#define _GSMR2L_TDCR_MASK              0x00000003
#define _GSMR2L_TDCR_LENGTH            0x00000002

#define _GSMR2L_RDCR1_POSITION         0x0000000F
#define _GSMR2L_RDCR1_MASK             0x00000001
#define _GSMR2L_RDCR1_LENGTH           0x00000001

#define _GSMR2L_RDCR0_POSITION         0x0000000E
#define _GSMR2L_RDCR0_MASK             0x00000001
#define _GSMR2L_RDCR0_LENGTH           0x00000001

#define _GSMR2L_RDCR_POSITION          0x0000000E
#define _GSMR2L_RDCR_MASK              0x00000003
#define _GSMR2L_RDCR_LENGTH            0x00000002

#define _GSMR2L_RENC2_POSITION         0x0000000D
#define _GSMR2L_RENC2_MASK             0x00000001
#define _GSMR2L_RENC2_LENGTH           0x00000001

#define _GSMR2L_RENC1_POSITION         0x0000000C
#define _GSMR2L_RENC1_MASK             0x00000001
#define _GSMR2L_RENC1_LENGTH           0x00000001

#define _GSMR2L_RENC0_POSITION         0x0000000B
#define _GSMR2L_RENC0_MASK             0x00000001
#define _GSMR2L_RENC0_LENGTH           0x00000001

#define _GSMR2L_RENC_POSITION          0x0000000B
#define _GSMR2L_RENC_MASK              0x00000007
#define _GSMR2L_RENC_LENGTH            0x00000003

#define _GSMR2L_TENC2_POSITION         0x0000000A
#define _GSMR2L_TENC2_MASK             0x00000001
#define _GSMR2L_TENC2_LENGTH           0x00000001

#define _GSMR2L_TENC1_POSITION         0x00000009
#define _GSMR2L_TENC1_MASK             0x00000001
#define _GSMR2L_TENC1_LENGTH           0x00000001

#define _GSMR2L_TENC0_POSITION         0x00000008
#define _GSMR2L_TENC0_MASK             0x00000001
#define _GSMR2L_TENC0_LENGTH           0x00000001

#define _GSMR2L_TENC_POSITION          0x00000008
#define _GSMR2L_TENC_MASK              0x00000007
#define _GSMR2L_TENC_LENGTH            0x00000003

#define _GSMR2L_DIAG1_POSITION         0x00000007
#define _GSMR2L_DIAG1_MASK             0x00000001
#define _GSMR2L_DIAG1_LENGTH           0x00000001

#define _GSMR2L_DIAG0_POSITION         0x00000006
#define _GSMR2L_DIAG0_MASK             0x00000001
#define _GSMR2L_DIAG0_LENGTH           0x00000001

#define _GSMR2L_DIAG_POSITION          0x00000006
#define _GSMR2L_DIAG_MASK              0x00000003
#define _GSMR2L_DIAG_LENGTH            0x00000002

#define _GSMR2L_ENR_POSITION           0x00000005
#define _GSMR2L_ENR_MASK               0x00000001
#define _GSMR2L_ENR_LENGTH             0x00000001

#define _GSMR2L_ENT_POSITION           0x00000004
#define _GSMR2L_ENT_MASK               0x00000001
#define _GSMR2L_ENT_LENGTH             0x00000001

#define _GSMR2L_MODE3_POSITION         0x00000003
#define _GSMR2L_MODE3_MASK             0x00000001
#define _GSMR2L_MODE3_LENGTH           0x00000001

#define _GSMR2L_MODE2_POSITION         0x00000002
#define _GSMR2L_MODE2_MASK             0x00000001
#define _GSMR2L_MODE2_LENGTH           0x00000001

#define _GSMR2L_MODE1_POSITION         0x00000001
#define _GSMR2L_MODE1_MASK             0x00000001
#define _GSMR2L_MODE1_LENGTH           0x00000001

#define _GSMR2L_MODE0_POSITION         0x00000000
#define _GSMR2L_MODE0_MASK             0x00000001
#define _GSMR2L_MODE0_LENGTH           0x00000001

#define _GSMR2L_MODE_POSITION          0x00000000
#define _GSMR2L_MODE_MASK              0x0000000F
#define _GSMR2L_MODE_LENGTH            0x00000004

#define _GSMR3L_EDGE1_POSITION         0x0000001E
#define _GSMR3L_EDGE1_MASK             0x00000001
#define _GSMR3L_EDGE1_LENGTH           0x00000001

#define _GSMR3L_EDGE0_POSITION         0x0000001D
#define _GSMR3L_EDGE0_MASK             0x00000001
#define _GSMR3L_EDGE0_LENGTH           0x00000001

#define _GSMR3L_EDGE_POSITION          0x0000001D
#define _GSMR3L_EDGE_MASK              0x00000003
#define _GSMR3L_EDGE_LENGTH            0x00000002

#define _GSMR3L_TCI_POSITION           0x0000001C
#define _GSMR3L_TCI_MASK               0x00000001
#define _GSMR3L_TCI_LENGTH             0x00000001

#define _GSMR3L_TSNC1_POSITION         0x0000001B
#define _GSMR3L_TSNC1_MASK             0x00000001
#define _GSMR3L_TSNC1_LENGTH           0x00000001

#define _GSMR3L_TSNC0_POSITION         0x0000001A
#define _GSMR3L_TSNC0_MASK             0x00000001
#define _GSMR3L_TSNC0_LENGTH           0x00000001

#define _GSMR3L_TSNC_POSITION          0x0000001A
#define _GSMR3L_TSNC_MASK              0x00000003
#define _GSMR3L_TSNC_LENGTH            0x00000002

#define _GSMR3L_RINV_POSITION          0x00000019
#define _GSMR3L_RINV_MASK              0x00000001
#define _GSMR3L_RINV_LENGTH            0x00000001

#define _GSMR3L_TINV_POSITION          0x00000018
#define _GSMR3L_TINV_MASK              0x00000001
#define _GSMR3L_TINV_LENGTH            0x00000001

#define _GSMR3L_TPL2_POSITION          0x00000017
#define _GSMR3L_TPL2_MASK              0x00000001
#define _GSMR3L_TPL2_LENGTH            0x00000001

#define _GSMR3L_TPL1_POSITION          0x00000016
#define _GSMR3L_TPL1_MASK              0x00000001
#define _GSMR3L_TPL1_LENGTH            0x00000001

#define _GSMR3L_TPL0_POSITION          0x00000015
#define _GSMR3L_TPL0_MASK              0x00000001
#define _GSMR3L_TPL0_LENGTH            0x00000001

#define _GSMR3L_TPL_POSITION           0x00000015
#define _GSMR3L_TPL_MASK               0x00000007
#define _GSMR3L_TPL_LENGTH             0x00000003

#define _GSMR3L_TPP1_POSITION          0x00000014
#define _GSMR3L_TPP1_MASK              0x00000001
#define _GSMR3L_TPP1_LENGTH            0x00000001

#define _GSMR3L_TPP0_POSITION          0x00000013
#define _GSMR3L_TPP0_MASK              0x00000001
#define _GSMR3L_TPP0_LENGTH            0x00000001

#define _GSMR3L_TPP_POSITION           0x00000013
#define _GSMR3L_TPP_MASK               0x00000003
#define _GSMR3L_TPP_LENGTH             0x00000002

#define _GSMR3L_TEND_POSITION          0x00000012
#define _GSMR3L_TEND_MASK              0x00000001
#define _GSMR3L_TEND_LENGTH            0x00000001

#define _GSMR3L_TDCR1_POSITION         0x00000011
#define _GSMR3L_TDCR1_MASK             0x00000001
#define _GSMR3L_TDCR1_LENGTH           0x00000001

#define _GSMR3L_TDCR0_POSITION         0x00000010
#define _GSMR3L_TDCR0_MASK             0x00000001
#define _GSMR3L_TDCR0_LENGTH           0x00000001

#define _GSMR3L_TDCR_POSITION          0x00000010
#define _GSMR3L_TDCR_MASK              0x00000003
#define _GSMR3L_TDCR_LENGTH            0x00000002

#define _GSMR3L_RDCR1_POSITION         0x0000000F
#define _GSMR3L_RDCR1_MASK             0x00000001
#define _GSMR3L_RDCR1_LENGTH           0x00000001

#define _GSMR3L_RDCR0_POSITION         0x0000000E
#define _GSMR3L_RDCR0_MASK             0x00000001
#define _GSMR3L_RDCR0_LENGTH           0x00000001

#define _GSMR3L_RDCR_POSITION          0x0000000E
#define _GSMR3L_RDCR_MASK              0x00000003
#define _GSMR3L_RDCR_LENGTH            0x00000002

#define _GSMR3L_RENC2_POSITION         0x0000000D
#define _GSMR3L_RENC2_MASK             0x00000001
#define _GSMR3L_RENC2_LENGTH           0x00000001

#define _GSMR3L_RENC1_POSITION         0x0000000C
#define _GSMR3L_RENC1_MASK             0x00000001
#define _GSMR3L_RENC1_LENGTH           0x00000001

#define _GSMR3L_RENC0_POSITION         0x0000000B
#define _GSMR3L_RENC0_MASK             0x00000001
#define _GSMR3L_RENC0_LENGTH           0x00000001

#define _GSMR3L_RENC_POSITION          0x0000000B
#define _GSMR3L_RENC_MASK              0x00000007
#define _GSMR3L_RENC_LENGTH            0x00000003

#define _GSMR3L_TENC2_POSITION         0x0000000A
#define _GSMR3L_TENC2_MASK             0x00000001
#define _GSMR3L_TENC2_LENGTH           0x00000001

#define _GSMR3L_TENC1_POSITION         0x00000009
#define _GSMR3L_TENC1_MASK             0x00000001
#define _GSMR3L_TENC1_LENGTH           0x00000001

#define _GSMR3L_TENC0_POSITION         0x00000008
#define _GSMR3L_TENC0_MASK             0x00000001
#define _GSMR3L_TENC0_LENGTH           0x00000001

#define _GSMR3L_TENC_POSITION          0x00000008
#define _GSMR3L_TENC_MASK              0x00000007
#define _GSMR3L_TENC_LENGTH            0x00000003

#define _GSMR3L_DIAG1_POSITION         0x00000007
#define _GSMR3L_DIAG1_MASK             0x00000001
#define _GSMR3L_DIAG1_LENGTH           0x00000001

#define _GSMR3L_DIAG0_POSITION         0x00000006
#define _GSMR3L_DIAG0_MASK             0x00000001
#define _GSMR3L_DIAG0_LENGTH           0x00000001

#define _GSMR3L_DIAG_POSITION          0x00000006
#define _GSMR3L_DIAG_MASK              0x00000003
#define _GSMR3L_DIAG_LENGTH            0x00000002

#define _GSMR3L_ENR_POSITION           0x00000005
#define _GSMR3L_ENR_MASK               0x00000001
#define _GSMR3L_ENR_LENGTH             0x00000001

#define _GSMR3L_ENT_POSITION           0x00000004
#define _GSMR3L_ENT_MASK               0x00000001
#define _GSMR3L_ENT_LENGTH             0x00000001

#define _GSMR3L_MODE3_POSITION         0x00000003
#define _GSMR3L_MODE3_MASK             0x00000001
#define _GSMR3L_MODE3_LENGTH           0x00000001

#define _GSMR3L_MODE2_POSITION         0x00000002
#define _GSMR3L_MODE2_MASK             0x00000001
#define _GSMR3L_MODE2_LENGTH           0x00000001

#define _GSMR3L_MODE1_POSITION         0x00000001
#define _GSMR3L_MODE1_MASK             0x00000001
#define _GSMR3L_MODE1_LENGTH           0x00000001

#define _GSMR3L_MODE0_POSITION         0x00000000
#define _GSMR3L_MODE0_MASK             0x00000001
#define _GSMR3L_MODE0_LENGTH           0x00000001

#define _GSMR3L_MODE_POSITION          0x00000000
#define _GSMR3L_MODE_MASK              0x0000000F
#define _GSMR3L_MODE_LENGTH            0x00000004

#define _GSMR4L_EDGE1_POSITION         0x0000001E
#define _GSMR4L_EDGE1_MASK             0x00000001
#define _GSMR4L_EDGE1_LENGTH           0x00000001

#define _GSMR4L_EDGE0_POSITION         0x0000001D
#define _GSMR4L_EDGE0_MASK             0x00000001
#define _GSMR4L_EDGE0_LENGTH           0x00000001

#define _GSMR4L_EDGE_POSITION          0x0000001D
#define _GSMR4L_EDGE_MASK              0x00000003
#define _GSMR4L_EDGE_LENGTH            0x00000002

#define _GSMR4L_TCI_POSITION           0x0000001C
#define _GSMR4L_TCI_MASK               0x00000001
#define _GSMR4L_TCI_LENGTH             0x00000001

#define _GSMR4L_TSNC1_POSITION         0x0000001B
#define _GSMR4L_TSNC1_MASK             0x00000001
#define _GSMR4L_TSNC1_LENGTH           0x00000001

#define _GSMR4L_TSNC0_POSITION         0x0000001A
#define _GSMR4L_TSNC0_MASK             0x00000001
#define _GSMR4L_TSNC0_LENGTH           0x00000001

#define _GSMR4L_TSNC_POSITION          0x0000001A
#define _GSMR4L_TSNC_MASK              0x00000003
#define _GSMR4L_TSNC_LENGTH            0x00000002

#define _GSMR4L_RINV_POSITION          0x00000019
#define _GSMR4L_RINV_MASK              0x00000001
#define _GSMR4L_RINV_LENGTH            0x00000001

#define _GSMR4L_TINV_POSITION          0x00000018
#define _GSMR4L_TINV_MASK              0x00000001
#define _GSMR4L_TINV_LENGTH            0x00000001

#define _GSMR4L_TPL2_POSITION          0x00000017
#define _GSMR4L_TPL2_MASK              0x00000001
#define _GSMR4L_TPL2_LENGTH            0x00000001

#define _GSMR4L_TPL1_POSITION          0x00000016
#define _GSMR4L_TPL1_MASK              0x00000001
#define _GSMR4L_TPL1_LENGTH            0x00000001

#define _GSMR4L_TPL0_POSITION          0x00000015
#define _GSMR4L_TPL0_MASK              0x00000001
#define _GSMR4L_TPL0_LENGTH            0x00000001

#define _GSMR4L_TPL_POSITION           0x00000015
#define _GSMR4L_TPL_MASK               0x00000007
#define _GSMR4L_TPL_LENGTH             0x00000003

#define _GSMR4L_TPP1_POSITION          0x00000014
#define _GSMR4L_TPP1_MASK              0x00000001
#define _GSMR4L_TPP1_LENGTH            0x00000001

#define _GSMR4L_TPP0_POSITION          0x00000013
#define _GSMR4L_TPP0_MASK              0x00000001
#define _GSMR4L_TPP0_LENGTH            0x00000001

#define _GSMR4L_TPP_POSITION           0x00000013
#define _GSMR4L_TPP_MASK               0x00000003
#define _GSMR4L_TPP_LENGTH             0x00000002

#define _GSMR4L_TEND_POSITION          0x00000012
#define _GSMR4L_TEND_MASK              0x00000001
#define _GSMR4L_TEND_LENGTH            0x00000001

#define _GSMR4L_TDCR1_POSITION         0x00000011
#define _GSMR4L_TDCR1_MASK             0x00000001
#define _GSMR4L_TDCR1_LENGTH           0x00000001

#define _GSMR4L_TDCR0_POSITION         0x00000010
#define _GSMR4L_TDCR0_MASK             0x00000001
#define _GSMR4L_TDCR0_LENGTH           0x00000001

#define _GSMR4L_TDCR_POSITION          0x00000010
#define _GSMR4L_TDCR_MASK              0x00000003
#define _GSMR4L_TDCR_LENGTH            0x00000002

#define _GSMR4L_RDCR1_POSITION         0x0000000F
#define _GSMR4L_RDCR1_MASK             0x00000001
#define _GSMR4L_RDCR1_LENGTH           0x00000001

#define _GSMR4L_RDCR0_POSITION         0x0000000E
#define _GSMR4L_RDCR0_MASK             0x00000001
#define _GSMR4L_RDCR0_LENGTH           0x00000001

#define _GSMR4L_RDCR_POSITION          0x0000000E
#define _GSMR4L_RDCR_MASK              0x00000003
#define _GSMR4L_RDCR_LENGTH            0x00000002

#define _GSMR4L_RENC2_POSITION         0x0000000D
#define _GSMR4L_RENC2_MASK             0x00000001
#define _GSMR4L_RENC2_LENGTH           0x00000001

#define _GSMR4L_RENC1_POSITION         0x0000000C
#define _GSMR4L_RENC1_MASK             0x00000001
#define _GSMR4L_RENC1_LENGTH           0x00000001

#define _GSMR4L_RENC0_POSITION         0x0000000B
#define _GSMR4L_RENC0_MASK             0x00000001
#define _GSMR4L_RENC0_LENGTH           0x00000001

#define _GSMR4L_RENC_POSITION          0x0000000B
#define _GSMR4L_RENC_MASK              0x00000007
#define _GSMR4L_RENC_LENGTH            0x00000003

#define _GSMR4L_TENC2_POSITION         0x0000000A
#define _GSMR4L_TENC2_MASK             0x00000001
#define _GSMR4L_TENC2_LENGTH           0x00000001

#define _GSMR4L_TENC1_POSITION         0x00000009
#define _GSMR4L_TENC1_MASK             0x00000001
#define _GSMR4L_TENC1_LENGTH           0x00000001

#define _GSMR4L_TENC0_POSITION         0x00000008
#define _GSMR4L_TENC0_MASK             0x00000001
#define _GSMR4L_TENC0_LENGTH           0x00000001

#define _GSMR4L_TENC_POSITION          0x00000008
#define _GSMR4L_TENC_MASK              0x00000007
#define _GSMR4L_TENC_LENGTH            0x00000003

#define _GSMR4L_DIAG1_POSITION         0x00000007
#define _GSMR4L_DIAG1_MASK             0x00000001
#define _GSMR4L_DIAG1_LENGTH           0x00000001

#define _GSMR4L_DIAG0_POSITION         0x00000006
#define _GSMR4L_DIAG0_MASK             0x00000001
#define _GSMR4L_DIAG0_LENGTH           0x00000001

#define _GSMR4L_DIAG_POSITION          0x00000006
#define _GSMR4L_DIAG_MASK              0x00000003
#define _GSMR4L_DIAG_LENGTH            0x00000002

#define _GSMR4L_ENR_POSITION           0x00000005
#define _GSMR4L_ENR_MASK               0x00000001
#define _GSMR4L_ENR_LENGTH             0x00000001

#define _GSMR4L_ENT_POSITION           0x00000004
#define _GSMR4L_ENT_MASK               0x00000001
#define _GSMR4L_ENT_LENGTH             0x00000001

#define _GSMR4L_MODE3_POSITION         0x00000003
#define _GSMR4L_MODE3_MASK             0x00000001
#define _GSMR4L_MODE3_LENGTH           0x00000001

#define _GSMR4L_MODE2_POSITION         0x00000002
#define _GSMR4L_MODE2_MASK             0x00000001
#define _GSMR4L_MODE2_LENGTH           0x00000001

#define _GSMR4L_MODE1_POSITION         0x00000001
#define _GSMR4L_MODE1_MASK             0x00000001
#define _GSMR4L_MODE1_LENGTH           0x00000001

#define _GSMR4L_MODE0_POSITION         0x00000000
#define _GSMR4L_MODE0_MASK             0x00000001
#define _GSMR4L_MODE0_LENGTH           0x00000001

#define _GSMR4L_MODE_POSITION          0x00000000
#define _GSMR4L_MODE_MASK              0x0000000F
#define _GSMR4L_MODE_LENGTH            0x00000004

#define _GSMR1H_GDE_POSITION           0x00000010
#define _GSMR1H_GDE_MASK               0x00000001
#define _GSMR1H_GDE_LENGTH             0x00000001

#define _GSMR1H_TCRC1_POSITION         0x0000000F
#define _GSMR1H_TCRC1_MASK             0x00000001
#define _GSMR1H_TCRC1_LENGTH           0x00000001

#define _GSMR1H_TCRC0_POSITION         0x0000000E
#define _GSMR1H_TCRC0_MASK             0x00000001
#define _GSMR1H_TCRC0_LENGTH           0x00000001

#define _GSMR1H_TCRC_POSITION          0x0000000E
#define _GSMR1H_TCRC_MASK              0x00000003
#define _GSMR1H_TCRC_LENGTH            0x00000002

#define _GSMR1H_REVD_POSITION          0x0000000D
#define _GSMR1H_REVD_MASK              0x00000001
#define _GSMR1H_REVD_LENGTH            0x00000001

#define _GSMR1H_TRX_POSITION           0x0000000C
#define _GSMR1H_TRX_MASK               0x00000001
#define _GSMR1H_TRX_LENGTH             0x00000001

#define _GSMR1H_TTX_POSITION           0x0000000B
#define _GSMR1H_TTX_MASK               0x00000001
#define _GSMR1H_TTX_LENGTH             0x00000001

#define _GSMR1H_CDP_POSITION           0x0000000A
#define _GSMR1H_CDP_MASK               0x00000001
#define _GSMR1H_CDP_LENGTH             0x00000001

#define _GSMR1H_CTSP_POSITION          0x00000009
#define _GSMR1H_CTSP_MASK              0x00000001
#define _GSMR1H_CTSP_LENGTH            0x00000001

#define _GSMR1H_CDS_POSITION           0x00000008
#define _GSMR1H_CDS_MASK               0x00000001
#define _GSMR1H_CDS_LENGTH             0x00000001

#define _GSMR1H_CTSS_POSITION          0x00000007
#define _GSMR1H_CTSS_MASK              0x00000001
#define _GSMR1H_CTSS_LENGTH            0x00000001

#define _GSMR1H_TFL_POSITION           0x00000006
#define _GSMR1H_TFL_MASK               0x00000001
#define _GSMR1H_TFL_LENGTH             0x00000001

#define _GSMR1H_RFW_POSITION           0x00000005
#define _GSMR1H_RFW_MASK               0x00000001
#define _GSMR1H_RFW_LENGTH             0x00000001

#define _GSMR1H_TXSY_POSITION          0x00000004
#define _GSMR1H_TXSY_MASK              0x00000001
#define _GSMR1H_TXSY_LENGTH            0x00000001

#define _GSMR1H_SYNL1_POSITION         0x00000003
#define _GSMR1H_SYNL1_MASK             0x00000001
#define _GSMR1H_SYNL1_LENGTH           0x00000001

#define _GSMR1H_SYNL0_POSITION         0x00000002
#define _GSMR1H_SYNL0_MASK             0x00000001
#define _GSMR1H_SYNL0_LENGTH           0x00000001

#define _GSMR1H_SYNL_POSITION          0x00000002
#define _GSMR1H_SYNL_MASK              0x00000003
#define _GSMR1H_SYNL_LENGTH            0x00000002

#define _GSMR1H_RTSM_POSITION          0x00000001
#define _GSMR1H_RTSM_MASK              0x00000001
#define _GSMR1H_RTSM_LENGTH            0x00000001

#define _GSMR1H_RSYN_POSITION          0x00000000
#define _GSMR1H_RSYN_MASK              0x00000001
#define _GSMR1H_RSYN_LENGTH            0x00000001

#define _GSMR2H_GDE_POSITION           0x00000010
#define _GSMR2H_GDE_MASK               0x00000001
#define _GSMR2H_GDE_LENGTH             0x00000001

#define _GSMR2H_TCRC1_POSITION         0x0000000F
#define _GSMR2H_TCRC1_MASK             0x00000001
#define _GSMR2H_TCRC1_LENGTH           0x00000001

#define _GSMR2H_TCRC0_POSITION         0x0000000E
#define _GSMR2H_TCRC0_MASK             0x00000001
#define _GSMR2H_TCRC0_LENGTH           0x00000001

#define _GSMR2H_TCRC_POSITION          0x0000000E
#define _GSMR2H_TCRC_MASK              0x00000003
#define _GSMR2H_TCRC_LENGTH            0x00000002

#define _GSMR2H_REVD_POSITION          0x0000000D
#define _GSMR2H_REVD_MASK              0x00000001
#define _GSMR2H_REVD_LENGTH            0x00000001

#define _GSMR2H_TRX_POSITION           0x0000000C
#define _GSMR2H_TRX_MASK               0x00000001
#define _GSMR2H_TRX_LENGTH             0x00000001

#define _GSMR2H_TTX_POSITION           0x0000000B
#define _GSMR2H_TTX_MASK               0x00000001
#define _GSMR2H_TTX_LENGTH             0x00000001

#define _GSMR2H_CDP_POSITION           0x0000000A
#define _GSMR2H_CDP_MASK               0x00000001
#define _GSMR2H_CDP_LENGTH             0x00000001

#define _GSMR2H_CTSP_POSITION          0x00000009
#define _GSMR2H_CTSP_MASK              0x00000001
#define _GSMR2H_CTSP_LENGTH            0x00000001

#define _GSMR2H_CDS_POSITION           0x00000008
#define _GSMR2H_CDS_MASK               0x00000001
#define _GSMR2H_CDS_LENGTH             0x00000001

#define _GSMR2H_CTSS_POSITION          0x00000007
#define _GSMR2H_CTSS_MASK              0x00000001
#define _GSMR2H_CTSS_LENGTH            0x00000001

#define _GSMR2H_TFL_POSITION           0x00000006
#define _GSMR2H_TFL_MASK               0x00000001
#define _GSMR2H_TFL_LENGTH             0x00000001

#define _GSMR2H_RFW_POSITION           0x00000005
#define _GSMR2H_RFW_MASK               0x00000001
#define _GSMR2H_RFW_LENGTH             0x00000001

#define _GSMR2H_TXSY_POSITION          0x00000004
#define _GSMR2H_TXSY_MASK              0x00000001
#define _GSMR2H_TXSY_LENGTH            0x00000001

#define _GSMR2H_SYNL1_POSITION         0x00000003
#define _GSMR2H_SYNL1_MASK             0x00000001
#define _GSMR2H_SYNL1_LENGTH           0x00000001

#define _GSMR2H_SYNL0_POSITION         0x00000002
#define _GSMR2H_SYNL0_MASK             0x00000001
#define _GSMR2H_SYNL0_LENGTH           0x00000001

#define _GSMR2H_SYNL_POSITION          0x00000002
#define _GSMR2H_SYNL_MASK              0x00000003
#define _GSMR2H_SYNL_LENGTH            0x00000002

#define _GSMR2H_RTSM_POSITION          0x00000001
#define _GSMR2H_RTSM_MASK              0x00000001
#define _GSMR2H_RTSM_LENGTH            0x00000001

#define _GSMR2H_RSYN_POSITION          0x00000000
#define _GSMR2H_RSYN_MASK              0x00000001
#define _GSMR2H_RSYN_LENGTH            0x00000001

#define _GSMR3H_GDE_POSITION           0x00000010
#define _GSMR3H_GDE_MASK               0x00000001
#define _GSMR3H_GDE_LENGTH             0x00000001

#define _GSMR3H_TCRC1_POSITION         0x0000000F
#define _GSMR3H_TCRC1_MASK             0x00000001
#define _GSMR3H_TCRC1_LENGTH           0x00000001

#define _GSMR3H_TCRC0_POSITION         0x0000000E
#define _GSMR3H_TCRC0_MASK             0x00000001
#define _GSMR3H_TCRC0_LENGTH           0x00000001

#define _GSMR3H_TCRC_POSITION          0x0000000E
#define _GSMR3H_TCRC_MASK              0x00000003
#define _GSMR3H_TCRC_LENGTH            0x00000002

#define _GSMR3H_REVD_POSITION          0x0000000D
#define _GSMR3H_REVD_MASK              0x00000001
#define _GSMR3H_REVD_LENGTH            0x00000001

#define _GSMR3H_TRX_POSITION           0x0000000C
#define _GSMR3H_TRX_MASK               0x00000001
#define _GSMR3H_TRX_LENGTH             0x00000001

#define _GSMR3H_TTX_POSITION           0x0000000B
#define _GSMR3H_TTX_MASK               0x00000001
#define _GSMR3H_TTX_LENGTH             0x00000001

#define _GSMR3H_CDP_POSITION           0x0000000A
#define _GSMR3H_CDP_MASK               0x00000001
#define _GSMR3H_CDP_LENGTH             0x00000001

#define _GSMR3H_CTSP_POSITION          0x00000009
#define _GSMR3H_CTSP_MASK              0x00000001
#define _GSMR3H_CTSP_LENGTH            0x00000001

#define _GSMR3H_CDS_POSITION           0x00000008
#define _GSMR3H_CDS_MASK               0x00000001
#define _GSMR3H_CDS_LENGTH             0x00000001

#define _GSMR3H_CTSS_POSITION          0x00000007
#define _GSMR3H_CTSS_MASK              0x00000001
#define _GSMR3H_CTSS_LENGTH            0x00000001

#define _GSMR3H_TFL_POSITION           0x00000006
#define _GSMR3H_TFL_MASK               0x00000001
#define _GSMR3H_TFL_LENGTH             0x00000001

#define _GSMR3H_RFW_POSITION           0x00000005
#define _GSMR3H_RFW_MASK               0x00000001
#define _GSMR3H_RFW_LENGTH             0x00000001

#define _GSMR3H_TXSY_POSITION          0x00000004
#define _GSMR3H_TXSY_MASK              0x00000001
#define _GSMR3H_TXSY_LENGTH            0x00000001

#define _GSMR3H_SYNL1_POSITION         0x00000003
#define _GSMR3H_SYNL1_MASK             0x00000001
#define _GSMR3H_SYNL1_LENGTH           0x00000001

#define _GSMR3H_SYNL0_POSITION         0x00000002
#define _GSMR3H_SYNL0_MASK             0x00000001
#define _GSMR3H_SYNL0_LENGTH           0x00000001

#define _GSMR3H_SYNL_POSITION          0x00000002
#define _GSMR3H_SYNL_MASK              0x00000003
#define _GSMR3H_SYNL_LENGTH            0x00000002

#define _GSMR3H_RTSM_POSITION          0x00000001
#define _GSMR3H_RTSM_MASK              0x00000001
#define _GSMR3H_RTSM_LENGTH            0x00000001

#define _GSMR3H_RSYN_POSITION          0x00000000
#define _GSMR3H_RSYN_MASK              0x00000001
#define _GSMR3H_RSYN_LENGTH            0x00000001

#define _GSMR4H_GDE_POSITION           0x00000010
#define _GSMR4H_GDE_MASK               0x00000001
#define _GSMR4H_GDE_LENGTH             0x00000001

#define _GSMR4H_TCRC1_POSITION         0x0000000F
#define _GSMR4H_TCRC1_MASK             0x00000001
#define _GSMR4H_TCRC1_LENGTH           0x00000001

#define _GSMR4H_TCRC0_POSITION         0x0000000E
#define _GSMR4H_TCRC0_MASK             0x00000001
#define _GSMR4H_TCRC0_LENGTH           0x00000001

#define _GSMR4H_TCRC_POSITION          0x0000000E
#define _GSMR4H_TCRC_MASK              0x00000003
#define _GSMR4H_TCRC_LENGTH            0x00000002

#define _GSMR4H_REVD_POSITION          0x0000000D
#define _GSMR4H_REVD_MASK              0x00000001
#define _GSMR4H_REVD_LENGTH            0x00000001

#define _GSMR4H_TRX_POSITION           0x0000000C
#define _GSMR4H_TRX_MASK               0x00000001
#define _GSMR4H_TRX_LENGTH             0x00000001

#define _GSMR4H_TTX_POSITION           0x0000000B
#define _GSMR4H_TTX_MASK               0x00000001
#define _GSMR4H_TTX_LENGTH             0x00000001

#define _GSMR4H_CDP_POSITION           0x0000000A
#define _GSMR4H_CDP_MASK               0x00000001
#define _GSMR4H_CDP_LENGTH             0x00000001

#define _GSMR4H_CTSP_POSITION          0x00000009
#define _GSMR4H_CTSP_MASK              0x00000001
#define _GSMR4H_CTSP_LENGTH            0x00000001

#define _GSMR4H_CDS_POSITION           0x00000008
#define _GSMR4H_CDS_MASK               0x00000001
#define _GSMR4H_CDS_LENGTH             0x00000001

#define _GSMR4H_CTSS_POSITION          0x00000007
#define _GSMR4H_CTSS_MASK              0x00000001
#define _GSMR4H_CTSS_LENGTH            0x00000001

#define _GSMR4H_TFL_POSITION           0x00000006
#define _GSMR4H_TFL_MASK               0x00000001
#define _GSMR4H_TFL_LENGTH             0x00000001

#define _GSMR4H_RFW_POSITION           0x00000005
#define _GSMR4H_RFW_MASK               0x00000001
#define _GSMR4H_RFW_LENGTH             0x00000001

#define _GSMR4H_TXSY_POSITION          0x00000004
#define _GSMR4H_TXSY_MASK              0x00000001
#define _GSMR4H_TXSY_LENGTH            0x00000001

#define _GSMR4H_SYNL1_POSITION         0x00000003
#define _GSMR4H_SYNL1_MASK             0x00000001
#define _GSMR4H_SYNL1_LENGTH           0x00000001

#define _GSMR4H_SYNL0_POSITION         0x00000002
#define _GSMR4H_SYNL0_MASK             0x00000001
#define _GSMR4H_SYNL0_LENGTH           0x00000001

#define _GSMR4H_SYNL_POSITION          0x00000002
#define _GSMR4H_SYNL_MASK              0x00000003
#define _GSMR4H_SYNL_LENGTH            0x00000002

#define _GSMR4H_RTSM_POSITION          0x00000001
#define _GSMR4H_RTSM_MASK              0x00000001
#define _GSMR4H_RTSM_LENGTH            0x00000001

#define _GSMR4H_RSYN_POSITION          0x00000000
#define _GSMR4H_RSYN_MASK              0x00000001
#define _GSMR4H_RSYN_LENGTH            0x00000001

#define _TODR1_TOD_POSITION            0x0000000F
#define _TODR1_TOD_MASK                0x00000001
#define _TODR1_TOD_LENGTH              0x00000001

#define _TODR2_TOD_POSITION            0x0000000F
#define _TODR2_TOD_MASK                0x00000001
#define _TODR2_TOD_LENGTH              0x00000001

#define _TODR3_TOD_POSITION            0x0000000F
#define _TODR3_TOD_MASK                0x00000001
#define _TODR3_TOD_LENGTH              0x00000001

#define _TODR4_TOD_POSITION            0x0000000F
#define _TODR4_TOD_MASK                0x00000001
#define _TODR4_TOD_LENGTH              0x00000001

#define _DSR1_SYN2_POSITION            0x00000008
#define _DSR1_SYN2_MASK                0x000000FF
#define _DSR1_SYN2_LENGTH              0x00000008

#define _DSR1_SYN1_POSITION            0x00000000
#define _DSR1_SYN1_MASK                0x000000FF
#define _DSR1_SYN1_LENGTH              0x00000008

#define _DSR2_SYN2_POSITION            0x00000008
#define _DSR2_SYN2_MASK                0x000000FF
#define _DSR2_SYN2_LENGTH              0x00000008

#define _DSR2_SYN1_POSITION            0x00000000
#define _DSR2_SYN1_MASK                0x000000FF
#define _DSR2_SYN1_LENGTH              0x00000008

#define _DSR3_SYN2_POSITION            0x00000008
#define _DSR3_SYN2_MASK                0x000000FF
#define _DSR3_SYN2_LENGTH              0x00000008

#define _DSR3_SYN1_POSITION            0x00000000
#define _DSR3_SYN1_MASK                0x000000FF
#define _DSR3_SYN1_LENGTH              0x00000008

#define _DSR4_SYN2_POSITION            0x00000008
#define _DSR4_SYN2_MASK                0x000000FF
#define _DSR4_SYN2_LENGTH              0x00000008

#define _DSR4_SYN1_POSITION            0x00000000
#define _DSR4_SYN1_MASK                0x000000FF
#define _DSR4_SYN1_LENGTH              0x00000008

#define _SCCS1_ID_POSITION             0x00000000
#define _SCCS1_ID_MASK                 0x00000001
#define _SCCS1_ID_LENGTH               0x00000001

#define _SCCS2_ID_POSITION             0x00000000
#define _SCCS2_ID_MASK                 0x00000001
#define _SCCS2_ID_LENGTH               0x00000001

#define _SCCS3_ID_POSITION             0x00000000
#define _SCCS3_ID_MASK                 0x00000001
#define _SCCS3_ID_LENGTH               0x00000001

#define _SCCS4_ID_POSITION             0x00000000
#define _SCCS4_ID_MASK                 0x00000001
#define _SCCS4_ID_LENGTH               0x00000001

#define _SMCMR1_CLEN3_POSITION         0x0000000E
#define _SMCMR1_CLEN3_MASK             0x00000001
#define _SMCMR1_CLEN3_LENGTH           0x00000001

#define _SMCMR1_CLEN2_POSITION         0x0000000D
#define _SMCMR1_CLEN2_MASK             0x00000001
#define _SMCMR1_CLEN2_LENGTH           0x00000001

#define _SMCMR1_CLEN1_POSITION         0x0000000C
#define _SMCMR1_CLEN1_MASK             0x00000001
#define _SMCMR1_CLEN1_LENGTH           0x00000001

#define _SMCMR1_CLEN0_POSITION         0x0000000B
#define _SMCMR1_CLEN0_MASK             0x00000001
#define _SMCMR1_CLEN0_LENGTH           0x00000001

#define _SMCMR1_CLEN_POSITION          0x0000000B
#define _SMCMR1_CLEN_MASK              0x0000000F
#define _SMCMR1_CLEN_LENGTH            0x00000004

#define _SMCMR1_SL_POSITION            0x0000000A
#define _SMCMR1_SL_MASK                0x00000001
#define _SMCMR1_SL_LENGTH              0x00000001

#define _SMCMR1_PEN_POSITION           0x00000009
#define _SMCMR1_PEN_MASK               0x00000001
#define _SMCMR1_PEN_LENGTH             0x00000001

#define _SMCMR1_PM_POSITION            0x00000008
#define _SMCMR1_PM_MASK                0x00000001
#define _SMCMR1_PM_LENGTH              0x00000001

#define _SMCMR1_SM1_POSITION           0x00000005
#define _SMCMR1_SM1_MASK               0x00000001
#define _SMCMR1_SM1_LENGTH             0x00000001

#define _SMCMR1_SM0_POSITION           0x00000004
#define _SMCMR1_SM0_MASK               0x00000001
#define _SMCMR1_SM0_LENGTH             0x00000001

#define _SMCMR1_SM_POSITION            0x00000004
#define _SMCMR1_SM_MASK                0x00000003
#define _SMCMR1_SM_LENGTH              0x00000002

#define _SMCMR1_DM1_POSITION           0x00000003
#define _SMCMR1_DM1_MASK               0x00000001
#define _SMCMR1_DM1_LENGTH             0x00000001

#define _SMCMR1_DM0_POSITION           0x00000002
#define _SMCMR1_DM0_MASK               0x00000001
#define _SMCMR1_DM0_LENGTH             0x00000001

#define _SMCMR1_DM_POSITION            0x00000002
#define _SMCMR1_DM_MASK                0x00000003
#define _SMCMR1_DM_LENGTH              0x00000002

#define _SMCMR1_TEN_POSITION           0x00000001
#define _SMCMR1_TEN_MASK               0x00000001
#define _SMCMR1_TEN_LENGTH             0x00000001

#define _SMCMR1_REN_POSITION           0x00000000
#define _SMCMR1_REN_MASK               0x00000001
#define _SMCMR1_REN_LENGTH             0x00000001

#define _SMCMR2_CLEN3_POSITION         0x0000000E
#define _SMCMR2_CLEN3_MASK             0x00000001
#define _SMCMR2_CLEN3_LENGTH           0x00000001

#define _SMCMR2_CLEN2_POSITION         0x0000000D
#define _SMCMR2_CLEN2_MASK             0x00000001
#define _SMCMR2_CLEN2_LENGTH           0x00000001

#define _SMCMR2_CLEN1_POSITION         0x0000000C
#define _SMCMR2_CLEN1_MASK             0x00000001
#define _SMCMR2_CLEN1_LENGTH           0x00000001

#define _SMCMR2_CLEN0_POSITION         0x0000000B
#define _SMCMR2_CLEN0_MASK             0x00000001
#define _SMCMR2_CLEN0_LENGTH           0x00000001

#define _SMCMR2_CLEN_POSITION          0x0000000B
#define _SMCMR2_CLEN_MASK              0x0000000F
#define _SMCMR2_CLEN_LENGTH            0x00000004

#define _SMCMR2_SL_POSITION            0x0000000A
#define _SMCMR2_SL_MASK                0x00000001
#define _SMCMR2_SL_LENGTH              0x00000001

#define _SMCMR2_PEN_POSITION           0x00000009
#define _SMCMR2_PEN_MASK               0x00000001
#define _SMCMR2_PEN_LENGTH             0x00000001

#define _SMCMR2_PM_POSITION            0x00000008
#define _SMCMR2_PM_MASK                0x00000001
#define _SMCMR2_PM_LENGTH              0x00000001

#define _SMCMR2_SM1_POSITION           0x00000005
#define _SMCMR2_SM1_MASK               0x00000001
#define _SMCMR2_SM1_LENGTH             0x00000001

#define _SMCMR2_SM0_POSITION           0x00000004
#define _SMCMR2_SM0_MASK               0x00000001
#define _SMCMR2_SM0_LENGTH             0x00000001

#define _SMCMR2_SM_POSITION            0x00000004
#define _SMCMR2_SM_MASK                0x00000003
#define _SMCMR2_SM_LENGTH              0x00000002

#define _SMCMR2_DM1_POSITION           0x00000003
#define _SMCMR2_DM1_MASK               0x00000001
#define _SMCMR2_DM1_LENGTH             0x00000001

#define _SMCMR2_DM0_POSITION           0x00000002
#define _SMCMR2_DM0_MASK               0x00000001
#define _SMCMR2_DM0_LENGTH             0x00000001

#define _SMCMR2_DM_POSITION            0x00000002
#define _SMCMR2_DM_MASK                0x00000003
#define _SMCMR2_DM_LENGTH              0x00000002

#define _SMCMR2_TEN_POSITION           0x00000001
#define _SMCMR2_TEN_MASK               0x00000001
#define _SMCMR2_TEN_LENGTH             0x00000001

#define _SMCMR2_REN_POSITION           0x00000000
#define _SMCMR2_REN_MASK               0x00000001
#define _SMCMR2_REN_LENGTH             0x00000001

#define _SMCE1_BRKE_POSITION           0x00000006
#define _SMCE1_BRKE_MASK               0x00000001
#define _SMCE1_BRKE_LENGTH             0x00000001

#define _SMCE1_BRK_POSITION            0x00000004
#define _SMCE1_BRK_MASK                0x00000001
#define _SMCE1_BRK_LENGTH              0x00000001

#define _SMCE1_BSY_POSITION            0x00000002
#define _SMCE1_BSY_MASK                0x00000001
#define _SMCE1_BSY_LENGTH              0x00000001

#define _SMCE1_TX_POSITION             0x00000001
#define _SMCE1_TX_MASK                 0x00000001
#define _SMCE1_TX_LENGTH               0x00000001

#define _SMCE1_RX_POSITION             0x00000000
#define _SMCE1_RX_MASK                 0x00000001
#define _SMCE1_RX_LENGTH               0x00000001

#define _SMCE2_BRKE_POSITION           0x00000006
#define _SMCE2_BRKE_MASK               0x00000001
#define _SMCE2_BRKE_LENGTH             0x00000001

#define _SMCE2_BRK_POSITION            0x00000004
#define _SMCE2_BRK_MASK                0x00000001
#define _SMCE2_BRK_LENGTH              0x00000001

#define _SMCE2_BSY_POSITION            0x00000002
#define _SMCE2_BSY_MASK                0x00000001
#define _SMCE2_BSY_LENGTH              0x00000001

#define _SMCE2_TX_POSITION             0x00000001
#define _SMCE2_TX_MASK                 0x00000001
#define _SMCE2_TX_LENGTH               0x00000001

#define _SMCE2_RX_POSITION             0x00000000
#define _SMCE2_RX_MASK                 0x00000001
#define _SMCE2_RX_LENGTH               0x00000001

#define _SMCM1_BRKE_POSITION           0x00000006
#define _SMCM1_BRKE_MASK               0x00000001
#define _SMCM1_BRKE_LENGTH             0x00000001

#define _SMCM1_BRK_POSITION            0x00000004
#define _SMCM1_BRK_MASK                0x00000001
#define _SMCM1_BRK_LENGTH              0x00000001

#define _SMCM1_BSY_POSITION            0x00000002
#define _SMCM1_BSY_MASK                0x00000001
#define _SMCM1_BSY_LENGTH              0x00000001

#define _SMCM1_TX_POSITION             0x00000001
#define _SMCM1_TX_MASK                 0x00000001
#define _SMCM1_TX_LENGTH               0x00000001

#define _SMCM1_RX_POSITION             0x00000000
#define _SMCM1_RX_MASK                 0x00000001
#define _SMCM1_RX_LENGTH               0x00000001

#define _SMCM2_BRKE_POSITION           0x00000006
#define _SMCM2_BRKE_MASK               0x00000001
#define _SMCM2_BRKE_LENGTH             0x00000001

#define _SMCM2_BRK_POSITION            0x00000004
#define _SMCM2_BRK_MASK                0x00000001
#define _SMCM2_BRK_LENGTH              0x00000001

#define _SMCM2_BSY_POSITION            0x00000002
#define _SMCM2_BSY_MASK                0x00000001
#define _SMCM2_BSY_LENGTH              0x00000001

#define _SMCM2_TX_POSITION             0x00000001
#define _SMCM2_TX_MASK                 0x00000001
#define _SMCM2_TX_LENGTH               0x00000001

#define _SMCM2_RX_POSITION             0x00000000
#define _SMCM2_RX_MASK                 0x00000001
#define _SMCM2_RX_LENGTH               0x00000001

#define _SPMODE_LOOP_POSITION          0x0000000E
#define _SPMODE_LOOP_MASK              0x00000001
#define _SPMODE_LOOP_LENGTH            0x00000001

#define _SPMODE_CI_POSITION            0x0000000D
#define _SPMODE_CI_MASK                0x00000001
#define _SPMODE_CI_LENGTH              0x00000001

#define _SPMODE_CP_POSITION            0x0000000C
#define _SPMODE_CP_MASK                0x00000001
#define _SPMODE_CP_LENGTH              0x00000001

#define _SPMODE_DIV16_POSITION         0x0000000B
#define _SPMODE_DIV16_MASK             0x00000001
#define _SPMODE_DIV16_LENGTH           0x00000001

#define _SPMODE_REV_POSITION           0x0000000A
#define _SPMODE_REV_MASK               0x00000001
#define _SPMODE_REV_LENGTH             0x00000001

#define _SPMODE_MS_POSITION            0x00000009
#define _SPMODE_MS_MASK                0x00000001
#define _SPMODE_MS_LENGTH              0x00000001

#define _SPMODE_EN_POSITION            0x00000008
#define _SPMODE_EN_MASK                0x00000001
#define _SPMODE_EN_LENGTH              0x00000001

#define _SPMODE_LEN3_POSITION          0x00000007
#define _SPMODE_LEN3_MASK              0x00000001
#define _SPMODE_LEN3_LENGTH            0x00000001

#define _SPMODE_LEN2_POSITION          0x00000006
#define _SPMODE_LEN2_MASK              0x00000001
#define _SPMODE_LEN2_LENGTH            0x00000001

#define _SPMODE_LEN1_POSITION          0x00000005
#define _SPMODE_LEN1_MASK              0x00000001
#define _SPMODE_LEN1_LENGTH            0x00000001

#define _SPMODE_LEN0_POSITION          0x00000004
#define _SPMODE_LEN0_MASK              0x00000001
#define _SPMODE_LEN0_LENGTH            0x00000001

#define _SPMODE_LEN_POSITION           0x00000004
#define _SPMODE_LEN_MASK               0x0000000F
#define _SPMODE_LEN_LENGTH             0x00000004

#define _SPMODE_PM3_POSITION           0x00000003
#define _SPMODE_PM3_MASK               0x00000001
#define _SPMODE_PM3_LENGTH             0x00000001

#define _SPMODE_PM2_POSITION           0x00000002
#define _SPMODE_PM2_MASK               0x00000001
#define _SPMODE_PM2_LENGTH             0x00000001

#define _SPMODE_PM1_POSITION           0x00000001
#define _SPMODE_PM1_MASK               0x00000001
#define _SPMODE_PM1_LENGTH             0x00000001

#define _SPMODE_PM0_POSITION           0x00000000
#define _SPMODE_PM0_MASK               0x00000001
#define _SPMODE_PM0_LENGTH             0x00000001

#define _SPMODE_PM_POSITION            0x00000000
#define _SPMODE_PM_MASK                0x0000000F
#define _SPMODE_PM_LENGTH              0x00000004

#define _SPIE_MME_POSITION             0x00000005
#define _SPIE_MME_MASK                 0x00000001
#define _SPIE_MME_LENGTH               0x00000001

#define _SPIE_TXE_POSITION             0x00000004
#define _SPIE_TXE_MASK                 0x00000001
#define _SPIE_TXE_LENGTH               0x00000001

#define _SPIE_BSY_POSITION             0x00000002
#define _SPIE_BSY_MASK                 0x00000001
#define _SPIE_BSY_LENGTH               0x00000001

#define _SPIE_RXB_POSITION             0x00000001
#define _SPIE_RXB_MASK                 0x00000001
#define _SPIE_RXB_LENGTH               0x00000001

#define _SPIE_TXB_POSITION             0x00000000
#define _SPIE_TXB_MASK                 0x00000001
#define _SPIE_TXB_LENGTH               0x00000001

#define _SPIM_MME_POSITION             0x00000005
#define _SPIM_MME_MASK                 0x00000001
#define _SPIM_MME_LENGTH               0x00000001

#define _SPIM_TXE_POSITION             0x00000004
#define _SPIM_TXE_MASK                 0x00000001
#define _SPIM_TXE_LENGTH               0x00000001

#define _SPIM_BSY_POSITION             0x00000002
#define _SPIM_BSY_MASK                 0x00000001
#define _SPIM_BSY_LENGTH               0x00000001

#define _SPIM_RXB_POSITION             0x00000001
#define _SPIM_RXB_MASK                 0x00000001
#define _SPIM_RXB_LENGTH               0x00000001

#define _SPIM_TXB_POSITION             0x00000000
#define _SPIM_TXB_MASK                 0x00000001
#define _SPIM_TXB_LENGTH               0x00000001

#define _SPCOM_STR_POSITION            0x00000007
#define _SPCOM_STR_MASK                0x00000001
#define _SPCOM_STR_LENGTH              0x00000001

#define _PBDIR_DR17_POSITION           0x00000011
#define _PBDIR_DR17_MASK               0x00000001
#define _PBDIR_DR17_LENGTH             0x00000001

#define _PBDIR_DR16_POSITION           0x00000010
#define _PBDIR_DR16_MASK               0x00000001
#define _PBDIR_DR16_LENGTH             0x00000001

#define _PBDIR_DR15_POSITION           0x0000000F
#define _PBDIR_DR15_MASK               0x00000001
#define _PBDIR_DR15_LENGTH             0x00000001

#define _PBDIR_DR14_POSITION           0x0000000E
#define _PBDIR_DR14_MASK               0x00000001
#define _PBDIR_DR14_LENGTH             0x00000001

#define _PBDIR_DR13_POSITION           0x0000000D
#define _PBDIR_DR13_MASK               0x00000001
#define _PBDIR_DR13_LENGTH             0x00000001

#define _PBDIR_DR12_POSITION           0x0000000C
#define _PBDIR_DR12_MASK               0x00000001
#define _PBDIR_DR12_LENGTH             0x00000001

#define _PBDIR_DR11_POSITION           0x0000000B
#define _PBDIR_DR11_MASK               0x00000001
#define _PBDIR_DR11_LENGTH             0x00000001

#define _PBDIR_DR10_POSITION           0x0000000A
#define _PBDIR_DR10_MASK               0x00000001
#define _PBDIR_DR10_LENGTH             0x00000001

#define _PBDIR_DR9_POSITION            0x00000009
#define _PBDIR_DR9_MASK                0x00000001
#define _PBDIR_DR9_LENGTH              0x00000001

#define _PBDIR_DR8_POSITION            0x00000008
#define _PBDIR_DR8_MASK                0x00000001
#define _PBDIR_DR8_LENGTH              0x00000001

#define _PBDIR_DR7_POSITION            0x00000007
#define _PBDIR_DR7_MASK                0x00000001
#define _PBDIR_DR7_LENGTH              0x00000001

#define _PBDIR_DR6_POSITION            0x00000006
#define _PBDIR_DR6_MASK                0x00000001
#define _PBDIR_DR6_LENGTH              0x00000001

#define _PBDIR_DR5_POSITION            0x00000005
#define _PBDIR_DR5_MASK                0x00000001
#define _PBDIR_DR5_LENGTH              0x00000001

#define _PBDIR_DR4_POSITION            0x00000004
#define _PBDIR_DR4_MASK                0x00000001
#define _PBDIR_DR4_LENGTH              0x00000001

#define _PBDIR_DR3_POSITION            0x00000003
#define _PBDIR_DR3_MASK                0x00000001
#define _PBDIR_DR3_LENGTH              0x00000001

#define _PBDIR_DR2_POSITION            0x00000002
#define _PBDIR_DR2_MASK                0x00000001
#define _PBDIR_DR2_LENGTH              0x00000001

#define _PBDIR_DR1_POSITION            0x00000001
#define _PBDIR_DR1_MASK                0x00000001
#define _PBDIR_DR1_LENGTH              0x00000001

#define _PBDIR_DR0_POSITION            0x00000000
#define _PBDIR_DR0_MASK                0x00000001
#define _PBDIR_DR0_LENGTH              0x00000001

#define _PBPAR_DD17_POSITION           0x00000011
#define _PBPAR_DD17_MASK               0x00000001
#define _PBPAR_DD17_LENGTH             0x00000001

#define _PBPAR_DD16_POSITION           0x00000010
#define _PBPAR_DD16_MASK               0x00000001
#define _PBPAR_DD16_LENGTH             0x00000001

#define _PBPAR_DD15_POSITION           0x0000000F
#define _PBPAR_DD15_MASK               0x00000001
#define _PBPAR_DD15_LENGTH             0x00000001

#define _PBPAR_DD14_POSITION           0x0000000E
#define _PBPAR_DD14_MASK               0x00000001
#define _PBPAR_DD14_LENGTH             0x00000001

#define _PBPAR_DD13_POSITION           0x0000000D
#define _PBPAR_DD13_MASK               0x00000001
#define _PBPAR_DD13_LENGTH             0x00000001

#define _PBPAR_DD12_POSITION           0x0000000C
#define _PBPAR_DD12_MASK               0x00000001
#define _PBPAR_DD12_LENGTH             0x00000001

#define _PBPAR_DD11_POSITION           0x0000000B
#define _PBPAR_DD11_MASK               0x00000001
#define _PBPAR_DD11_LENGTH             0x00000001

#define _PBPAR_DD10_POSITION           0x0000000A
#define _PBPAR_DD10_MASK               0x00000001
#define _PBPAR_DD10_LENGTH             0x00000001

#define _PBPAR_DD9_POSITION            0x00000009
#define _PBPAR_DD9_MASK                0x00000001
#define _PBPAR_DD9_LENGTH              0x00000001

#define _PBPAR_DD8_POSITION            0x00000008
#define _PBPAR_DD8_MASK                0x00000001
#define _PBPAR_DD8_LENGTH              0x00000001

#define _PBPAR_DD7_POSITION            0x00000007
#define _PBPAR_DD7_MASK                0x00000001
#define _PBPAR_DD7_LENGTH              0x00000001

#define _PBPAR_DD6_POSITION            0x00000006
#define _PBPAR_DD6_MASK                0x00000001
#define _PBPAR_DD6_LENGTH              0x00000001

#define _PBPAR_DD5_POSITION            0x00000005
#define _PBPAR_DD5_MASK                0x00000001
#define _PBPAR_DD5_LENGTH              0x00000001

#define _PBPAR_DD4_POSITION            0x00000004
#define _PBPAR_DD4_MASK                0x00000001
#define _PBPAR_DD4_LENGTH              0x00000001

#define _PBPAR_DD3_POSITION            0x00000003
#define _PBPAR_DD3_MASK                0x00000001
#define _PBPAR_DD3_LENGTH              0x00000001

#define _PBPAR_DD2_POSITION            0x00000002
#define _PBPAR_DD2_MASK                0x00000001
#define _PBPAR_DD2_LENGTH              0x00000001

#define _PBPAR_DD1_POSITION            0x00000001
#define _PBPAR_DD1_MASK                0x00000001
#define _PBPAR_DD1_LENGTH              0x00000001

#define _PBPAR_DD0_POSITION            0x00000000
#define _PBPAR_DD0_MASK                0x00000001
#define _PBPAR_DD0_LENGTH              0x00000001

#define _PBODR_OD15_POSITION           0x0000000F
#define _PBODR_OD15_MASK               0x00000001
#define _PBODR_OD15_LENGTH             0x00000001

#define _PBODR_OD14_POSITION           0x0000000E
#define _PBODR_OD14_MASK               0x00000001
#define _PBODR_OD14_LENGTH             0x00000001

#define _PBODR_OD13_POSITION           0x0000000D
#define _PBODR_OD13_MASK               0x00000001
#define _PBODR_OD13_LENGTH             0x00000001

#define _PBODR_OD12_POSITION           0x0000000C
#define _PBODR_OD12_MASK               0x00000001
#define _PBODR_OD12_LENGTH             0x00000001

#define _PBODR_OD11_POSITION           0x0000000B
#define _PBODR_OD11_MASK               0x00000001
#define _PBODR_OD11_LENGTH             0x00000001

#define _PBODR_OD10_POSITION           0x0000000A
#define _PBODR_OD10_MASK               0x00000001
#define _PBODR_OD10_LENGTH             0x00000001

#define _PBODR_OD9_POSITION            0x00000009
#define _PBODR_OD9_MASK                0x00000001
#define _PBODR_OD9_LENGTH              0x00000001

#define _PBODR_OD8_POSITION            0x00000008
#define _PBODR_OD8_MASK                0x00000001
#define _PBODR_OD8_LENGTH              0x00000001

#define _PBODR_OD7_POSITION            0x00000007
#define _PBODR_OD7_MASK                0x00000001
#define _PBODR_OD7_LENGTH              0x00000001

#define _PBODR_OD6_POSITION            0x00000006
#define _PBODR_OD6_MASK                0x00000001
#define _PBODR_OD6_LENGTH              0x00000001

#define _PBODR_OD5_POSITION            0x00000005
#define _PBODR_OD5_MASK                0x00000001
#define _PBODR_OD5_LENGTH              0x00000001

#define _PBODR_OD4_POSITION            0x00000004
#define _PBODR_OD4_MASK                0x00000001
#define _PBODR_OD4_LENGTH              0x00000001

#define _PBODR_OD3_POSITION            0x00000003
#define _PBODR_OD3_MASK                0x00000001
#define _PBODR_OD3_LENGTH              0x00000001

#define _PBODR_OD2_POSITION            0x00000002
#define _PBODR_OD2_MASK                0x00000001
#define _PBODR_OD2_LENGTH              0x00000001

#define _PBODR_OD1_POSITION            0x00000001
#define _PBODR_OD1_MASK                0x00000001
#define _PBODR_OD1_LENGTH              0x00000001

#define _PBODR_OD0_POSITION            0x00000000
#define _PBODR_OD0_MASK                0x00000001
#define _PBODR_OD0_LENGTH              0x00000001

#define _PBDAT_D17_POSITION            0x00000011
#define _PBDAT_D17_MASK                0x00000001
#define _PBDAT_D17_LENGTH              0x00000001

#define _PBDAT_D16_POSITION            0x00000010
#define _PBDAT_D16_MASK                0x00000001
#define _PBDAT_D16_LENGTH              0x00000001

#define _PBDAT_D15_POSITION            0x0000000F
#define _PBDAT_D15_MASK                0x00000001
#define _PBDAT_D15_LENGTH              0x00000001

#define _PBDAT_D14_POSITION            0x0000000E
#define _PBDAT_D14_MASK                0x00000001
#define _PBDAT_D14_LENGTH              0x00000001

#define _PBDAT_D13_POSITION            0x0000000D
#define _PBDAT_D13_MASK                0x00000001
#define _PBDAT_D13_LENGTH              0x00000001

#define _PBDAT_D12_POSITION            0x0000000C
#define _PBDAT_D12_MASK                0x00000001
#define _PBDAT_D12_LENGTH              0x00000001

#define _PBDAT_D11_POSITION            0x0000000B
#define _PBDAT_D11_MASK                0x00000001
#define _PBDAT_D11_LENGTH              0x00000001

#define _PBDAT_D10_POSITION            0x0000000A
#define _PBDAT_D10_MASK                0x00000001
#define _PBDAT_D10_LENGTH              0x00000001

#define _PBDAT_D9_POSITION             0x00000009
#define _PBDAT_D9_MASK                 0x00000001
#define _PBDAT_D9_LENGTH               0x00000001

#define _PBDAT_D8_POSITION             0x00000008
#define _PBDAT_D8_MASK                 0x00000001
#define _PBDAT_D8_LENGTH               0x00000001

#define _PBDAT_D7_POSITION             0x00000007
#define _PBDAT_D7_MASK                 0x00000001
#define _PBDAT_D7_LENGTH               0x00000001

#define _PBDAT_D6_POSITION             0x00000006
#define _PBDAT_D6_MASK                 0x00000001
#define _PBDAT_D6_LENGTH               0x00000001

#define _PBDAT_D5_POSITION             0x00000005
#define _PBDAT_D5_MASK                 0x00000001
#define _PBDAT_D5_LENGTH               0x00000001

#define _PBDAT_D4_POSITION             0x00000004
#define _PBDAT_D4_MASK                 0x00000001
#define _PBDAT_D4_LENGTH               0x00000001

#define _PBDAT_D3_POSITION             0x00000003
#define _PBDAT_D3_MASK                 0x00000001
#define _PBDAT_D3_LENGTH               0x00000001

#define _PBDAT_D2_POSITION             0x00000002
#define _PBDAT_D2_MASK                 0x00000001
#define _PBDAT_D2_LENGTH               0x00000001

#define _PBDAT_D1_POSITION             0x00000001
#define _PBDAT_D1_MASK                 0x00000001
#define _PBDAT_D1_LENGTH               0x00000001

#define _PBDAT_D0_POSITION             0x00000000
#define _PBDAT_D0_MASK                 0x00000001
#define _PBDAT_D0_LENGTH               0x00000001

#define _SIMODE_SMC2_POSITION          0x0000001F
#define _SIMODE_SMC2_MASK              0x00000001
#define _SIMODE_SMC2_LENGTH            0x00000001

#define _SIMODE_SMC2CS2_POSITION       0x0000001E
#define _SIMODE_SMC2CS2_MASK           0x00000001
#define _SIMODE_SMC2CS2_LENGTH         0x00000001

#define _SIMODE_SMC2CS1_POSITION       0x0000001D
#define _SIMODE_SMC2CS1_MASK           0x00000001
#define _SIMODE_SMC2CS1_LENGTH         0x00000001

#define _SIMODE_SMC2CS0_POSITION       0x0000001C
#define _SIMODE_SMC2CS0_MASK           0x00000001
#define _SIMODE_SMC2CS0_LENGTH         0x00000001

#define _SIMODE_SMC2CS_POSITION        0x0000001C
#define _SIMODE_SMC2CS_MASK            0x00000007
#define _SIMODE_SMC2CS_LENGTH          0x00000003

#define _SIMODE_SDMB1_POSITION         0x0000001B
#define _SIMODE_SDMB1_MASK             0x00000001
#define _SIMODE_SDMB1_LENGTH           0x00000001

#define _SIMODE_SDMB0_POSITION         0x0000001A
#define _SIMODE_SDMB0_MASK             0x00000001
#define _SIMODE_SDMB0_LENGTH           0x00000001

#define _SIMODE_SDMB_POSITION          0x0000001A
#define _SIMODE_SDMB_MASK              0x00000003
#define _SIMODE_SDMB_LENGTH            0x00000002

#define _SIMODE_RFSDB1_POSITION        0x00000019
#define _SIMODE_RFSDB1_MASK            0x00000001
#define _SIMODE_RFSDB1_LENGTH          0x00000001

#define _SIMODE_RFSDB0_POSITION        0x00000018
#define _SIMODE_RFSDB0_MASK            0x00000001
#define _SIMODE_RFSDB0_LENGTH          0x00000001

#define _SIMODE_RFSDB_POSITION         0x00000018
#define _SIMODE_RFSDB_MASK             0x00000003
#define _SIMODE_RFSDB_LENGTH           0x00000002

#define _SIMODE_DSCB_POSITION          0x00000017
#define _SIMODE_DSCB_MASK              0x00000001
#define _SIMODE_DSCB_LENGTH            0x00000001

#define _SIMODE_CRTB_POSITION          0x00000016
#define _SIMODE_CRTB_MASK              0x00000001
#define _SIMODE_CRTB_LENGTH            0x00000001

#define _SIMODE_STZB_POSITION          0x00000015
#define _SIMODE_STZB_MASK              0x00000001
#define _SIMODE_STZB_LENGTH            0x00000001

#define _SIMODE_CEB_POSITION           0x00000014
#define _SIMODE_CEB_MASK               0x00000001
#define _SIMODE_CEB_LENGTH             0x00000001

#define _SIMODE_FEB_POSITION           0x00000013
#define _SIMODE_FEB_MASK               0x00000001
#define _SIMODE_FEB_LENGTH             0x00000001

#define _SIMODE_GMB_POSITION           0x00000012
#define _SIMODE_GMB_MASK               0x00000001
#define _SIMODE_GMB_LENGTH             0x00000001

#define _SIMODE_TFSDB1_POSITION        0x00000011
#define _SIMODE_TFSDB1_MASK            0x00000001
#define _SIMODE_TFSDB1_LENGTH          0x00000001

#define _SIMODE_TFSDB0_POSITION        0x00000010
#define _SIMODE_TFSDB0_MASK            0x00000001
#define _SIMODE_TFSDB0_LENGTH          0x00000001

#define _SIMODE_TFSDB_POSITION         0x00000010
#define _SIMODE_TFSDB_MASK             0x00000003
#define _SIMODE_TFSDB_LENGTH           0x00000002

#define _SIMODE_SMC1_POSITION          0x0000000F
#define _SIMODE_SMC1_MASK              0x00000001
#define _SIMODE_SMC1_LENGTH            0x00000001

#define _SIMODE_SMC1CS2_POSITION       0x0000000E
#define _SIMODE_SMC1CS2_MASK           0x00000001
#define _SIMODE_SMC1CS2_LENGTH         0x00000001

#define _SIMODE_SMC1CS1_POSITION       0x0000000D
#define _SIMODE_SMC1CS1_MASK           0x00000001
#define _SIMODE_SMC1CS1_LENGTH         0x00000001

#define _SIMODE_SMC1CS0_POSITION       0x0000000C
#define _SIMODE_SMC1CS0_MASK           0x00000001
#define _SIMODE_SMC1CS0_LENGTH         0x00000001

#define _SIMODE_SMC1CS_POSITION        0x0000000C
#define _SIMODE_SMC1CS_MASK            0x00000007
#define _SIMODE_SMC1CS_LENGTH          0x00000003

#define _SIMODE_SDMA1_POSITION         0x0000000B
#define _SIMODE_SDMA1_MASK             0x00000001
#define _SIMODE_SDMA1_LENGTH           0x00000001

#define _SIMODE_SDMA0_POSITION         0x0000000A
#define _SIMODE_SDMA0_MASK             0x00000001
#define _SIMODE_SDMA0_LENGTH           0x00000001

#define _SIMODE_SDMA_POSITION          0x0000000A
#define _SIMODE_SDMA_MASK              0x00000003
#define _SIMODE_SDMA_LENGTH            0x00000002

#define _SIMODE_RFSDA1_POSITION        0x00000009
#define _SIMODE_RFSDA1_MASK            0x00000001
#define _SIMODE_RFSDA1_LENGTH          0x00000001

#define _SIMODE_RFSDA0_POSITION        0x00000008
#define _SIMODE_RFSDA0_MASK            0x00000001
#define _SIMODE_RFSDA0_LENGTH          0x00000001

#define _SIMODE_RFSDA_POSITION         0x00000008
#define _SIMODE_RFSDA_MASK             0x00000003
#define _SIMODE_RFSDA_LENGTH           0x00000002

#define _SIMODE_DSCA_POSITION          0x00000007
#define _SIMODE_DSCA_MASK              0x00000001
#define _SIMODE_DSCA_LENGTH            0x00000001

#define _SIMODE_CRTA_POSITION          0x00000006
#define _SIMODE_CRTA_MASK              0x00000001
#define _SIMODE_CRTA_LENGTH            0x00000001

#define _SIMODE_STZA_POSITION          0x00000005
#define _SIMODE_STZA_MASK              0x00000001
#define _SIMODE_STZA_LENGTH            0x00000001

#define _SIMODE_CEA_POSITION           0x00000004
#define _SIMODE_CEA_MASK               0x00000001
#define _SIMODE_CEA_LENGTH             0x00000001

#define _SIMODE_FEA_POSITION           0x00000003
#define _SIMODE_FEA_MASK               0x00000001
#define _SIMODE_FEA_LENGTH             0x00000001

#define _SIMODE_GMA_POSITION           0x00000002
#define _SIMODE_GMA_MASK               0x00000001
#define _SIMODE_GMA_LENGTH             0x00000001

#define _SIMODE_TFSDA1_POSITION        0x00000001
#define _SIMODE_TFSDA1_MASK            0x00000001
#define _SIMODE_TFSDA1_LENGTH          0x00000001

#define _SIMODE_TFSDA0_POSITION        0x00000000
#define _SIMODE_TFSDA0_MASK            0x00000001
#define _SIMODE_TFSDA0_LENGTH          0x00000001

#define _SIMODE_TFSDA_POSITION         0x00000000
#define _SIMODE_TFSDA_MASK             0x00000003
#define _SIMODE_TFSDA_LENGTH           0x00000002

#define _SIGMR_ENB_POSITION            0x00000003
#define _SIGMR_ENB_MASK                0x00000001
#define _SIGMR_ENB_LENGTH              0x00000001

#define _SIGMR_ENA_POSITION            0x00000002
#define _SIGMR_ENA_MASK                0x00000001
#define _SIGMR_ENA_LENGTH              0x00000001

#define _SIGMR_RDM1_POSITION           0x00000001
#define _SIGMR_RDM1_MASK               0x00000001
#define _SIGMR_RDM1_LENGTH             0x00000001

#define _SIGMR_RDM0_POSITION           0x00000000
#define _SIGMR_RDM0_MASK               0x00000001
#define _SIGMR_RDM0_LENGTH             0x00000001

#define _SIGMR_RDM_POSITION            0x00000000
#define _SIGMR_RDM_MASK                0x00000003
#define _SIGMR_RDM_LENGTH              0x00000002

#define _SISTR_CRORA_POSITION          0x00000007
#define _SISTR_CRORA_MASK              0x00000001
#define _SISTR_CRORA_LENGTH            0x00000001

#define _SISTR_CROTA_POSITION          0x00000006
#define _SISTR_CROTA_MASK              0x00000001
#define _SISTR_CROTA_LENGTH            0x00000001

#define _SISTR_CRORB_POSITION          0x00000005
#define _SISTR_CRORB_MASK              0x00000001
#define _SISTR_CRORB_LENGTH            0x00000001

#define _SISTR_CROTB_POSITION          0x00000004
#define _SISTR_CROTB_MASK              0x00000001
#define _SISTR_CROTB_LENGTH            0x00000001

#define _SICMR_CSRRA_POSITION          0x00000007
#define _SICMR_CSRRA_MASK              0x00000001
#define _SICMR_CSRRA_LENGTH            0x00000001

#define _SICMR_CSRTA_POSITION          0x00000006
#define _SICMR_CSRTA_MASK              0x00000001
#define _SICMR_CSRTA_LENGTH            0x00000001

#define _SICMR_CSRRB_POSITION          0x00000005
#define _SICMR_CSRRB_MASK              0x00000001
#define _SICMR_CSRRB_LENGTH            0x00000001

#define _SICMR_CSRTB_POSITION          0x00000004
#define _SICMR_CSRTB_MASK              0x00000001
#define _SICMR_CSRTB_LENGTH            0x00000001

#define _SICR_GR4_POSITION             0x0000001F
#define _SICR_GR4_MASK                 0x00000001
#define _SICR_GR4_LENGTH               0x00000001

#define _SICR_SC4_POSITION             0x0000001E
#define _SICR_SC4_MASK                 0x00000001
#define _SICR_SC4_LENGTH               0x00000001

#define _SICR_R4CS2_POSITION           0x0000001D
#define _SICR_R4CS2_MASK               0x00000001
#define _SICR_R4CS2_LENGTH             0x00000001

#define _SICR_R4CS1_POSITION           0x0000001C
#define _SICR_R4CS1_MASK               0x00000001
#define _SICR_R4CS1_LENGTH             0x00000001

#define _SICR_R4CS0_POSITION           0x0000001B
#define _SICR_R4CS0_MASK               0x00000001
#define _SICR_R4CS0_LENGTH             0x00000001

#define _SICR_R4CS_POSITION            0x0000001B
#define _SICR_R4CS_MASK                0x00000007
#define _SICR_R4CS_LENGTH              0x00000003

#define _SICR_T4CS2_POSITION           0x0000001A
#define _SICR_T4CS2_MASK               0x00000001
#define _SICR_T4CS2_LENGTH             0x00000001

#define _SICR_T4CS1_POSITION           0x00000019
#define _SICR_T4CS1_MASK               0x00000001
#define _SICR_T4CS1_LENGTH             0x00000001

#define _SICR_T4CS0_POSITION           0x00000018
#define _SICR_T4CS0_MASK               0x00000001
#define _SICR_T4CS0_LENGTH             0x00000001

#define _SICR_T4CS_POSITION            0x00000018
#define _SICR_T4CS_MASK                0x00000007
#define _SICR_T4CS_LENGTH              0x00000003

#define _SICR_GR3_POSITION             0x00000017
#define _SICR_GR3_MASK                 0x00000001
#define _SICR_GR3_LENGTH               0x00000001

#define _SICR_SC3_POSITION             0x00000016
#define _SICR_SC3_MASK                 0x00000001
#define _SICR_SC3_LENGTH               0x00000001

#define _SICR_R3CS2_POSITION           0x00000015
#define _SICR_R3CS2_MASK               0x00000001
#define _SICR_R3CS2_LENGTH             0x00000001

#define _SICR_R3CS1_POSITION           0x00000014
#define _SICR_R3CS1_MASK               0x00000001
#define _SICR_R3CS1_LENGTH             0x00000001

#define _SICR_R3CS0_POSITION           0x00000013
#define _SICR_R3CS0_MASK               0x00000001
#define _SICR_R3CS0_LENGTH             0x00000001

#define _SICR_R3CS_POSITION            0x00000013
#define _SICR_R3CS_MASK                0x00000007
#define _SICR_R3CS_LENGTH              0x00000003

#define _SICR_T3CS2_POSITION           0x00000012
#define _SICR_T3CS2_MASK               0x00000001
#define _SICR_T3CS2_LENGTH             0x00000001

#define _SICR_T3CS1_POSITION           0x00000011
#define _SICR_T3CS1_MASK               0x00000001
#define _SICR_T3CS1_LENGTH             0x00000001

#define _SICR_T3CS0_POSITION           0x00000010
#define _SICR_T3CS0_MASK               0x00000001
#define _SICR_T3CS0_LENGTH             0x00000001

#define _SICR_T3CS_POSITION            0x00000010
#define _SICR_T3CS_MASK                0x00000007
#define _SICR_T3CS_LENGTH              0x00000003

#define _SICR_GR2_POSITION             0x0000000F
#define _SICR_GR2_MASK                 0x00000001
#define _SICR_GR2_LENGTH               0x00000001

#define _SICR_SC2_POSITION             0x0000000E
#define _SICR_SC2_MASK                 0x00000001
#define _SICR_SC2_LENGTH               0x00000001

#define _SICR_R2CS2_POSITION           0x0000000D
#define _SICR_R2CS2_MASK               0x00000001
#define _SICR_R2CS2_LENGTH             0x00000001

#define _SICR_R2CS1_POSITION           0x0000000C
#define _SICR_R2CS1_MASK               0x00000001
#define _SICR_R2CS1_LENGTH             0x00000001

#define _SICR_R2CS0_POSITION           0x0000000B
#define _SICR_R2CS0_MASK               0x00000001
#define _SICR_R2CS0_LENGTH             0x00000001

#define _SICR_R2CS_POSITION            0x0000000B
#define _SICR_R2CS_MASK                0x00000007
#define _SICR_R2CS_LENGTH              0x00000003

#define _SICR_T2CS2_POSITION           0x0000000A
#define _SICR_T2CS2_MASK               0x00000001
#define _SICR_T2CS2_LENGTH             0x00000001

#define _SICR_T2CS1_POSITION           0x00000009
#define _SICR_T2CS1_MASK               0x00000001
#define _SICR_T2CS1_LENGTH             0x00000001

#define _SICR_T2CS0_POSITION           0x00000008
#define _SICR_T2CS0_MASK               0x00000001
#define _SICR_T2CS0_LENGTH             0x00000001

#define _SICR_T2CS_POSITION            0x00000008
#define _SICR_T2CS_MASK                0x00000007
#define _SICR_T2CS_LENGTH              0x00000003

#define _SICR_GR1_POSITION             0x00000007
#define _SICR_GR1_MASK                 0x00000001
#define _SICR_GR1_LENGTH               0x00000001

#define _SICR_SC1_POSITION             0x00000006
#define _SICR_SC1_MASK                 0x00000001
#define _SICR_SC1_LENGTH               0x00000001

#define _SICR_R1CS2_POSITION           0x00000005
#define _SICR_R1CS2_MASK               0x00000001
#define _SICR_R1CS2_LENGTH             0x00000001

#define _SICR_R1CS1_POSITION           0x00000004
#define _SICR_R1CS1_MASK               0x00000001
#define _SICR_R1CS1_LENGTH             0x00000001

#define _SICR_R1CS0_POSITION           0x00000003
#define _SICR_R1CS0_MASK               0x00000001
#define _SICR_R1CS0_LENGTH             0x00000001

#define _SICR_R1CS_POSITION            0x00000003
#define _SICR_R1CS_MASK                0x00000007
#define _SICR_R1CS_LENGTH              0x00000003

#define _SICR_T1CS2_POSITION           0x00000002
#define _SICR_T1CS2_MASK               0x00000001
#define _SICR_T1CS2_LENGTH             0x00000001

#define _SICR_T1CS1_POSITION           0x00000001
#define _SICR_T1CS1_MASK               0x00000001
#define _SICR_T1CS1_LENGTH             0x00000001

#define _SICR_T1CS0_POSITION           0x00000000
#define _SICR_T1CS0_MASK               0x00000001
#define _SICR_T1CS0_LENGTH             0x00000001

#define _SICR_T1CS_POSITION            0x00000000
#define _SICR_T1CS_MASK                0x00000007
#define _SICR_T1CS_LENGTH              0x00000003

#endif /* C1600R_H */
