import argparse
import os
import struct
import time
from serial import Serial

# Maximum baud via SMC1 (Console port) is 57600
# DEV = '/dev/tty.usbserial-ABSCDTXJ'
# BAUD = 57600

# Using SCC3 via the WIC slot Ive managed 230400
DEV = '/dev/tty.usbserial-FT94JP1H'
BAUD = 230400

RETRIES = 10

def convert_arg_to_long(arg: str) -> int:
    try:
        val = int(arg)
    except ValueError:
        try:
            val = int(arg, 16)
        except ValueError:
            raise ValueError(f'{arg} is not a valid integer')

    if not (0 <= val <= 0xFFFFFFFF):
        raise ValueError(f'Value {arg} is invalid. Min 0, max 0xFFFFFFFF.')

    return val


def convert_hex_to_bytes(data: str) -> bytes:
    offset = 0

    chars = []

    while True:
        if offset >= len(data):
            break
            
        if offset == 0 and (len(data) & 1) == 1:
            text = data[offset:(offset + 1)]
            offset += 1
        else:
            text = data[offset:(offset + 2)]
            offset += 2

        try:
            val = int(text, 16)
        except ValueError:
            raise ValueError(f'"{text}"" is not valid hex formatted data')

        chars.append(val)

    return bytes(chars)


def main():
    parser = argparse.ArgumentParser(
        description='Load application software or read/write memory via UART'
    )

    # Only one option from the following group should ever be specified, and
    # determines what action will be taken by the script
    act_group = parser.add_mutually_exclusive_group()
    act_group.add_argument(
        '-a', '--addr',
        dest='addr', type=str, default=None,
        help='The address from which memory reads or writes commence. Min 0, '
             'max 0xFFFFFFFF, can be byte aligned'
    )
    act_group.add_argument(
        '-b', '--base',
        dest='base', type=str, default=None,
        help='Base address where the binary file will be loaded in RAM. Min '
             '0, max 0xFFFFFFFE, must be word aligned'
    )

    exec_group = parser.add_mutually_exclusive_group()
    exec_group.add_argument(
        '-e', '--exec',
        dest='exec', type=str, default=None,
        help='Address to JSR to to execute loaded code. Min 0, max '
             '0xFFFFFFFE, must be word aligned.'
    )
    exec_group.add_argument(
        '-j', '--jump',
        dest='jump', type=str, default=None,
        help='Address to JMP to to execute loaded code. Min 0, max '
             '0xFFFFFFFE, must be word aligned.'
    )

    parser.add_argument(
        '-l', '--length',
        dest='length', type=str, default=None,
        help='How many bytes to read from memory during a read operation. Min '
             '0, max 0xFFFFFFFF.'
    )

    parser.add_argument(
        '-r', '--read',
        dest='rd_flag', action='store_true',
        help='Read data from memory starting from addr for length bytes'
    )
    parser.add_argument(
        '-w', '--write',
        dest='wr_flag', action='store_true',
        help='Write data to memory starting from addr'
    )

    parser.add_argument(
        '--word',
        dest='word_flag', action='store_true',
        help='Write a word to the address specified by addr'
    )
    parser.add_argument(
        '--long',
        dest='long_flag', action='store_true',
        help='Write a long to the address specified by addr'
    )

    parser.add_argument(
        'data',
        type=str, nargs='?',
        help='When specifying --base, this argument contains the filename of '
             'the binary to be loaded into memory. When specifying --addr and '
             '--write, this argument contains hex formatted data that is to '
             'be written to memory. If specifying --addr and --read, this '
             'argument contains the filename into which the read data will be '
             'stored. If specifying --word or --long, this argument contains '
             'the value to be written.'
    )

    args = parser.parse_args()

    addr = args.addr
    base = args.base
    exec = args.exec
    jump = args.jump
    length = args.length
    rd_flag = args.rd_flag
    wr_flag = args.wr_flag
    word_flag = args.word_flag
    long_flag = args.long_flag
    data = args.data

    if addr is not None:
        # Performing a memory read or write
        if rd_flag is False and wr_flag is False and word_flag is False and long_flag is False:
            raise ValueError(
                'When specifying --addr, you must also specify one of --read '
                ', --write, --word or --long'
            )

        if rd_flag is True and length is None:
            raise ValueError(
                'When specifying --read, you must also specify --length'
            )
        
        if wr_flag is True and data is None:
            raise ValueError(
                'When specifying --write, you must also specify the data to '
                'be written using the data argument. Data must be hex '
                'formatted.'
            )
        
        if wr_flag is True and (word_flag is True or long_flag is True):
            raise ValueError(
                '--write is implied when --word or --long is specified'
            )
        
        if word_flag is True and long_flag is True:
            raise ValueError(
                '--word and --long are mutually exclusive'
            )
        
        if (word_flag is True or long_flag is True) and data is None:
            raise ValueError(
                'When specifying --word or --long, you must also specify the '
                'data to be written using the data argument. Data must be hex '
                'formatted.'
            )
        
        if exec is True or jump is True:
            print('--exec and --jump are ignored when reading/writing memory')
        
        addr = convert_arg_to_long(addr)

        if rd_flag:
            length = convert_arg_to_long(length)

        if wr_flag:
            data_wr = convert_hex_to_bytes(data)

            if addr + len(data_wr) > 0x100000000:
                raise Exception(
                    f'{len(data_wr)} bytes from 0x{addr:08X} exceeds 32 bit '
                    'address space'
                )
            
            length = len(data_wr)
        
        if word_flag or long_flag:
            length = 1

            data_wr = convert_hex_to_bytes(data)

            if word_flag:
                if len(data_wr) > 2:
                    raise ValueError(
                        'Data has invalid length, must be maximum of 2 bytes'
                    )
                
                if len(data_wr) < 2:
                    data_wr = (b'\x00' * (2 - len(data_wr))) + data_wr
            elif long_flag:
                if len(data_wr) > 4:
                    raise ValueError(
                        'Data has invalid length, must be maximum of 4 bytes'
                    )
                
                if len(data_wr) < 4:
                    data_wr = (b'\x00' * (4 - len(data_wr))) + data_wr

        length_be = struct.pack('>L', length)
        addr_be = struct.pack('>L', convert_arg_to_long(addr))
    elif base is not None:
        # Loading binary
        base = convert_arg_to_long(base)

        if data is None:
            raise Exception(
                'Filename must be specified via the data argument when '
                'loading binary data'
            )
        
        if rd_flag is True or wr_flag is True:
            print(
                '--read and --write are ignored during binary load. '
                '--write assumed.'
            )
        
        if base & 0x1 == 1:
            raise ValueError('Base must be word aligned')

        length = os.stat(data).st_size

        if not (2 <= length <= 0x100000000):
            raise ValueError(
                'Size of file is invalid. Minimum 2 bytes, maximum '
                '4294967296, in 2 byte increments.'
            )
        
        if base + length > 0x100000000:
            raise Exception(
                f'{length} bytes from 0x{base:08X} exceeds 32 bit address '
                'space'
            )

        with open(data, 'r+b') as file:
            data_wr = file.read(length)
        
        base_be = struct.pack('>L', convert_arg_to_long(base))
        length_be = struct.pack('>L', length)

    if exec is not None:
        # Performing a JSR
        exec = convert_arg_to_long(exec)

        if exec & 0x1 == 1:
            raise ValueError('JSR address must be word aligned')

        exec_be = struct.pack('>L', exec)
    elif jump is not None:
        # Performing a JMP
        jump = convert_arg_to_long(jump)

        if jump & 0x1 == 1:
            raise ValueError('JMP address must be word aligned')

        jump_be = struct.pack('>L', jump)

    ######################################
    # Establish connection with bootloader
    ser = Serial(
        DEV,
        baudrate=BAUD,
        timeout=1
    )

    if ser.in_waiting > 0:
        ser.read(size=ser.in_waiting)
    
    # Wait for serial loader to be available
    print('Waiting for serial loader availability:', end='', flush=True)

    failed = 0

    while True:
        ser.write(bytes([1]))
        ser.flush()

        try:
            if ord(ser.read(size=1)) == 2:
                print(' OK')
                break
        except TypeError:
            if failed == 0:
                print(' ', end='')

            failed += 1

            print('.', end='', flush=True)

            if failed == RETRIES:
                print(' Failed after too many attempts')

                return

    ###################
    # Perform action(s)

    if addr is not None:
        if rd_flag is True:
            # Reading memory - send the command
            data_tx = bytes(b'\x08' + length_be + addr_be)

            ser.write(data_tx)
            ser.flush()

            failed = 0

            while True:
                try:
                    if ord(ser.read(size=1)) == 9:
                        break
                except TypeError:
                    if failed == 0:
                        print(' ', end='')

                    failed += 1

                    print('.', end='', flush=True)

                    if failed == RETRIES:
                        print(' Failed: transfer not acknowledged')

                        return

            print(
                f'Reading {length} bytes from 0x{addr:08X}: ',
                end='',
                flush=True
            )

            to_rx = length
            data_rx = []
            failed = 0

            while to_rx > 0:
                try:
                    data_rx.append(ord(ser.read(size=1)))
                except TypeError:
                    if failed == 0:
                        print(' ', end='')

                    failed += 1

                    print('.', end='', flush=True)

                    if failed == RETRIES:
                        print(' Failed: transfer failed, too many timeouts')

                        return
                    else:
                        continue

                to_rx -= 1

                if to_rx % 100 == 0:
                    print('.', end='', flush=True)
            
            if failed == 0:
                print(' OK')
            else:
                print(
                    'WARNING: '
                    ' Data is likely not valid due to timeouts when receiving'
                )
            
            if data is None:
                # hexdump the data
                hexdump(bytes(data_rx), addr)
            else:
                # Write the data into the filename specified
                # print(data)
                with open(data, 'w+b') as file:
                    file.write(bytes(data_rx))

        elif wr_flag is True:
            # Writing memory - send the command and data
            print(
                f'Writing {length} bytes to 0x{addr:08X}:',
                end='',
                flush=True
            )

            data_tx = bytes(b'\x03' + length_be + addr_be + data_wr)

            ser.write(data_tx)
            ser.flush()

            failed = 0

            while True:
                try:
                    if ord(ser.read(size=1)) == 4:
                        break
                except TypeError:
                    if failed == 0:
                        print(' ', end='')

                    failed += 1

                    print('.', end='', flush=True)

                    if failed == RETRIES:
                        print(' Failed: transfer not acknowledged')

                        return

            print(' OK')
        elif word_flag is True or long_flag is True:
            # Writing a word or long
            if word_flag is True:
                print(
                    f'Writing word to 0x{addr:08X}:',
                    end='',
                    flush=True
                )

                data_tx = bytes(b'\x0A\x02' + length_be + addr_be + data_wr)
            elif long_flag is True:
                print(
                    f'Writing long to 0x{addr:08X}:',
                    end='',
                    flush=True
                )

                data_tx = bytes(b'\x0A\x04' + length_be + addr_be + data_wr)
            
            ser.write(data_tx)
            ser.flush()

            failed = 0

            while True:
                try:
                    if ord(ser.read(size=1)) == 11:
                        break
                except TypeError:
                    if failed == 0:
                        print(' ', end='')

                    failed += 1

                    print('.', end='', flush=True)

                    if failed == RETRIES:
                        print(' Failed: transfer not acknowledged')

                        return

            print(' OK')
    elif base is not None:
        # Send the code over
        start = time.time()

        print(f'Loading {length} bytes to 0x{base:08X}:', end='', flush=True)

        data_tx = bytes(b'\x03' + length_be + base_be + data_wr)

        ser.write(data_tx)
        ser.flush()

        failed = 0

        while True:
            try:
                if ord(ser.read(size=1)) == 4:
                    break
            except TypeError:
                if failed == 0:
                    print(' ', end='')

                failed += 1

                print('.', end='', flush=True)

                if failed == 15:
                    print(' Failed: transfer not acknowledged')

                    return

        duration = time.time() - start

        print(' Done in %.3fs' % duration)

        # If user chose to execute their code, send that command
        failed = 0

        if exec is not None:
            pc = struct.pack('>L', exec)
            data_tx = bytes(b'\x05' + pc)

            print(f'Executing from 0x{exec:08X}:', end='', flush=True)
        elif jump is not None:
            pc = struct.pack('>L', jump)
            data_tx = bytes(b'\x06' + pc)

            print(f'Jumping to 0x{jump:08X}:', end='', flush=True)
        
        if exec is not None or jump is not None:
            ser.write(data_tx)
            ser.flush()

            while True:
                try:
                    if ord(ser.read(size=1)) == 7:
                        break
                except TypeError:
                    if failed == 0:
                        print(' ', end='')
                    
                    failed += 1

                    print('.', end='', flush=True)

                    if failed == 2:
                        print(' Failed: execution not acknowledged')

                        return

            print(' OK')

        # After loading code, print out anything that the board sends back
        print()
        print('============================================================')
        while True:
            try:
                char = ser.read(size=1)

                if char:
                    print(char.decode('utf-8'), end='')
            except KeyboardInterrupt:
                # Allow us to exit on Ctrl-C
                break

    ser.close()











def hexdump(data, addr):
    """ Prints a nicely formatted hex dump of the supplied data, with user
    supplied address to display on the left hand side.

    Data is indented according to the address supplied such that it always
    displays most naturally aligned to 16 byte boundaries.
    """
    print(
        ' -------- -------- -------- -------- --------  ----------------'
    )

    dataptr = 0

    line_spaces = addr % 16
    addr &= ~(0xF)

    while dataptr < len(data):
        bytesleft = len(data) - dataptr

        if line_spaces > 0:
            line_bytes = 16 - line_spaces
        else:
            line_bytes = 16 if bytesleft > 16 else bytesleft

        print(f' {addr:08x} ', end='')

        if line_spaces > 0:
            for i in range(line_spaces):
                print('  ', end='')

                if i % 4 == 3:
                    print(' ', end='')

        ctr = line_spaces

        for i in range(16 - line_spaces):
            if i < line_bytes and i < len(data):
                print(f'{data[dataptr + i]:02x}', end='')
            else:
                print('  ', end='')
            
            if ctr % 4 == 3:
                print(' ', end='')
            
            ctr += 1

        print(' ', end='')

        if line_spaces > 0:
            print(' ' * line_spaces, end='')

        for i in range(line_bytes):
            if i < len(data):
                c = data[dataptr + i : dataptr + i + 1]

                if c[0] >= 32 and c[0] < 0x7f:
                    print(c.decode('latin-1'), end='')
                else:
                    print('.', end='')
            else:
                print(' ', end='')

        print()

        addr += 16
        dataptr += line_bytes
        line_spaces = 0


if __name__ == '__main__':
    main()
