#include <stdio.h>
#include <string.h>

#include <malloc.h>

#include <openssl/sha.h>

#include <bitchain.h>
#include <bitblock.h>
#include <bithash.h>
#include <blockfile.h>

char* getfilehash(char* path){
	char hash[BITBLOCK_FILENAME_HASH_LENGTH];
	calc_sha256(path, hash);

	return hash;
};

char* getblockhash(char* block){
	char hash[BITBLOCK_DATA_NAME_BLOCK_HASH_LENGTH];
	return hash;
};

int calc_sha256(char* path, char output[65]){
	FILE *file = fopen(path, "rb");

        if(!file) return -1;

	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	const int bufSize = 32768;
	unsigned char *buffer = malloc(bufSize);
	int bytesRead = 0;

	if(!buffer) return -1;

	while((bytesRead = fread(buffer, 1, bufSize, file)))
	{
		SHA256_Update(&sha256, buffer, bytesRead);
	}

	SHA256_Final(hash, &sha256);
	sha256_hash_string(hash, output);

	fclose(file);
	free(buffer);

	return 0;
}

void sha256_hash_string(unsigned char hash[SHA256_DIGEST_LENGTH], char outputBuffer[65])
{
	int i = 0;

	for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
	}

	outputBuffer[64] = 0;
}


