#!/bin/python3
import socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("127.0.0.1", 20001))
sock.settimeout(0.01)
while True:
	try:
		print("%c" % sock.recv(1).decode(), end='')
	except :
		continue
	
	
