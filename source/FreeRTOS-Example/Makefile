# List all of the object files that will be combined into your final binary
# in the OBJ variable.
#
# For example, if you have the following source files
#
#   main.c
#   user.c
#   driver.s
#
# then your OBJ list would be
#
#   main.o user.o driver.o
#
# The compiler will automatically choose the correct source file (.c, .s etc)
# according to the object file (.o) to be created.

CPU=cpu32

PREFIX=m68k-unknown-elf

OBJ=main.o string.o FreeRTOS-Kernel/tasks.o FreeRTOS-Kernel/list.o FreeRTOS-Kernel/queue.o FreeRTOS-Kernel/timers.o FreeRTOS-Kernel/portable/MemMang/heap_4.o FreeRTOS-Kernel/portable/GCC/m68k/port.o FreeRTOS-Kernel/portable/GCC/m68k/portasm.o

# Dont modify below this line (unless you know what youre doing).

CC=$(PREFIX)-gcc
AS=$(PREFIX)-as
LD=$(PREFIX)-ld
OBJCOPY=$(PREFIX)-objcopy
OBJDUMP=$(PREFIX)-objdump

CFLAGS=-m$(CPU) -Wall -g -static -I. -I./include/ -I./FreeRTOS-Kernel/include/ -I./FreeRTOS-Kernel/portable/GCC/m68k/ -msoft-float -MMD -MP -O1
LFLAGS=--script=platform.ld
AFLAGS=-m$(CPU) -Wall -c -g

SRC=$(wildcard *.c)
DEP=$(SRC:%.c=%.d)

%/%.o: %.c
	$(CC) $(CFLAGS) -m$(CPU) -c -o $@ $<

%/%.o: %.s
	$(CC) $(CFLAGS) -m$(CPU) -c $<

%/%.o: %.S
	$(CC) $(CFLAGS) -m$(CPU) -c $<

bmbinary: $(OBJ)
	$(LD) -o $@ $(OBJ) $(LFLAGS)

-include $(DEP)

crt: crt0.o

clean:
	rm -f bmbinary bmbinary.rom bmbinary.srec $(OBJ) $(DEP)

rom:
	$(OBJCOPY) -O binary bmbinary bmbinary.rom
	$(OBJCOPY) -O srec bmbinary bmbinary.srec
	python3 roms.py

dump:
	$(OBJDUMP) -belf32-m68k -st -j.reset -j.ivt bmbinary
	$(OBJDUMP) -belf32-m68k -dt -j.text bmbinary
	$(OBJDUMP) -belf32-m68k -st -j.rodata -j.data -j.bss bmbinary

dumps:
	$(OBJDUMP) -belf32-m68k -st -j.reset -j.ivt bmbinary
	$(OBJDUMP) -belf32-m68k -St -j.text bmbinary
	$(OBJDUMP) -belf32-m68k -st -j.rodata -j.data -j.bss -j.pbss bmbinary

hexdump:
	hexdump -C bmbinary.rom
