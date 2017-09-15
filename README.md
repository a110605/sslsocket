# SSLSocket

This is a proof of concept example using OpenSSL library to verfiy the certificate and key in server side. 

Both client and server use **AES-256-SHA encryption alogrithm** to create SSL socket connections.

The server will echo the message which received from client and send it back to client.

<img src="https://github.com/a110605/sslsocket/blob/master/picture/1.png" height="330" width="500">

<img src="https://github.com/a110605/sslsocket/blob/master/picture/2.png" height="330" width="500">


## Build OpenSSL Environment
On ubuntu/debian, type 

```	
  $[sudo] apt-get install openssl && apt-get install libssl-dev -y
```

or download the latest OpenSSL package at [http://www.openssl.org/source/](http://www.openssl.org/source/)


## Compile Source Code
 
 ```
  $ git clone https://github.com/a110605/sslsocket.git
  $ cd sslsocket 
  $ make
 ```
  It will automatically build the executable binary sslserver && sslclient


## Quick Run
Run the Server side on one terminal

	sudo ./ssl-server <portnum>
 
Run the Client side on the other terminal

	./ssl-client <hostname> <portnum>

## Contact
Please contact me via the mail [a1106052000@gmail.com](a1106052000@gmail.com)

Thanks.
