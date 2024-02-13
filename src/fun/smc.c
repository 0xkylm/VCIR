#include "smc.h"

void _print(unsigned char txt[]) {
    int key = 11;
    printf("%d\n", key);
    for (int i = 0; i < strlen(txt); i++) {
      //  printf("%c", txt[i]);
    }
    printf("\0");
    printf("\0");
}

void changeProtect(void *addr, int memSize) {
    DWORD oldProtect;
    if (!VirtualProtect(addr, memSize, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        perror("VirtualProtect error:");
        exit(EXIT_FAILURE);
    }
}

void runtime_patching(void *addr, int size, int key, int off) {
    unsigned char *instruction;

    for (int offset = 0; offset < size; ++offset) {
        instruction = (unsigned char *)addr + offset;


        if (offset == off) {
            unsigned char *toPatch = instruction;
            *toPatch = key;

        //    printf("modified succesfully\n");

           // offset = size * size;

        }
      //  printf("%d ?= %d\n",offset,size);

    }
}

// int main(int argc, char *argv[]) {
//     unsigned char buf[] = "Hello world";
//     _print(buf);

//     size_t memSize = (void *)runtime_patching - (void *)_print;
    
//     changeProtect(_print, memSize);
//     runtime_patching(_print, memSize, 54);
//     _print(buf);
//     return 0;
// }
