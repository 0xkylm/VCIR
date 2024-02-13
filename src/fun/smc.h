#ifndef SMC_H
#define SMC_H

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <windows.h>

#include "fun.h"

void _print(unsigned char txt[]);

void changeProtect(void *addr, int memSize);

void runtime_patching(void *addr, int size, int key,int off);

#endif
