#ifndef C1600R_H
#define C1600R_H

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

/* The following registers are all internal to the QUICC */
#define DPRBASE MODULE_BASE
#define REGB (DPRBASE + 0x1000)
#define SPIBASE (DPRBASE + 0xD00)
#define TIMERBASE (DPRBASE + 0xDB0)
#define IDMA1BASE (DPRBASE + 0xE70)
#define SMC1BASE (DPRBASE + 0xE80)
#define IDMA2BASE (DPRBASE + 0xF70)
#define SMC2BASE (DPRBASE + 0xF80)

#ifndef __ASSEMBLER__
#include <stdint.h>
/* Don't modify below this line unless you know what you're doing */

/* The following registers are external to the QUICC */
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
        uint8_t :3;
    };
    struct {
        uint8_t u8;
    };
} __LEDCRbits_t;
#define LEDCRbits (*(volatile __LEDCRbits_t *)(PERIPHERAL_BASE + 0x80001))


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
#define PCTLbits (*(volatile __PCTLbits_t *)(PERIPHERAL_BASE + 0x80001))


/* This register is a work in progress */
#define SPCR (*(volatile uint8_t *)(PERIPHERAL_BASE + 0x30000))
typedef union {
    struct {
        uint8_t :4;
        uint8_t EN:1;
        uint8_t PWR:1;
        uint8_t :2;
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
        uint8_t RD:1;
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

/* Parameter RAM */
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

typedef union {
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
        uint16_t LEN;
        uint8_t *DST;
    };
} __SPIRxBufferDescriptor_t;

typedef union {
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
        uint16_t LEN;
        uint8_t *SRC;
    };
} __SPITxBufferDescriptor_t;

typedef union {
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
        uint32_t LEN;
        uint8_t *SRC;
        uint8_t *DST;
    };
} __IDMABufferDescriptor_t;

typedef union {
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
} __SMCRxBufferDescriptorFlags_t;

typedef union {
    struct {
        __SMCRxBufferDescriptorFlags_t flags;
        uint16_t LEN;
        uint8_t *DST;
    };
} __SMCRxBufferDescriptor_t;

typedef union {
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
} __SMCTxBufferDescriptorFlags_t;

typedef union {
    struct {
        __SMCTxBufferDescriptorFlags_t flags;
        uint16_t LEN;
        uint8_t *SRC;
    };
} __SMCTxBufferDescriptor_t;

#define SPIRBASE (*(volatile uint16_t *)(SPIBASE))
#define SPITBASE (*(volatile uint16_t *)(SPIBASE + 0x2))
#define SPIRFCR (*(volatile uint8_t *)(SPIBASE + 0x4))
#define SPIRFCRbits (*(volatile __RFCRbits_t *)(SPIBASE + 0x4))
#define SPITFCR (*(volatile uint8_t *)(SPIBASE + 0x5))
#define SPITFCRbits (*(volatile __TFCRbits_t *)(SPIBASE + 0x5))
#define SPIMRBLR (*(volatile uint16_t *)(SPIBASE + 0x6))


#define IDMA1IBASE (*(volatile uint16_t *)(IDMA1BASE))
#define IDMA1IBPTR (*(volatile uint16_t *)(IDMA1BASE + 0x2))


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


#define IDMA2IBASE (*(volatile uint16_t *)(IDMA2BASE))
#define IDMA2IBPTR (*(volatile uint16_t *)(IDMA2BASE + 0x2))


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


/* SIM Registers */
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


/* TODO Protocol specific structs */
#define SCCM1 (*(volatile uint16_t *)(REGB + 0x614))
#define SCCM2 (*(volatile uint16_t *)(REGB + 0x634))
#define SCCM3 (*(volatile uint16_t *)(REGB + 0x654))
#define SCCM4 (*(volatile uint16_t *)(REGB + 0x674))


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
#define PCTL (PERIPHERAL_BASE + 0x8000F)

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
#define OR0 (REGB + 0x54)
#define BR1 (REGB + 0x60)
#define OR1 (REGB + 0x64)
#define BR2 (REGB + 0x70)
#define OR2 (REGB + 0x74)
#define BR3 (REGB + 0x80)
#define OR3 (REGB + 0x84)
#define BR4 (REGB + 0x90)
#define OR4 (REGB + 0x94)
#define BR5 (REGB + 0xA0)
#define OR5 (REGB + 0xA4)
#define BR6 (REGB + 0xB0)
#define OR6 (REGB + 0xB4)
#define BR7 (REGB + 0xC0)
#define OR7 (REGB + 0xC4)
#define ICCR (REGB + 0x500)
#define CMR1 (REGB + 0x504)
#define SAPR1 (REGB + 0x508)
#define DAPR1 (REGB + 0x50C)
#define BCR1 (REGB + 0x510)
#define FCR1 (REGB + 0x514)
#define CMAR1 (REGB + 0x516)
#define CSR1 (REGB + 0x518)
#define SDSR (REGB + 0x51C)
#define SDCR (REGB + 0x51E)
#define SDAR (REGB + 0x520)
#define CMR2 (REGB + 0x526)
#define SAPR2 (REGB + 0x528)
#define DAPR2 (REGB + 0x52C)
#define BCR2 (REGB + 0x530)
#define FCR2 (REGB + 0x534)
#define CMAR2 (REGB + 0x536)
#define CSR2 (REGB + 0x538)
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
#define TRR1 (REGB + 0x594)
#define TRR2 (REGB + 0x596)
#define TCR1 (REGB + 0x598)
#define TCR2 (REGB + 0x59A)
#define TCN1 (REGB + 0x59C)
#define TCN2 (REGB + 0x59E)
#define TMR3 (REGB + 0x5A0)
#define TMR4 (REGB + 0x5A2)
#define TRR3 (REGB + 0x5A4)
#define TRR4 (REGB + 0x5A6)
#define TCR3 (REGB + 0x5A8)
#define TCR4 (REGB + 0x5AA)
#define TCN3 (REGB + 0x5AC)
#define TCN4 (REGB + 0x5AE)
#define TER1 (REGB + 0x5B0)
#define TER2 (REGB + 0x5B2)
#define TER3 (REGB + 0x5B4)
#define TER4 (REGB + 0x5B6)
#define CR (REGB + 0x5C0)
#define RCCR (REGB + 0x5C4)
#define RTER (REGB + 0x5D6)
#define RTMR (REGB + 0x5DA)
#define BRGC1 (REGB + 0x5F0)
#define BRGC2 (REGB + 0x5F4)
#define BRGC3 (REGB + 0x5F8)
#define BRGC4 (REGB + 0x5FC)
#define GSMR1L (REGB + 0x600)
#define GSMR1H (REGB + 0x604)
#define PSMR1 (REGB + 0x608)
#define TODR1 (REGB + 0x60C)
#define DSR1 (REGB + 0x60E)
#define SCCE1 (REGB + 0x610)
#define SCCM1 (REGB + 0x614)
#define SCCS1 (REGB + 0x617)
#define GSMR2L (REGB + 0x620)
#define GSMR2H (REGB + 0x624)
#define PSMR2 (REGB + 0x628)
#define TODR2 (REGB + 0x62C)
#define DSR2 (REGB + 0x62E)
#define SCCE2 (REGB + 0x630)
#define SCCM2 (REGB + 0x634)
#define SCCS2 (REGB + 0x637)
#define GSMR3L (REGB + 0x640)
#define GSMR3H (REGB + 0x644)
#define PSMR3 (REGB + 0x648)
#define TODR3 (REGB + 0x64C)
#define DSR3 (REGB + 0x64E)
#define SCCE3 (REGB + 0x650)
#define SCCM3 (REGB + 0x654)
#define SCCS3 (REGB + 0x657)
#define GSMR4L (REGB + 0x660)
#define GSMR4H (REGB + 0x664)
#define PSMR4 (REGB + 0x668)
#define TODR4 (REGB + 0x66C)
#define DSR4 (REGB + 0x66E)
#define SCCE4 (REGB + 0x670)
#define SCCM4 (REGB + 0x674)
#define SCCS4 (REGB + 0x677)
#define SMCMR1 (REGB + 0x682)
#define SMCE1 (REGB + 0x686)
#define SMCM1 (REGB + 68A)
#define SMCMR2 (REGB + 0x692)
#define SMCE2 (REGB + 0x696)
#define SMCM2 (REGB + 69A)
#define SPMODE (REGB + 0x6A0)
#define SPIE (REGB + 0x6A6)
#define SPIM (REGB + 0x6AA)
#define SPCOM (REGB + 0x6AD)
#define PIPC (REGB + 0x6B2)
#define PTPR (REGB + 0x6B6)
#define PBDIR (REGB + 0x6B8)
#define PBPAR (REGB + 0x6BC)
#define PBODR (REGB + 0x6C2)
#define PBDAT (REGB + 0x6C4)
#define SIMODE (REGB + 0x6E0)
#define SIGMR (REGB + 0x6E4)
#define SISTR (REGB + 0x6E6)
#define SICMR (REGB + 0x6E7)
#define SICR (REGB + 0x6EC)
#define SIRP (REGB + 0x6F2)

#endif /* __ASSEMBLER__ */

#endif /* C1600R_H */
