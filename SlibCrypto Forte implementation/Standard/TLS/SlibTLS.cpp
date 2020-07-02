/*
 * SlibTLS.cpp
 *
 *  
 */

#include "SlibTLS.h"

SlibTLS* SlibTLS::m_pInstance = NULL;

SlibTLS* SlibTLS::Instance()
{
	if (!m_pInstance)
	   m_pInstance = new SlibTLS;
	return m_pInstance;
}


SlibTLS::SlibTLS() {
	// TODO Auto-generated constructor stub

}

SlibTLS::~SlibTLS() {
	// TODO Auto-generated destructor stub
}

SSL_CTX* SlibTLS::opensslGetContext() const {
	return ctx;
}

int SlibTLS::opensslGetSocketFD() const {
	return sockfd;
}

SSL* SlibTLS::opensslGetSSLHandle() const {
	return ssl;
}

int SlibTLS::opensslServerCreateContext() {
    const SSL_METHOD *method;

    method = SSLv23_server_method();//TLS_server_method();// //TLSv1_2_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
		perror("Unable to create SSL context");
		ERR_print_errors_fp(stderr);
		return SLIB_ERROR;
    }
	
    return SLIB_SUCCESS; // because openssl returns 1 on success
}

void SlibTLS::opensslServerInit() const {
	SSL_load_error_strings();
	OpenSSL_add_ssl_algorithms();
}

int SlibTLS::opensslServerConfigureContext(SSL_CTX *ctx, const char* cert, const char* key) {
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
	ssl = SSL_new(ctx);
	//printf("Awais: Check private key result = %d\n", SSL_CTX_check_private_key(ctx));
    return SLIB_SUCCESS;
}

int SlibTLS::opensslServerCreateSocket(int port) {
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
		perror("Unable to create socket");
		return SLIB_ERROR;
    }

    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("Unable to bind");
		return SLIB_ERROR;
    }

    if (listen(sockfd, 1) < 0) {
		perror("Unable to listen");
		return SLIB_ERROR;
    }

    return SLIB_SUCCESS;
}

int SlibTLS::opensslServerHandshakeWait() {
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);

	int client = accept(sockfd, (struct sockaddr*)&addr, &len);
	if (client < 0) {
		perror("Unable to accept");
		return SLIB_ERROR;
	}

	//ssl = SSL_new(ctx);
	SSL_set_fd(ssl, client);

	if (SSL_accept(ssl) <= 0) {
		ERR_print_errors_fp(stderr);
		return SLIB_ERROR;
	}
	return SLIB_SUCCESS;
}


void SlibTLS::opensslClientInit() const{
	SSL_load_error_strings();
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	SSL_library_init();
}

int SlibTLS::opensslClientCreateSocket() {
	  sockfd = socket(AF_INET, SOCK_STREAM, 0);
	  if(sockfd == -1) {
		  perror("Unable to create socket");
		  return SLIB_ERRORN1;
	  }
	  return SLIB_SUCCESS;
}

int SlibTLS::opensslClientCreateContext() {
    const SSL_METHOD *method;

    method = SSLv23_client_method();//TLS_client_method(); ////TLSv1_2_client_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
		perror("Unable to create SSL context");
		ERR_print_errors_fp(stderr);
		return SLIB_ERROR;
    }

    return SLIB_SUCCESS; // because openssl returns 1 on success
}

int SlibTLS::opensslClientHandshake(const char *ip, int port) {
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

int SlibTLS::opensslSetCiphers(SSL_CTX* ctx, int cipherListId) {
	const char* preferred_ciphers = opensslCipherSuite(cipherListId);

	if(preferred_ciphers == NULL) {
		printf("Invalid cipher suite ID\n");
		return SLIB_ERROR;
	}

	int res = SSL_CTX_set_cipher_list(ctx, preferred_ciphers);//SSL_CTX_set_ciphersuites(ctx, preferred_ciphers);
	if(res == 1) return SLIB_SUCCESS; else return SLIB_ERROR;
}

int SlibTLS::opensslSetCiphers(SSL* ssl, int cipherListId) {
	const char* preferred_ciphers = opensslCipherSuite(cipherListId);
	if(preferred_ciphers == NULL) {
		printf("Invalid cipher suite ID.\n");
		return SLIB_ERROR;
	}
	int res = SSL_set_cipher_list(ssl, preferred_ciphers);//SSL_set_ciphersuites(ssl, preferred_ciphers);
	if(res == 1) return SLIB_SUCCESS; else return SLIB_ERROR;
}

int SlibTLS::opensslWrite(SSL *ssl, const uint8_t *data, size_t datalen) {
	if(SSL_write(ssl, data, datalen) <= 0) {
		ERR_print_errors_fp(stderr);
		return SLIB_ERRORN1;
	}
	return SLIB_SUCCESS;
}

int SlibTLS::opensslRead(SSL *ssl, uint8_t *data, size_t datalen) {

	if(SSL_read(ssl, data, datalen) <= 0) {
		ERR_print_errors_fp(stderr);
		return SLIB_ERRORN1;
	}
	return SLIB_SUCCESS;
}

const char* SlibTLS::opensslCipherSuite(int id) {
	if(id == SLIB_CIPHER_SUITE_DEFAULT)
		return "TLS_AES_256_GCM_SHA384:TLS_CHACHA20_POLY1305_SHA256:TLS_AES_128_GCM_SHA256";
	if(id == SLIB_CIPHER_SUITE_TLS_AES_128_GCM_SHA256)
		return "TLS_AES_128_GCM_SHA256";
	if(id == TLS_CHACHA20_POLY1305_SHA256)
		return "TLS_CHACHA20_POLY1305_SHA256";
	if(id == ECDHE_RSA_AES256_SHA256)
		return "ECDHE-RSA-AES256-SHA256";
	if(id == ECDHE_RSA_AES128_GCM_SHA256)
		return "ECDHE-RSA-AES128-GCM-SHA256";
	if(id == SLIB_CIPHER_SUITE_TLS2_DEFAULT)
		return "HIGH:!aNULL:!kRSA:!PSK:!SRP:!MD5:!RC4";
	if(id == SLIB_CIPHER_SUITE_TLS2_ENULL)
		return "eNULL";
	if(id == TLS_ECDHE_ECDSA_WITH_NULL_SHA)
		return "TLS-ECDHE-ECDSA-WITH-NULL-SHA";
	if(id == TLS_COMPLEMENTOFALL)
		return "COMPLEMENTOFALL:aNULL";
	if(id == TLS_NULL_SHA)
		return "LOW:NULL-SHA256:!kRSA";
	if(id == SLIB_CIPHER_SUITE_TLS2_DEFAULT2)
		return "LOW:!aNULL:!kRSA:!PSK:!SRP:!MD5:!RC4:eNULL";
	if(id == SLIB_CIPHER_SUITE_TLS2_LOW)  
		return "LOW";
	if(id == SLIB_CIPHER_SUITE_TLS2_LOW1)  
		return "ECDHE-RSA-AES128-SHA256";
	if(id == SLIB_CIPHER_SUITE_TLS2_NULL_SHA)  
		return "NULL-SHA256";

	return NULL;
}
