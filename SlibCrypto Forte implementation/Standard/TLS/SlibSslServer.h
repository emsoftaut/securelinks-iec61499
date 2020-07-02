/*
 * SlibSsl.h
 *
 *  
 */

#ifndef SRC_MODULES_SLIBCRYPTO_SLIBSSLSERVER_H_
#define SRC_MODULES_SLIBCRYPTO_SLIBSSLSERVER_H_

#include <openssl/ssl.h>
#include <openssl/err.h>

extern "C" {

	void init_openssl();
	SSL_CTX* get_context();
	int create_context();
	int configure_context(SSL_CTX *ctx, char* cert, char* key);
	int create_socket(int port);
	int get_socket_fd();
	int wait_for_handshake();
}

#endif /* SRC_MODULES_SLIBCRYPTO_SLIBSSLSERVER_H_ */
