#ifndef FUN_H
#define FUN_H
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>

void where_hook();
int IsElevated();
int returnx2(char *fmt,...);
char* HandleOn(const char* name);
void GetToken(const char PrivName[]);
void printAAAA();
void ChangeRegKey(char ap[]);
void call(const char cmd[]);


typedef struct 
{
    void *function_pointers[8]; 
} funcs_fun;

#endif

// fun.h
// typedef struct 
// {
//     void (*pprintAAAA)(); // Déclaration du pointeur de fonction pour printAAAA
// } funcs_fun;
