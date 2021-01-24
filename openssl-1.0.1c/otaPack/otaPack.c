#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aes.h>

unsigned char indate[AES_BLOCK_SIZE];
unsigned char outdate[AES_BLOCK_SIZE];
unsigned char decryptdate[AES_BLOCK_SIZE];
//unsigned char userkey[] = "\x09\x8F\x6B\xCD\x46\x21\xD3\x73\xCA\xDE\x4E\x83\x26\x27\xB4\xF6";
//unsigned char IV[] = "\x0A\x91\x72\x71\x6A\xE6\x42\x84\x09\x88\x5B\x8B\x82\x9C\xCB\x05";

static void _encrypt_file(char *file_in, char *file_out, char *passwd);
static void _decrypt_file(char *file_in, char *file_out, char *passwd);

static void _encrypt_file(char *file_in, char *file_out, char *passwd)
{
	FILE *fp_in = fopen(file_in, "r+");
	FILE *fp_out = fopen(file_out, "w+");
	unsigned char iv[AES_BLOCK_SIZE];	

	int postion = 0;
	int bytes_read, bytes_write;
	AES_KEY aes_key;	

	AES_set_encrypt_key(passwd, 128, &aes_key);
	while(1)
	{
		memset(iv, 0, AES_BLOCK_SIZE);
		bytes_read = fread(indate, 1, AES_BLOCK_SIZE, fp_in);
        AES_cfb128_encrypt(indate, outdate, bytes_read, &aes_key, iv, &postion, AES_ENCRYPT);
        bytes_write = fwrite(outdate, 1, bytes_read, fp_out);
		if(bytes_read < AES_BLOCK_SIZE)
			break;
	}
	fclose(fp_in);
	fclose(fp_out);
}

static void _decrypt_file(char *file_in, char *file_out, char *passwd)
{
    FILE *fp_in = fopen(file_in, "r+");
    FILE *fp_out = fopen(file_out, "w+");
    unsigned char iv[AES_BLOCK_SIZE];
	int postion = 0;
    int bytes_read, bytes_write;
	AES_KEY aes_key;

    AES_set_encrypt_key(passwd, 128, &aes_key);
	while (1) 
	{
		memset(iv, 0, AES_BLOCK_SIZE);
        bytes_read = fread(outdate, 1, AES_BLOCK_SIZE, fp_in);
        AES_cfb128_encrypt(outdate, decryptdate, bytes_read, &aes_key, iv, &postion, AES_DECRYPT);
        bytes_write = fwrite(decryptdate, 1, bytes_read, fp_out);
        if (bytes_read < AES_BLOCK_SIZE)
            break;
    }
    fclose(fp_in);
    fclose(fp_out);
}

int main(int argc, char *argv[])
{
	if(argc < 5)
	{
		printf("enter parameter error!!!\r\n");
		exit(-1);
	}
	char file_in[64];
	char file_out[64];
	int mode = -1;
	char passwd[16+1];

	if(*(argv[1]+0) == '-')	//加密
	{
		if(*(argv[1]+1) == 'd')
			mode = AES_DECRYPT;
		else if(*(argv[1]+1) == 'e')
			mode = AES_ENCRYPT;
	}
	
	strcpy(file_in, argv[2]);
	strcpy(file_out, argv[3]);
	strcpy(passwd, argv[4]);

	if(mode == AES_DECRYPT)
	{
		_decrypt_file(file_in, file_out, passwd);	
	}
	else if(mode == AES_ENCRYPT)
	{
		_encrypt_file(file_in, file_out, passwd);
	}
}
