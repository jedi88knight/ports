--- get.c.orig	2000-06-21 19:15:41 UTC
+++ get.c
@@ -55,6 +55,8 @@
 #ifdef STONE_SSL
 #include <openssl/ssl.h>
 #include <openssl/bio.h>
+#include <openssl/opensslconf.h>
+#include <openssl/err.h>
 #endif
 
 #include "sysdep.h"
@@ -169,27 +171,33 @@ get(char *loc, NETPORT port, char *url, 
       OpenSSL_add_all_algorithms();
       OpenSSL_add_ssl_algorithms();
 
-		if(ssl_version != NULL && strcasecmp(ssl_version, "SSLv23") == 0) {
-			if((ctx = SSL_CTX_new(SSLv23_client_method())) == NULL) {
-				ERR_print_errors_fp(stderr);
-				goto error;
-			}
-			D_PRINTF( "SSL version = SSLv23\n" );
-		}
-		else if(ssl_version != NULL && strcasecmp(ssl_version, "SSLv2") == 0) {
+#ifndef OPENSSL_NO_SSL2
+		if(ssl_version != NULL && strcasecmp(ssl_version, "SSLv2") == 0) {
 			if((ctx = SSL_CTX_new(SSLv2_client_method())) == NULL) {
 				ERR_print_errors_fp(stderr);
 				goto error;
 			}
 			D_PRINTF( "SSL version = SSLv2\n" );
 		}
-		else {
+		else
+#endif
+#ifndef OPENSSL_NO_SSL3_METHOD
+		if(ssl_version != NULL && strcasecmp(ssl_version, "SSLv3") == 0) {
 			if((ctx = SSL_CTX_new(SSLv3_client_method())) == NULL) {
 				ERR_print_errors_fp(stderr);
 				goto error;
 			}
 			D_PRINTF( "SSL version = SSLv3\n" );
 		}
+		else
+#endif
+		{
+			if((ctx = SSL_CTX_new(SSLv23_client_method())) == NULL) {
+				ERR_print_errors_fp(stderr);
+				goto error;
+			}
+			D_PRINTF( "SSL version = SSLv23\n" );
+		}
 		
 		/* set preferred cipher */
 		if(ssl_cipher != NULL && strlen(ssl_cipher) > 0) {
