forte_add_module(TLS "TLS FBs")

#set(OPENSSL_LIBRARY_DIR "C://openssl-1.1.1d-win64-mingw//lib" CACHE PATH "OpenSSL Library Directory")
#set(OPENSSL_INCLUDE_DIR "C://openssl-1.1.1d-win64-mingw//include" CACHE PATH "OpenSSL Library Directory")

#forte_add_sourcefile_hcpp(SlibSslClient)
#forte_add_sourcefile_hcpp(SlibSslServer)

forte_add_sourcefile_hcpp(SlibTLSClientHandShake)
forte_add_sourcefile_hcpp(SlibTLSServerHandShake)
forte_add_sourcefile_hcpp(SlibTLSWrite)
forte_add_sourcefile_hcpp(SlibTLSRead)
forte_add_sourcefile_hcpp(SlibTLS)

#forte_add_include_directories( ${OPENSSL_INCLUDE_DIR})
#forte_add_link_directories(${OPENSSL_LIBRARY_DIR})
#forte_add_link_library(libssl.a libcrypto.a -lws2_32)
forte_add_link_library(-lssl -lcrypto)



