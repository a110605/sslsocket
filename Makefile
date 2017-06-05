CC = gcc                  
CFLAGS =  -Wall  -lssl -lcrypto
INC = -I /usr/foo/include   
LIB = -L/usr/lib   

all: server client
server: 
	${CC} ssl_server.c ${CFLAGS}  ${LIB}  -o ssl_server 
client: 
	${CC} ssl_client.c ${CFLAGS}  ${LIB}  -o ssl_client 
clean: 
	rm -rf ssl_server ssl_client