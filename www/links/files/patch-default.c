--- default.c.orig	2014-11-05 19:25:50 UTC
+++ default.c
@@ -824,7 +824,7 @@ void init_home(void)
 	get_compiler_name();
 	links_home = get_home(&first_use);
 	if (!links_home) {
-		fprintf(stderr, "Unable to find or create links config directory. Please check, that you have $HOME variable set correctly and that you have write permission to your home directory.\n\007");
+		fprintf(stderr, "Unable to find or create links config directory. Please check, that you have $HOME variable set correctly and that you have write permission to your home directory.\n");
 		sleep(3);
 		return;
 	}
