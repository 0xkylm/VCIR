#ifndef VM_H
#define VM_H
#include "../fun/fun.h"
#include "crypto.h"

#include "../fun/smc.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  NOP = 1,
  MOVE,
  SUB,
  ADD,
  JMP,
  JE,
  JNE,
  AND,
  OR,
  NOT,
  XOR,
  SHR,
  SHL,
  CALL,
  RET,
  INC,
  DEC,
  WinFunc,
  CMP,
  PSreg,
  ResSTR,
  CryptoFunc,
  WriteNextBC,
  END
} opcode;

// typedef struct{ /*Seul et unique utilisation de chatgpt pour les nom j'ai pas
// d'immagination :'( */
//     int Alpha;
//     int Nebula;
//     int Nova;
//     int Orion;
//     int Quasar;
//     int Celestial;
//     int Specter;
//     int Aether;
//     int Eclipse;
//     int Cosmos;
// }Register;

// int len_regstr1 = 50;
typedef struct {
  int reg[9];
  char regSTR[50];
  unsigned char S[256];
} Register;

typedef enum { /*Seul et unique utilisation de chatgpt pour les nom j'ai pas
                  d'immagination :'( */
               Alpha,
               Nebula,
               Nova,
               Orion,
               Quasar,
               Celestial,
               Specter,
               Aether,
               Eclipse,
               Cosmos
} RegisterEnum;

typedef enum { Void, Bool, Int, Char } Types;

typedef struct VM VM;

typedef struct VM {
  int eip;
  int current_bc;
  int arg1;
  int arg2;
  int binary;
  int binarycpy;

  int *full_bytecode;
  int *next_bytecode; // ou liste chainé a voir; bon bah choix fait;

  Register *reg;

  funcs_fun *funcWin;

  funcs_crypto *funcCrypto;

  // VM *next;
  VM *prev;

} VM;

/*VM func*/
VM *create_vm(int *bytecode, int sizebytescode, VM *prev;);
int end_of_vm(VM *vm);
int func_syscall(VM *vm);
int is_cipher(VM *vm);
int is_first(VM *vm);
void init_reg(VM *vm);
void init_WinFunc(VM *vm);
void init_funcCrypto(VM *vm);
void vm_free(VM *vm);
void reg_free(Register *reg);
void Func_free(funcs_fun *fun);
void vm_loop(VM *vm);
void next_vm(VM *vm);

//----------------Debug-------------------//
void vm_debug_instr(VM *vm, int eip);
void vm_debug_full_debug(VM *vm);
void vm_debug_stack(VM *vm);
void vm_debug_reg(VM *vm);

void vm_giga_switchcase(VM *vm, int bytecode);

/*Flex func*/

int my_strlen(char const str[]);

#endif
