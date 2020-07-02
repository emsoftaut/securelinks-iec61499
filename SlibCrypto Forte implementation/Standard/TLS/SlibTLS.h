/*
 * SlibTLS.h
 *
 * 
 */

#ifndef SRC_MODULES_SLIBCRYPTO_STANDARD_TLS_SLIBTLS_H_
#define SRC_MODULES_SLIBCRYPTO_STANDARD_TLS_SLIBTLS_H_

/*#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>


#define DIV 1048576
#define WIDTH 7
#endif*/

//#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
//#endif

#include <openssl/ssl.h>
#include <openssl/err.h>

#define SLIB_ERROR 0
#define SLIB_ERRORN1 -1
#define SLIB_SUCCESS 1

#define SLIB_CIPHER_SUITE_DEFAULT 1
#define SLIB_CIPHER_SUITE_TLS_AES_128_GCM_SHA256 2
#define TLS_CHACHA20_POLY1305_SHA256 3
#define ECDHE_RSA_AES256_SHA256 4
#define ECDHE_RSA_AES128_GCM_SHA256 5

#define SLIB_CIPHER_SUITE_TLS2_DEFAULT 10
#define SLIB_CIPHER_SUITE_TLS2_ENULL 11
#define TLS_ECDHE_ECDSA_WITH_NULL_SHA 12
#define TLS_COMPLEMENTOFALL 13
#define TLS_NULL_SHA 14
#define SLIB_CIPHER_SUITE_TLS2_DEFAULT2 15
#define SLIB_CIPHER_SUITE_TLS2_LOW 16
#define SLIB_CIPHER_SUITE_TLS2_LOW1 17
#define SLIB_CIPHER_SUITE_TLS2_NULL_SHA 18


class SlibTLS {
public:
	static SlibTLS* Instance();


	virtual ~SlibTLS();

	SSL_CTX* opensslGetContext() const;
	SSL* opensslGetSSLHandle() const;
	int opensslGetSocketFD() const;


	void opensslServerInit() const;
	int opensslServerCreateContext();
	int opensslServerConfigureContext(SSL_CTX *ctx, const char* cert, const char* key);
	int opensslServerCreateSocket(int port);
	int opensslServerHandshakeWait();

	void opensslClientInit() const;
	int opensslClientCreateSocket();
	int opensslClientCreateContext();
	int opensslClientHandshake(const char *ip, int port);
	int opensslSetCiphers(SSL_CTX* ctx, int cipherListId);
	int opensslSetCiphers(SSL* ssl, int cipherListId);

	int opensslWrite(SSL *ssl, const uint8_t *data, size_t datalen);
	int opensslRead(SSL *ssl, uint8_t *data, size_t datalen);

	const char* opensslCipherSuite(int id);

private:
	SlibTLS();
	SlibTLS(SlibTLS const&){};
	SlibTLS& operator=(SlibTLS const&){};
	static SlibTLS* m_pInstance;

	SSL_CTX *ctx = NULL;
	SSL *ssl = NULL;
	int sockfd;

};



#endif /* SRC_MODULES_SLIBCRYPTO_STANDARD_TLS_SLIBTLS_H_ */
