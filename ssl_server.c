//ssl_server.c
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>
#include "openssl/ssl.h"
#include "openssl/err.h"
 
#define FAIL    -1
 
 //Open listener for client to connect
int OpenListener(int port)
{   
    int sd;
    struct sockaddr_in addr;
 
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ) //bind the IP and port number
    {
        perror("can't bind port");
        abort();
    }
    if ( listen(sd, 10) != 0 )
    {
        perror("Can't configure listening port");
        abort();
    }
    return sd;
}
 
//check if user is root
int isRoot()
{
    if (getuid() != 0)
        return 0;
    else   
        return 1;    
}

//Init server instance and context
SSL_CTX* InitServerCTX(void)
{   
    const SSL_METHOD *method;
    SSL_CTX *ctx;
 
    OpenSSL_add_all_algorithms();  //load & register all cryptos, etc. 
    SSL_load_error_strings();   // load all error messages */
    method = SSLv23_server_method();  // create new server-method instance 
    ctx = SSL_CTX_new(method);   // create new context from method
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

//Load the certificate 
void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile)
{
    //set the local certificate from CertFile
    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    //set the private key from KeyFile
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    //verify private key 
    if ( !SSL_CTX_check_private_key(ctx) )
    {
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}

//Serve the connection -- threadable
void Servlet(SSL* ssl) 
{   
    char buf[1024];
    char reply[1024];
    int sd, bytes;
    const char* echo="%s Opps! I am your server!";
 
    if ( SSL_accept(ssl) == FAIL ) //do SSL-protocol accept
        ERR_print_errors_fp(stderr);
    else
    {
        bytes = SSL_read(ssl, buf, sizeof(buf)); // get request 
        if ( bytes > 0 )
        {
            buf[bytes] = 0;
            printf("Client message: \"%s\"\n", buf);
            printf("---------------------------------------------\n");
            sprintf(reply, echo, buf);   // construct reply
            SSL_write(ssl, reply, strlen(reply)); // send reply 
        }
        else
            ERR_print_errors_fp(stderr);
    }
    sd = SSL_get_fd(ssl);       /* get socket connection */
    SSL_free(ssl);         /* release SSL state */
    close(sd);          /* close connection */
}
 
 //main function
int main(int count, char *strings[])
{   
    SSL_CTX *ctx;
    int server;
    char *portnum;
 
    if(!isRoot())
    {
        printf("This program must be run as root/sudo user!\n");
        exit(0);
    }

    if ( count != 2 )
    {
        printf("Usage: %s <portnum>\n", strings[0]);
        exit(0);
    }

    SSL_library_init(); //init SSL library
    printf("Initialize SSL library.\n");
    portnum = strings[1]; //assign the port num
    ctx = InitServerCTX();  //initialize SSL 
    LoadCertificates(ctx, "mycert.pem", "mykey.pem"); // load certs and key
    server = OpenListener(atoi(portnum));    // create server socket
    printf("Open SSL server socket, port:%d\n",atoi(portnum));
    printf("Waiting for client to connect...\n");
    
    while (1)
    {   
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;
 
        int client = accept(server, (struct sockaddr*)&addr, &len);  // accept client connection 
        printf("Connection from: %s:%d\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        ssl = SSL_new(ctx);              // get new SSL state with context 
        SSL_set_fd(ssl, client);      // set connection socket to SSL state
        Servlet(ssl);         // service client connection 
    }

    close(server);          // close server socket
    SSL_CTX_free(ctx);         // release context
}
