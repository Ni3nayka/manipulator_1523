import socket               # Import socket module

s = socket.socket()         # Create a socket object
host = "192.168.1.62" #socket.gethostname() # Get local machine name
port = 12345                # Reserve a port for your service.

s.connect((host, port))     
s.send(b'Hi i am aslam')
print(s.recv(1024))
s.close                     # Close the socket when done     
