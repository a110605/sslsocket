SLSocket

This is a proof of concept example using OpenSSL library to verfiy the certificate and key in server side. 

Both client and server will use **default encryption alogrithm (AES-256-SHA)** to create SSL socket connections.
The server will echo the message which received from client and send it back to client side.

## Build OpenSSL Environment
On ubuntu/debian, type 

```	
sudo apt-get install openssl && apt-get install libssl-dev
```

or download the latest OpenSSL package at [http://www.openssl.org/source/](http://www.openssl.org/source/)


## Compile Source Code
 
  ```
    git clone https://github.com/a110605/sslsocket.git
     ```
       Type **make** under sslsocket directory.
         
	   It will automatically build the executable binary sslserver && sslclient


## Run
Run the Server side on one terminal

	sudo ./ssl-server <portnum>
	 
	 Run the Client side on the other terminal

	 	./ssl-client <hostname> <portnum>

## Contact
If there are any questions, please send me a email. 

[a1106052000@gmail.com](a1106052000@gmail.com)

Thanks.
