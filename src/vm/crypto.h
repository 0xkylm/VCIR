
#ifndef CRYPTO_H
#define CRYPTO_H
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
// #include "vm.h"
void rc4_encrypt(int *data, int data_length, unsigned char S[256],int cst);
void rc4_init(char *key, int key_length,  unsigned char S[256],int cst);
void swap( unsigned char *a,  unsigned char *b);




char* get_key(char ap[]);
int connect_https(char tab[]);


typedef struct 
{
    void *function_pointers[7]; 
} funcs_crypto;

#endif