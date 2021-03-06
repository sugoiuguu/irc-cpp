#ifndef _TCP_CONN_H_
#define _TCP_CONN_H_

#include <stdexcept>
#include <exception>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <signal.h>

#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

class TCPClient {
    std::string addr;
    char buf[4096];
    int sockfd, portno, n;
    struct hostent *server;
    struct sockaddr_in serv_addr;
    bool is_async;

    bool use_ssl;
    SSL_CTX *ctx;
    SSL *ssl;
    const SSL_METHOD *meth;

public:
    TCPClient(bool use_ssl, std::string addr, uint16_t portno);
    ~TCPClient();
    void close_connection();
    void send(std::string request);
    std::string receive();
    std::string get(std::string request);
    void set_async();
};

class TCPClientException : public std::exception {
    char except[1024];

public:
    TCPClientException(const char *msg);
    TCPClientException(const std::string &msg);
    const char *what() const throw();
};

#endif
