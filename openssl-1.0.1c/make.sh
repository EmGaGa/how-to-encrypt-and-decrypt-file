#! /bin/sh
aa=`pwd`

echo $aa

bb=`which mipsel-linux-gnu-gcc`

echo $bb

KERNEL_DIR=$bb/../mipsel-linux-gnu/sysroot/usr/include

ROOT=../../..     
STAGING_DIR=$ROOT/out/rootfs-staging

echo $KERNEL_DIR

INSTALL_DIR=$aa/object

BUILD_STATIC_LIB=no

if [ "$BUILD_STATIC_LIB" = "yes" ]; then
#编译静态库
echo "static lib ----"
./config --prefix=$INSTALL_DIR --openssldir=$INSTALL_DIR/openssl --cross-compile-prefix=mipsel-linux-gnu- no-asm no-shared no-zlib no-sse2 no-comp no-dso no-gmp no-rfc3779 no-krb5 no-rc5 no-zlib-dynamic no-hw no-md2 no-mdc2 no-idea no-camellia no-ec no-ecdsa no-ecdh no-store no-ripemd no-bf no-cast no-dsa 
else
#编译动态库
echo "dyn lib ----"
./config --prefix=$INSTALL_DIR --openssldir=$INSTALL_DIR/openssl --cross-compile-prefix=mipsel-linux-gnu- shared no-dso no-asm no-zlib no-sse2 no-comp no-gmp no-rfc3779 no-krb5 no-rc5 no-zlib-dynamic no-hw no-md2 no-mdc2 no-idea no-camellia no-ec no-ecdsa no-ecdh no-store no-ripemd no-bf no-cast no-dsa 
fi

make build_libs

if [ "$BUILD_STATIC_LIB" = "yes" ]; then
#编译静态库
cp *.a $STAGING_DIR/lib
else
#编译动态库

echo "cp dyn lib ---"
cp -a -t $STAGING_DIR/usr/lib/ libcrypto.so.1.0.0 libssl.so.1.0.0 libcrypto.so libssl.so
fi

rsync -a -r -L --exclude=".svn" ./include/openssl $STAGING_DIR/usr/include