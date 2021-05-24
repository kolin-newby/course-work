# kone9079
# miha5997

# Takes around 10 to 15 minutes to run on given pcap file


import sys
from scapy.all import *


def main(argv):

	# flags = 0x012 is [SYN,ACK]
	# flags = 0x002 is [SYN]

	pcap_file = argv[0]
	data_reader = PcapReader(pcap_file)

	# to limit reader for testing purposes
	row_cnt = 0
	# IP : (snt, rcv)
	pkt_dict = {}
	# list of IP's to return at end
	detected = []

	# Only sending [SYN] & only recieving [SYN,ACK]
	for pkt in data_reader:
		if (pkt.haslayer(IP) and pkt.haslayer(TCP) and pkt.haslayer(Ether)) and (pkt[TCP].flags == 0x002 or pkt[TCP].flags == 0x012):
			# print(pkt.show())

			src = pkt[IP].src
			dst = pkt[IP].dst

			# if SYN
			if pkt[TCP].flags == 0x002:
				if src not in pkt_dict:
					pkt_dict[src] = (1,0)
				else:
					pkt_dict[src] = (pkt_dict[src][0] + 1, pkt_dict[src][1])
			# if SYN,ACK
			else:
				if dst not in pkt_dict:
					pkt_dict[dst] = (0,1)
				else:
					pkt_dict[dst] = (pkt_dict[dst][0], pkt_dict[dst][1] + 1)

	z_cnt = 0
	for ip in pkt_dict:
		if pkt_dict[ip][1] == 0:
			if pkt_dict[ip][0] > 0:
				detected.append(ip)
				continue
		if (pkt_dict[ip][0] > (3 * (pkt_dict[ip][1]))):
			detected.append(ip)

	for x in detected:
		print(str(x))


if __name__ == '__main__':
	main(sys.argv[1:])