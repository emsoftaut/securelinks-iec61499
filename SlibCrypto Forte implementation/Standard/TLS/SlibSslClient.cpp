/*
 * SlibSslClient.cpp
 *
 *  
 */
#include "SlibSslClient.h"

#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibSslClient_gen.cpp"
#endif

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>


#define DIV 1048576
#define WIDTH 7
#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#define SLIB_ERROR 0
#define SLIB_SUCCESS 1

static SSL_CTX *ctx = NULL;
static SSL *ssl = NULL;
static int sockfd;

void slib_client_init_openssl() {
	SSL_load_error_strings();
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	SSL_library_init();
}

int slib_client_create_socket() {

	  sockfd = socket(AF_INET, SOCK_STREAM, 0);
	  if(sockfd == -1) {
		  perror("Unable to create socket");
		  return -1;
	  }

	  return SLIB_SUCCESS;
}

int slib_client_create_context() {
    const SSL_METHOD *method;

    method = TLS_client_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
		perror("Unable to create SSL context");
		ERR_print_errors_fp(stderr);
		return SLIB_ERROR;
    }

    return SLIB_SUCCESS; // because openssl returns 1 on success
}

int slib_client_do_handshake(char *ip, int port) {
	  struct sockaddr_in dest_addr;

	  dest_addr.sin_family = AF_INET;
	  dest_addr.sin_port = htons(port);
	  dest_addr.sin_addr.s_addr = inet_addr(ip);

	  if ( connect(sockfd, (struct sockaddr *) &dest_addr, sizeof(struct sockaddr)) == -1 ) {
		  perror("Unable to connect socket");
		  return SLIB_ERROR;
	  }

	ssl = SSL_new(ctx);
	SSL_set_fd(ssl, sockfd);

	if ( SSL_connect(ssl) != 1 ) {
		ERR_print_errors_fp(stderr);
		return SLIB_ERROR;
	}
	return SLIB_SUCCESS;
}

