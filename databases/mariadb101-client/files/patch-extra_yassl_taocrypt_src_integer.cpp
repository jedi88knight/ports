--- extra/yassl/taocrypt/src/integer.cpp.orig	2015-12-23 15:33:29 UTC
+++ extra/yassl/taocrypt/src/integer.cpp
@@ -74,7 +74,7 @@ template <class T>
 CPP_TYPENAME AlignedAllocator<T>::pointer AlignedAllocator<T>::allocate(
                                            size_type n, const void *)
 {
-    if (n > this->max_size())
+    if (n > AlignedAllocator<T>::max_size())
         return 0;
     if (n == 0)
         return 0;
