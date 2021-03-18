
# FreeRTOS on Cisco 1600R Example

This directory contains a standalone FreeRTOS application which implements a handful of tasks that will each blink one of the available status LEDs available on a 1600R series router.

## Get started
### Toolchain
I've set this up to work with my m68k bare metal "toolchain of sorts", details of which can be found [here](https://github.com/tomstorey/m68k_bare_metal). Follow the instructions in that repo to configure an environment which can be used to compile code for the m68k architecture.

### FreeRTOS with m68k port
To use this example, you will need to clone my FreeRTOS kernel repository which contains a Motorola 68000 port into this directory by running:

`git clone https://github.com/tomstorey/FreeRTOS-Kernel.git`

Then, move the included `FreeRTOSConfig.h` into `FreeRTOS-Kernel/include`.

### Build the source
From here you should be able to run the following commands to build a ROM image:

```
make crt
make && make rom
```

This results in a file called `bmbinary.rom` which must be split as even (FW1) and odd (FW2) bytes between two physical ROMs. This can often be done in the software for your favourite programmer, or you can use the included `roms.py` script to do this for you (requires Python 3).

By default, `roms.py` is called via the `make rom` command, but you can remove this from the Makefile and call it manually if desired:

`python3 roms.py`

and it will split bmbinary.rom into two files called `fw1` and `fw2`, which are then programmed and installed into their respective ROMs and sockets.

### Run it
To run this code, you will need to either:

1. implement a hardware mod to the board itself to install a jumper that allows the WE/ pin of smaller ROMs to be disconnected from the address signal that is routed to that pin of the socket. This mod allows you to switch easily between the factory ROMs and your own ROMs, but is quite fiddly to implement. See the main README.md file for details of this mod.
2. physically modify the ROMs to tie the WE/ pin to the adjacent VCC pin, and cut the pin off to ensure that it doesnt make contact with the socket - although this does not lend itself to re-programming the ROMs. This could be done with a single set of ROMs that has my serial bootloader programmed into them, allowing code to be uploaded and executed from RAM instead of needing to continually reprogram ROMs.

## Support
I'll do my best to help you out if you run into difficulties, please raise an issue against this repo.
