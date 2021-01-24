CC=cc
CFLAGS=-O -I../crypto/aes -I../include

OTAPACK_OBJS = otaPack.o ../libcrypto.a ../libssl.a

.c.o:
	$(CC) -c $(CFLAGS) $*.c

all: otaPack

otaPack:  $(OTAPACK_OBJS)
	$(CC) $(CFLAGS) -o $@ $(OTAPACK_OBJS)

test:
	./otaPack -e test.zip encrypt.zip 1234567890123456
	./otaPack -d encrypt.zip decrypt.zip 1234567890123456
	unzip decrypt.zip
clean:
	/bin/rm -f *.o otaPack
	/bin/rm -f encrypt.zip decrypt.zip
	/bin/rm -f test
