/*
 * SlibSslClient.h
 *
 *  
 */

#ifndef SRC_MODULES_SLIBCRYPTO_STANDARD_TLS_SLIBSSLCLIENT_H_
#define SRC_MODULES_SLIBCRYPTO_STANDARD_TLS_SLIBSSLCLIENT_H_

#include <openssl/ssl.h>
#include <openssl/err.h>


extern "C" {
	void slib_client_init_openssl();
	int slib_client_create_socket();
	int slib_client_create_context();
	int slib_client_do_handshake(char* ip, int port);
}

#endif /* SRC_MODULES_SLIBCRYPTO_STANDARD_TLS_SLIBSSLCLIENT_H_ */
