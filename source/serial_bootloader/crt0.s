    .title "crt0.s for MC68360 bare metal"

    .extern main
    .extern __rom_base

    .global _start
    .global __DefaultInterrupt

    .section .text
    .align 2
_start:
    /* Reset all external peripherals */
    reset

    /* Setup SR for supervisor state, and mask all interrupts */
    move.w  #0x2700, %sr

    /* Init SP to internal SRAM - DRAM not available yet */
    movea.l #0x0FF00400, %sp

    /* Configure VBR to start of ROM */
    lea     __rom_base, %a0
    movec   %a0, %vbr

    /* Source/Destination function code registers to supervisor space */
    moveq   #7, %d0
    movec   %d0, %sfc
    movec   %d0, %dfc

    /* Configure MBAR to point to address 0x0FF00000 - stack now useable */
    move.l  #0x0FF00001, %d0
    moves.l %d0, 0x3FF00
    moves.l 0x3FF00, %d0

    /* Zeroise internal dual-port RAM (user data and parameter RAM) */
    move.l  #0x3FF, %d0
    clr.l   %d1
    movea.l #0x0FF00000, %a0

0:
    move.l  %d1, %a0@+
    dbf     %d0, 0b

    /* Make sure Breakpoint Control Register is cleared */
    clr.l   0x0FF01034                  /* BKCR */

.call_main:
    jsr     main

    /* Undefined behaviour - return to _start */
    bra.w   _start

/*
 * __DefaultInterrupt handles all interrupt and exception vectors that have not
 * been overridden by the programmer.
 *
 * Unless handled more specifically, all exceptions and interrupts simply
 * return.
 */
    .weak __DefaultInterrupt

__DefaultInterrupt:
    rte

    .end
