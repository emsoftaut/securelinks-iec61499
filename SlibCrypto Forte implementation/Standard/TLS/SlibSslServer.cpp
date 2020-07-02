#include "SlibSslServer.h"

#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "SlibSslServer_gen.cpp"
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
static int sock_fd;

SSL_CTX* get_context() {
	return ctx;
}

void init_openssl() {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

int create_context() {
    const SSL_METHOD *method;

    method = TLS_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
		perror("Unable to create SSL context");
		ERR_print_errors_fp(stderr);
		return SLIB_ERROR;
    }

    return SLIB_SUCCESS; // because openssl returns 1 on success
}

int configure_context(SSL_CTX *ctx, char* cert, char* key) {
    SSL_CTX_set_ecdh_auto(ctx, 1);

    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, cert, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        return SLIB_ERROR;
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, key, SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        return SLIB_ERROR;
    }
    return SLIB_SUCCESS;
}

int get_socket_fd() {
	return sock_fd;
}

int create_socket(int port) {
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
		perror("Unable to create socket");
		return SLIB_ERROR;
    }

    if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("Unable to bind");
		return SLIB_ERROR;
    }

    if (listen(sock_fd, 1) < 0) {
		perror("Unable to listen");
		return SLIB_ERROR;
    }

    return SLIB_SUCCESS;
}

int wait_for_handshake() {
	struct sockaddr_in addr;
	int len = sizeof(addr);

	int client = accept(sock_fd, (struct sockaddr*)&addr, &len);
	if (client < 0) {
		perror("Unable to accept");
		return SLIB_ERROR;
	}

	ssl = SSL_new(get_context());
	SSL_set_fd(ssl, client);

	if (SSL_accept(ssl) <= 0) {
		ERR_print_errors_fp(stderr);
		return SLIB_ERROR;
	}
	return SLIB_SUCCESS;
}


