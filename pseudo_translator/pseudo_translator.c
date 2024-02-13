#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int shellcode[100];

int parse_PSreg(char *arg1, int i) {

  for (int j = 0; j < strlen(arg1) * 3 - 1; j++) {

    printf("arg1[%d] = %c\n", j, arg1[j]);
    shellcode[i] = PSreg;
    printf("write %d\t?= %c ", arg1[j], arg1[j]);

    i++;
    shellcode[i] = arg1[j];
    i++;
    shellcode[i] = j;
    i++;
  }
}

int parse_argu(char *arg1, char *arg2, int i) {
  printf("arg1: %s ::index ::%d\n", arg1, i);

  i++;

  printf("arg2: %s ::index ::%d\n", arg2, i);

  // shellcode[i] = arg1;
  if (arg1[0] = '0' && arg1[1] == 'x' && atoi(&arg1[2]) < 255) {
    shellcode[i] = atoi(&arg1[2]);
    printf("if arg1 = %d\n", atoi(&arg1[2]));

  } else {
    getchar();
    printf("strlen = %d\n", strlen(&arg1));
    for (int w = 0; w < strlen(&arg1) - 2; w++) {

      printf("arg1[%d] = %c\n", w, arg1[w - 1]);
      shellcode[i] = 888;
      i++;
    }
    printf("else arg1 = %s\n", arg1);
    // shellcode[i] = arg1;
  }
  i++;
  // i++;
  // printf("i = %d\n", i);
  if (arg2[0] = '0' && arg2[1] == 'x' && atoi(&arg2[2]) < 255) {
    shellcode[i] = atoi(&arg2[2]);
    printf("if arg2 = %d\n", atoi(&arg2[2]));
    shellcode[i] = atoi(&arg2[2]);
  } else {
    printf("else arg2 = %s\n", arg2);
  }
  // getchar();
  return i;
} // shellcode[i] = arg2;

void parse_file(FILE *file) {
  char arg1[100];
  char arg2[100];

  char word[100];
  int i = 0;
deb:
  while (fscanf(file, "%s", word) != EOF) {
    printf("%s\n", word);
    printf("index ::%d\n", i++);
    int a = 1;

    a = memcmp(word, "NOP", 3);
    if (a == 0) {
      printf("NOP detected opcode:: %d\n", NOP);
      shellcode[i] = NOP;
    }
    a = memcmp(word, "MOVE", 4);
    if (a == 0) {
      printf("MOVE detected opcode:: %d\n", MOVE);
      shellcode[i] = MOVE;
      goto READ_ARGS;
    }
    a = memcmp(word, "SUB", 3);
    if (a == 0) {
      printf("SUB detected opcode:: %d\n", SUB);
      shellcode[i] = SUB;
      goto READ_ARGS;
    }
    a = memcmp(word, "ADD", 3);
    if (a == 0) {
      printf("ADD detected opcode:: %d\n", ADD);
      shellcode[i] = ADD;
      goto READ_ARGS;
    }
    a = memcmp(word, "JMP", 3);
    if (a == 0) {
      printf("JMP detected opcode:: %d\n", JMP);
      shellcode[i] = JMP;
      goto READ_ARGS;
    }
    a = memcmp(word, "JE", 2);
    if (a == 0) {
      printf("JE detected opcode:: %d\n", JE);
      shellcode[i] = JE;
      goto READ_ARGS;
    }
    a = memcmp(word, "JNE", 3);
    if (a == 0) {
      printf("JNE detected opcode:: %d\n", JNE);
      shellcode[i] = JNE;
      goto READ_ARGS;
    }
    a = memcmp(word, "AND", 3);
    if (a == 0) {
      printf("AND detected opcode:: %d\n", AND);
      shellcode[i] = AND;
      goto READ_ARGS;
    }
    a = memcmp(word, "OR", 2);
    if (a == 0) {
      printf("OR detected opcode:: %d\n", OR);
      shellcode[i] = OR;
      goto READ_ARGS;
    }
    a = memcmp(word, "NOT", 3);
    if (a == 0) {
      printf("NOT detected opcode:: %d\n", NOT);
      shellcode[i] = NOT;
      goto READ_ARGS;
    }
    a = memcmp(word, "XOR", 3);
    if (a == 0) {
      printf("XOR detected opcode:: %d\n", XOR);
      shellcode[i] = XOR;
      goto READ_ARGS;
    }
    a = memcmp(word, "SHR", 3);
    if (a == 0) {
      printf("SHR detected opcode:: %d\n", SHR);
      shellcode[i] = SHR;
      goto READ_ARGS;
    }
    a = memcmp(word, "SHL", 3);
    if (a == 0) {
      printf("SHL detected opcode:: %d\n", SHL);
      shellcode[i] = SHL;
      goto READ_ARGS;
    }
    a = memcmp(word, "CALL", 4);
    if (a == 0) {
      printf("CALL detected opcode:: %d\n", CALL);
      shellcode[i] = CALL;
      goto READ_ARGS;
    }
    a = memcmp(word, "RET", 3);
    if (a == 0) {
      printf("RET detected opcode:: %d\n", RET);
      shellcode[i] = RET;
    }
    a = memcmp(word, "INC", 3);
    if (a == 0) {
      printf("INC detected opcode:: %d\n", INC);
      shellcode[i] = INC;
      goto READ_ARGS;
    }
    a = memcmp(word, "DEC", 3);
    if (a == 0) {
      printf("DEC detected opcode:: %d\n", DEC);
      shellcode[i] = DEC;
      goto READ_ARGS;
    }
    a = memcmp(word, "WinFunc", 7);
    if (a == 0) {
      printf("WinFunc detected opcode:: %d\n", WinFunc);
      shellcode[i] = WinFunc;
      goto READ_ARGS;
    }
    a = memcmp(word, "CMP", 3);
    if (a == 0) {
      printf("CMP detected opcode:: %d\n", CMP);
      shellcode[i] = CMP;
      goto READ_ARGS;
    }
    a = memcmp(word, "PSreg", 5);
    if (a == 0) {
      printf("PSreg detected opcode:: %d\n", PSreg);
      shellcode[i] = PSreg;
      goto READ_ARGS_2;
    }
    a = memcmp(word, "ResSTR", 6);
    if (a == 0) {
      printf("ResSTR detected opcode:: %d\n", ResSTR);
      shellcode[i] = ResSTR;
      goto READ_ARGS;
    }
    a = memcmp(word, "WriteNextBC", 11);
    if (a == 0) {
      printf("WriteNextBC detected opcode:: %d\n", WriteNextBC);
      shellcode[i] = WriteNextBC;
      goto READ_ARGS;
    }
    a = memcmp(word, "END", 3);
    if (a == 0) {
      printf("END detected opcode:: %d\n", END);
      shellcode[i] = END;
    }
    a = memcmp(word, "#", 1);
    if (a == 0) {
      printf("Comment detected\n");
    }
  }
  shellcode[i++] = 0x99;
  printf("shellcode ::\"");
  for (int j = 0; j < i; j++) {
    if (j == i - 1) {
      printf("%d\"", shellcode[j]);
    } else
      printf("%d,", shellcode[j]);
  }

  return;

READ_ARGS:
  fscanf(file, "%s", arg1);
  fscanf(file, "%s", arg2);
  printf("arg1: %s\narg2: %s\n", arg1, arg2);
  i = parse_argu(arg1, arg2, i);
  printf("I have parsed the arguments Normal Aergu\n");
  goto deb;
READ_ARGS_2:
  fscanf(file, "%s", arg1);
  printf("arg1: %s\n", arg1);
  i = parse_PSreg(arg1, i);
  printf("I have parsed the arguments GotO psREG\n");
  goto deb;
}

FILE *fptr;

int main(int argc, char const *argv[]) {

  fptr = fopen(argv[1], "r");

  parse_file(fptr);

  return 0;
}
