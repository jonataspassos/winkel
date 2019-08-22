import sys
from bluetooth import *

HOST = sys.argv[1]       # The remote host
PORT = 8888                 # Server port

mac = "B4:F7:A1:61:49:86"

s=BluetoothSocket( RFCOMM )

s.connect((HOST, PORT))

while True :
   message = raw_input('Send:')
   if not message : break
   s.send(message)
   data = s.recv(1024)
   print ('Received', data)
s.close()
