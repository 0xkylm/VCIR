// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>



#include "crypto.h"

void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

void rc4_init( char *key, int key_length, unsigned char S[256],int cst) {
    for (int i = 0; i < cst; i++) {
        S[i] = i;
    }

    int j = 0;
    for (int i = 0; i < cst; i++) {
        j = (j + S[i] + key[i % key_length]) % cst;
        swap(&S[i], &S[j]);
    }
}

void rc4_encrypt(int *data, int data_length,unsigned  char S[256],int cst) {
    int i = 0;
    int j = 0;


    for (int k = 0; k < data_length; k++) {
        i = (i + 1) % cst;
        j = (j + S[i]) % cst;

        

        swap(&S[i], &S[j]);

        unsigned char key = S[(S[i] + S[j]) % cst];
        data[k] ^= key;

        
    }

}


char* get_key(char tab[]){


 return tab;
}



    
