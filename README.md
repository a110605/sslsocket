This is a proof of concept example using OpenSSL library to verfiy the 
certificate and key in server side. Both client and server will use 
default encryption alogrithm (AES-256-SHA) to create SSL socket connections.
The server will echo the message which received from client and send it back
to client side. 

Build OpenSSL Environment
	Under Ubuntu, just type "apt-get install openssl" and
	 "apt-get install libssl-dev" on command line. Or you can download
	the latest OpenSSL package at http://www.openssl.org/source/.

Compile Source Code
	Type "make" under sslsocket directory.It will automatically compile
	and generate the executable binary ssl_server, ssl_client.

To run the Server
	sudo ./ssl-server <portnum> 

To run the Client 
	./ssl-client <hostname> <portnum> 
