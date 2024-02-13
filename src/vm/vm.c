#include "vm.h"
// #include "../fun/fun.h"

// #include <sys/syscall.h>
// #include <unistd.h>

int my_strlen(char const str[]) {
  const char *p = str;
  while (*p != '\0') {
    p++;
  }
  return p - str;
}

VM *create_vm(int *bytecode, int sizebytescoden, VM *prev) {

  VM *vm = (VM *)malloc(sizeof(VM));
  Register *reg = (Register *)malloc(sizeof(Register));
  vm->reg = reg;
  vm->eip = 0;
  vm->current_bc = bytecode[0];
  vm->arg1 = 0;
  vm->arg2 = 0;
  vm->binary = 0;
  vm->full_bytecode = bytecode;
  vm->next_bytecode = bytecode;
  init_reg(vm);
  funcs_fun *funcWin = (funcs_fun *)malloc(sizeof(funcs_fun));
  vm->funcWin = funcWin;
  init_WinFunc(vm);

  vm->prev = NULL;

  if (prev != NULL) {
    // VM *prev = (VM*)malloc(sizeof(VM));
    vm->prev = prev;
    vm->binary ^= 16;
  }

  //   funcs_crypto *funcCrypto = (funcs_crypto*)malloc(sizeof(funcs_crypto));

  //    vm->funcCrypto = funcCrypto;

  //   init_funcCrypto(vm);

  return vm;
}

void init_funcCrypto(VM *vm) {

  vm->funcCrypto->function_pointers[0] = rc4_init;
  vm->funcCrypto->function_pointers[1] = rc4_encrypt;
}

void init_WinFunc(VM *vm) {

  vm->funcWin->function_pointers[0] = printAAAA;
  vm->funcWin->function_pointers[1] = GetToken;
  vm->funcWin->function_pointers[2] = IsElevated;
  vm->funcWin->function_pointers[3] = where_hook;
  vm->funcWin->function_pointers[4] = HandleOn;
  vm->funcWin->function_pointers[5] = returnx2;
  vm->funcWin->function_pointers[6] = ChangeRegKey;
  vm->funcWin->function_pointers[7] = call;
}

void init_reg(VM *vm) {

  for (int i = 0; i <= Cosmos; i++) {
    vm->reg->reg[i] = 0;
  }

  vm->binarycpy = 0;
  vm->binary = 0;

  for (int i = 0; i < 50; i++) {
    vm->reg->regSTR[i] = '\0';
  }

  //     for (int i = 0; i < sizeof(vm->next_bytecode); i++)
  // {
  //     vm->next_bytecode[i]= 0x99;
  // }
}

int end_of_vm(VM *vm) {
  VM *cpy_vm = vm;
  vm->reg->reg[Quasar] = 0;

  while (cpy_vm->current_bc != 0x99) {
    cpy_vm->current_bc = cpy_vm->full_bytecode[vm->reg->reg[Quasar]];
    vm->reg->reg[Quasar]++;
  }

  return 3 % vm->reg->reg[Quasar];
}

void vm_giga_switchcase(VM *vm, int bytecode) {
  switch (bytecode) {
  case NOP:
    // vm->eip++;
    break;
  case MOVE:

    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    if (vm->arg1 <= Cosmos && vm->arg2 <= Cosmos) {
      vm->reg->reg[vm->arg1] = vm->reg->reg[vm->arg2];
      vm->eip++;
    } else {
      vm->eip += 3;
      break;
    }

    break;
  case SUB:

    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    vm->reg->reg[vm->arg1] = vm->reg->reg[vm->arg1] - vm->reg->reg[vm->arg2];

    break;

  case ADD:

    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    vm->reg->reg[vm->arg1] = vm->reg->reg[vm->arg1] + vm->reg->reg[vm->arg2];

    break;

  case JMP:
    vm->arg1 = vm->full_bytecode[vm->eip];

    vm->eip = vm->arg1;

    break;
  case JE:
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];
    vm->binarycpy = vm->binary;

    if (vm->binarycpy ==
        (vm->binary >>= 1,
         vm->binary <<=
         1)) // vérifie si le bit le plus a droite vaut 1 source ce test
             // :https://cyberchef.org/#recipe=Rotate_right(1,false)Bit_shift_left(1)
    {
      vm->eip = vm->arg1;
    }

    break;
  case JNE:
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];
    vm->binarycpy = vm->binary;

    if (vm->binarycpy != (vm->binary >>= 1, vm->binary <<= 1)) {
      vm->eip = vm->arg1;
    }
    break;
  case CMP:
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    if (vm->arg1 == vm->arg2) {
      vm->binary ^= 1;
    }

    break;
  case XOR:

    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    vm->reg->reg[vm->arg1] ^= vm->reg->reg[vm->arg2];
    vm->eip++;

    break;
  case AND:
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    vm->reg->reg[vm->arg1] &= vm->reg->reg[vm->arg2];

    break;
  case OR:
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    vm->reg->reg[vm->arg1] |= vm->reg->reg[vm->arg2];
    break;
  case SHR:
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    vm->reg->reg[vm->arg1] >>= vm->reg->reg[vm->arg2];

    break;
  case SHL:
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    vm->reg->reg[vm->arg1] <<= vm->reg->reg[vm->arg2];

    break;
  case CALL:

    // func_syscall(vm);
    break;
  case RET:
    break;
  case INC:
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    vm->reg->reg[vm->arg1] += vm->arg2;
    break;
  case DEC:
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];
    vm->reg->reg[vm->arg1] -= vm->arg2;
    break;
  case WinFunc:

    // printf("Enter in Winfunc \n");
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    // printf("Nova = %d \n", vm->reg->reg[Nova]);

    // A faire arg2 = type de retour
    switch (vm->arg2) {
    case Void:
      // printf("Good case\n");
      (*(void (*)())vm->funcWin->function_pointers[vm->arg1])(vm->reg->regSTR);
      break;
    case Int:

      vm->reg->reg[Nova] =
          (*(int (*)())vm->funcWin->function_pointers[vm->arg1])(
              vm->reg->regSTR[0], vm->reg->reg[Nebula]);
      break;

    default:
      (*(void (*)())vm->funcWin->function_pointers[vm->arg1])();
      break;
    }

    vm->eip++;
    break;

  case CryptoFunc:
    break;

  case WriteNextBC:

    // printf("hey listen \n");

    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    vm->next_bytecode[vm->arg2] = vm->arg1;
    ///     vm->reg->regSTR[vm->arg2+1] = 0x99;

    vm->eip++;
    break;

  case PSreg:
    // printf(" current regSTR %s\n",vm->reg->regSTR);
    // printf("GoodCase\n");
    vm->arg1 = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm->arg2 = vm->full_bytecode[vm->eip];

    vm->reg->regSTR[vm->arg2] = vm->arg1;
    //  vm->reg->regSTR[vm->arg2+1] = '\0';

    // printf("%s\n",vm->reg->regSTR);

    vm->eip++;

    break;

  case ResSTR:

    for (int i = 0; i < 50; i++) {
      vm->reg->regSTR[i] = '\0';
    }

    // vm->eip++;

    break;

  default:
    break;
  }
}
int is_cipher(VM *vm) {
  vm->binarycpy = vm->binary;

  // printf("binary = %d\n",vm->binary);
  //// printf(" calc = %d\n",vm->binarycpy ^ 16);

  vm->binarycpy ^= 16;
  if (vm->binarycpy > vm->binary) {
    //  printf("not ciphered\n");
    return 0;
  }

  return 1;
}
int is_first(VM *vm) {
  vm->binarycpy = vm->binary;

  // printf("binary = %d\n",vm->binary);
  //// printf(" calc = %d\n",vm->binarycpy ^ 16);

  vm->binarycpy ^= 2;
  if (vm->binarycpy > vm->binary) {
    //  printf("not ciphered\n");
    return 0;
  }

  return 1;
}

void vm_loop(VM *vm) {

  if (is_first(vm) == 1) {

    //     printf("first vm");
    //     unsigned char buf[] = "Hello world";
    //     _print(buf);

    int memSize = (void *)runtime_patching - (void *)vm_giga_switchcase;
    //   printf("%d = 2670\n",memSize);
    memSize = 2670;
    changeProtect(vm_giga_switchcase, memSize);
    // runtime_patching(vm_giga_switchcase, memSize, 85,1);
    runtime_patching(vm_giga_switchcase, memSize, 0xec, 10);
    runtime_patching(vm_giga_switchcase, memSize, 0x38, 5);
    runtime_patching(vm_giga_switchcase, memSize, 0x48, 6);
    runtime_patching(vm_giga_switchcase, memSize, 0x8d, 7);
    runtime_patching(vm_giga_switchcase, memSize, 0x6c, 8);

    printf("[*] Patching");
    //     _print(buf);
    //     return 0;
    vm->binary ^= 2;
  }

  //  printf(" is cipher = %d\n",is_cipher(vm));
  //   getchar();

  // printf("cipher = %d\n",is_cipher(vm));
  if (is_cipher(vm) == 1) {

    //       getchar();
    //   printf("Im ciphered\n");
    // vm_debug_reg(vm);

    next_vm(vm);

    //    printf("Im not ciphered\n");

    vm_debug_reg(vm);

    //       getchar();
  }

  do {

    //   printf("Loooooooooooooooooooop");

    vm->current_bc = vm->full_bytecode[vm->eip];
    vm->eip++;
    vm_giga_switchcase(vm, vm->current_bc);

    //   printf("%s",vm->reg->regSTR);
    if (vm->current_bc > END && vm->current_bc != 0x99) {
      //    printf("Instruction inconnue %x\n",vm->current_bc);
    }

    //     printf("%s",vm->reg->regSTR);

  } while (vm->current_bc != 0x99);

  //  vm_debug_reg(vm);

  next_vm(vm);

  //   getchar();

  //     printf("LAST\n\n\n");

  // vm_debug_reg(vm);

  //   getchar();
}

void next_vm(VM *vm) {
  // key

  // déchifremment

  if (is_cipher(vm) == 1) {
    // printf("IM FUCKING CIPHERED\n");
    //    vm->reg->regSTR = vm->prev->reg->regSTR;
    for (int i = 0; i < my_strlen(vm->prev->reg->regSTR); i++) {
      vm->reg->regSTR[i] = vm->prev->reg->regSTR[i];
      vm->reg->regSTR[i + 1] = '\0';
    }

    vm->next_bytecode = vm->prev->next_bytecode;
    for (int i = 0; i < my_strlen(vm->prev->reg->regSTR); i++) {
      vm->reg->regSTR[i] = vm->prev->reg->regSTR[i];
    }
  }

  // printf("aaa\n");
  vm->reg->reg[Orion] = 210;
  vm->reg->reg[Celestial] = 256;
  //  vm->reg->regSTR[0] ='h';
  //  vm->reg->regSTR[1] ='b';
  // char key[] ="My_B1G_S3CUR3_K3Y!";
  // for (int i = 0; i < strlen(key); i++)
  // {
  //     vm->reg->regSTR[i] = key[i];
  // }

  //     vm->next_bytecode[0] = 14;
  // printf("\n");

  // printf("I cipher/encipher with the key %s\n",vm->reg->regSTR);

  // vm_debug_reg(vm);

  rc4_init(vm->reg->regSTR, my_strlen(vm->reg->regSTR), vm->reg->S,
           vm->reg->reg[Celestial]);
  // printf("crash ?");
  rc4_encrypt(vm->next_bytecode, vm->reg->reg[Orion], vm->reg->S,
              vm->reg->reg[Celestial]);

  // printf("crash ?");

  for (int i = 0; i < vm->reg->reg[Orion]; i++) {
    //  printf("%d,", vm->next_bytecode[i]);
  }

  // printf("\n");
  //     rc4_init(vm->reg->regSTR, my_strlen(vm->reg->regSTR),
  //     vm->reg->S,vm->reg->reg[Celestial]); rc4_encrypt(vm->next_bytecode,
  //     vm->reg->reg[Orion], vm->reg->S,vm->reg->reg[Celestial]);

  // for (int i = 0; i < vm->reg->reg[Orion]; i++) {
  //     printf("%d,", vm->next_bytecode[i]);
  // }

  //   printf("\n");

  // getchar();

  // rc4_init(vm->reg->regSTR, my_strlen(vm->reg->regSTR),
  // vm->reg->S,vm->reg->reg[Celestial]); rc4_encrypt(vm->next_bytecode,
  // vm->reg->reg[Orion], vm->reg->S,vm->reg->reg[Celestial]);

  // for (int i = 0; i < vm->reg->reg[Orion]; i++) {
  //     printf("%d ", vm->next_bytecode[i]);
  // }

  //  printf("\n");
}

void vm_free(VM *vm) { free(vm); }

void reg_free(Register *reg) { free(reg); }

void Func_free(funcs_fun *fun) { free(fun); }

void vm_debug_reg(VM *vm) {
  printf("Alpha :  %d \n", vm->reg->reg[Alpha]);
  printf("Nebula :  %d \n", vm->reg->reg[Nebula]);
  printf("Nova :  %d \n", vm->reg->reg[Nova]);
  printf("Orion :  %d \n", vm->reg->reg[Orion]);
  printf("Quasar :  %d \n", vm->reg->reg[Quasar]);
  printf("Celestial :  %d \n", vm->reg->reg[Celestial]);
  printf("Specter :  %d \n", vm->reg->reg[Specter]);
  printf("Aether :  %d \n", vm->reg->reg[Aether]);
  printf("Eclipse :  %d \n", vm->reg->reg[Eclipse]);
  printf("Cosmos :  %d \n", vm->reg->reg[Cosmos]);
  printf("-------------------------------------------\n");
  printf("arg1 : %d \n", vm->arg1);
  printf("arg2 : %d \n", vm->arg2);
  printf("-------------------------------------------\n");

  int b[10], bc[10], n, j;

  n = vm->binary;
  for (j = 0; n > 0; j++) {
    b[j] = n % 2;
    n = n / 2;
  }

  printf("binary : ");
  for (j = j - 1; j >= 0; j--) {
    printf("%d", b[j]);
  }
  printf("\n");

  n = vm->binarycpy;
  for (j = 0; n > 0; j++) {
    bc[j] = n % 2;
    n = n / 2;
  }

  printf("binarycpy : ");
  for (j = j - 1; j >= 0; j--) {
    printf("%d", bc[j]);
  }
  printf("\n");

  printf("-------------------------------------------\n");

  printf("full bytede :  \n");
  int i = 0;
  do {
    printf("0x%x-", vm->full_bytecode[i]);
    i++;
  } while (vm->full_bytecode[i] != 0x99);
  printf("\n");

  printf("Next bytede :  \n");
  i = 0;
  do {
    printf("0x%x-", vm->next_bytecode[i]);
    i++;
  } while (vm->next_bytecode[i] != 0x99);
  printf("\n");

  printf("current_bc : 0x%x \n", vm->current_bc);
  printf("eip : %d \n", vm->eip);
  printf("-------------------------------------------\n");
}
