import socket               # Import socket module

s = socket.socket()         # Create a socket object
host = "192.168.1.62" #socket.gethostname() # Get local machine name
port = 12345                # Reserve a port for your service.
s.bind((host, port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.
while True:
   c, addr = s.accept()     # Establish connection with client.
   print ('Got connection from', addr)
   print (c.recv(1024))
   c.send(b'Thank you for connecting')
   c.close()                # Close the connection