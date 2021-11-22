/*
 * Modify the ROM and RAM base and sz (size) variables below to
 * suit your systems memory layout.
 *
 *   base indicates at what address a memory begins
 *   sz indicates the size of that memory
 *
 * Values can be specified in decimal, hexadecimal, or as units such
 * as 1K or 1M.
 *
 * Space for the stack may also be reserved here. The heap will then
 * consume all remaining RAM between the end of the .bss section and
 * the lowest address reserved for the stack.
 *
 * Since there are no controls in place to ensure the stack does not
 * grow into the heap, the user is responsible for reserving sufficient
 * stack space to prevent it overwriting the upper areas of the heap.
 */
__rom_base = 0x04000000;
__rom_sz = 1M;
__ram_base = 0x027FE000;
__ram_sz = 8K;

__stack_sz = 4K;

/*
 * Dont modify below this line (unless you know what youre doing),
 * except to add user interrupt vectors.
 */

STARTUP(crt0.o)
OUTPUT_ARCH(m68k)

__rom_end = (__rom_base + __rom_sz);
__ram_end = (__ram_base + __ram_sz);

__evt_org = __rom_base;
__text_org = __rom_base + 0x400;
__text_sz = __rom_sz - 0x400;
__data_org = __ram_base;
__data_sz = __ram_sz;

/* Make sure stack size is a multiple of 16, and at least the amount the user
 * thought they were getting. */
__stack_sz += 15;
__stack_sz &= ~0xF;

MEMORY {
    evt          (r!ax) : ORIGIN = __evt_org, LENGTH = 0x400
    text         (rx!w) : ORIGIN = __text_org, LENGTH = __text_sz
    data        (rwx!a) : ORIGIN = __data_org, LENGTH = __data_sz
}

SECTIONS {
    .evt : {
        /* Reset vector */
        LONG(__ram_end);                /* Initial SSP */
        LONG(ABSOLUTE(_start));         /* Initial PC */

        /* Exception vector table */
        LONG(DEFINED(BusError) ? ABSOLUTE(BusError) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(AddressError) ? ABSOLUTE(AddressError) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(IllegalInstruction) ? ABSOLUTE(IllegalInstruction) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(ZeroDivide) ? ABSOLUTE(ZeroDivide) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(CHKInstruction) ? ABSOLUTE(CHKInstruction) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAPVInstruction) ? ABSOLUTE(TRAPVInstruction) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PrivilegeViolation) ? ABSOLUTE(PrivilegeViolation) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(Trace) ? ABSOLUTE(Trace) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(Line1010Emulator) ? ABSOLUTE(Line1010Emulator) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(Line1111Emulator) ? ABSOLUTE(Line1111Emulator) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(HardwareBreakpoint) ? ABSOLUTE(HardwareBreakpoint) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(CoprocessorProtocolViolation) ? ABSOLUTE(CoprocessorProtocolViolation) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(FormatError) ? ABSOLUTE(FormatError) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(UninitializedInterruptVector) ? ABSOLUTE(UninitializedInterruptVector) : ABSOLUTE(__DefaultInterrupt));
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
        LONG(DEFINED(SpuriousInterrupt) ? ABSOLUTE(SpuriousInterrupt) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(IRQ1) ? ABSOLUTE(IRQ1) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(IRQ2) ? ABSOLUTE(IRQ2) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(IRQ3) ? ABSOLUTE(IRQ3) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(IRQ4) ? ABSOLUTE(IRQ4) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(IRQ5) ? ABSOLUTE(IRQ5) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(IRQ6) ? ABSOLUTE(IRQ6) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(IRQ7) ? ABSOLUTE(IRQ7) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP0) ? ABSOLUTE(TRAP0) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP1) ? ABSOLUTE(TRAP1) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP2) ? ABSOLUTE(TRAP2) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP3) ? ABSOLUTE(TRAP3) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP4) ? ABSOLUTE(TRAP4) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP5) ? ABSOLUTE(TRAP5) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP6) ? ABSOLUTE(TRAP6) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP7) ? ABSOLUTE(TRAP7) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP8) ? ABSOLUTE(TRAP8) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP9) ? ABSOLUTE(TRAP9) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP10) ? ABSOLUTE(TRAP10) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP11) ? ABSOLUTE(TRAP11) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP12) ? ABSOLUTE(TRAP12) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP13) ? ABSOLUTE(TRAP13) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP14) ? ABSOLUTE(TRAP14) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(TRAP15) ? ABSOLUTE(TRAP15) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(FPBranchOrSetUnorderedCondition) ? ABSOLUTE(FPBranchOrSetUnorderedCondition) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(FPInexactResult) ? ABSOLUTE(FPInexactResult) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(FPZeroDivide) ? ABSOLUTE(FPZeroDivide) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(FPUnderflow) ? ABSOLUTE(FPUnderflow) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(FPOperandError) ? ABSOLUTE(FPOperandError) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(FPOverflow) ? ABSOLUTE(FPOverflow) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(FPSignallingNAN) ? ABSOLUTE(FPSignallingNAN) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(FPUnimplementedDataType) ? ABSOLUTE(FPUnimplementedDataType) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(MMUConfigurationError) ? ABSOLUTE(MMUConfigurationError) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(MMUIllegalOperation) ? ABSOLUTE(MMUIllegalOperation) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(MMUAccessLevelViolation) ? ABSOLUTE(MMUAccessLevelViolation) : ABSOLUTE(__DefaultInterrupt));
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
        LONG(0); /* Unassigned, reserved */
/*
 *
 * User Interrupt Vectors
 *
 *   Vector #         Address
 *   Hex    Dec       Hex      Dec
 *   40-FF  64-255    100-3FC  256-1020
 *
 * To calculate the offset within the .evt section to place your vector, use
 * the following calculation (assuming vector number = 0x50):
 *
 *   0x50 * 4 = 0x140
 *
 * You could then place your vector at that position in the vector table as
 * follows:
 *
 *   . = 0x140;
 *   LONG(ABSOLUTE(NameOfHandlerFunction));
 */
        /* 0x40: Interrupt vector for the PIT, used for FreeRTOS ticks */
        LONG(ABSOLUTE(PITInterruptHandler));
        
        /* 0xE0-FF: Communication Processor Module (CPM) */
        . = 0x380;
        LONG(DEFINED(CPMErrorHandler) ? ABSOLUTE(CPMErrorHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PC11InterruptHandler) ? ABSOLUTE(PC11InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PC10InterruptHandler) ? ABSOLUTE(PC10InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(SMC2PIPInterruptHandler) ? ABSOLUTE(SMC2PIPInterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(SMC1InterruptHandler) ? ABSOLUTE(SMC1InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(SPIInterruptHandler) ? ABSOLUTE(SPIInterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PC9InterruptHandler) ? ABSOLUTE(PC9InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(Timer4InterruptHandler) ? ABSOLUTE(Timer4InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(0); /* Unassigned, reserved */
        LONG(DEFINED(PC8InterruptHandler) ? ABSOLUTE(PC8InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PC7InterruptHandler) ? ABSOLUTE(PC7InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PC6InterruptHandler) ? ABSOLUTE(PC6InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(Timer3InterruptHandler) ? ABSOLUTE(Timer3InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(0); /* Unassigned, reserved */
        LONG(DEFINED(PC5InterruptHandler) ? ABSOLUTE(PC5InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PC4InterruptHandler) ? ABSOLUTE(PC4InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(0); /* Unassigned, reserved */
        LONG(DEFINED(RISCTimerTableInterruptHandler) ? ABSOLUTE(RISCTimerTableInterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(Timer2InterruptHandler) ? ABSOLUTE(Timer2InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(0); /* Unassigned, reserved */
        LONG(DEFINED(IDMA2InterruptHandler) ? ABSOLUTE(IDMA2InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(IDMA1InterruptHandler) ? ABSOLUTE(IDMA1InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(SDMAChannelBusErrorHandler) ? ABSOLUTE(SDMAChannelBusErrorHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PC3InterruptHandler) ? ABSOLUTE(PC3InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PC2InterruptHandler) ? ABSOLUTE(PC2InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(Timer1InterruptHandler) ? ABSOLUTE(Timer1InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PC1InterruptHandler) ? ABSOLUTE(PC1InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(SCC4InterruptHandler) ? ABSOLUTE(SCC4InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(SCC3InterruptHandler) ? ABSOLUTE(SCC3InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(SCC2InterruptHandler) ? ABSOLUTE(SCC2InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(SCC1InterruptHandler) ? ABSOLUTE(SCC1InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
        LONG(DEFINED(PC0InterruptHandler) ? ABSOLUTE(PC0InterruptHandler) : ABSOLUTE(__DefaultInterrupt));
    } > evt

    .text : {
        _text_start = .;
        *(.text .text.*)
        . = ALIGN(0x10);
        _text_end = .;
    } > text

    .rodata : AT(_text_end) {
        _rodata_start = .;
        *(.rodata .rodata.*)
        . = ALIGN(0x10);
        _rodata_end = .;
    } > text

    .data : AT(_rodata_end) {
        _data_start = .;
        *(.data .data.*)
        . = ALIGN(0x10);
        _data_end = .;
    } > data

    .bss : {
        _bss_start = .;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(0x10);
        _bss_end = .;
    } > data

    .heap : {
        _heap_start = .;
        . += (__ram_sz - __stack_sz - SIZEOF(.bss) - SIZEOF(.data));
        _heap_end = .;
    } > data
}
