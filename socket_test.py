#!/usr/bin/env python

import socket   #for sockets
import sys  #for exit


s = socket.socket()


print('Socket Created')
ip = '192.168.43.233'
port = 80

s.connect((ip , port))
print 'Socket Connected to ' + ip
message = "efdeyherfsgwrsf"
s.sendall(message)
print 'Message send successfully'