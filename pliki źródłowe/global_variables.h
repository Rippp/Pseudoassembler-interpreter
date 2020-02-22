#ifndef GLOBALS_H
#define GLOBALS_H
#define MAX_LENGTH 100
#include<windows.h>

extern HANDLE hStdout;

struct Order
{
	char label[MAX_LENGTH];
	char order[10];
	char arg1[35];
	char arg2[35];
};

struct Variable
{
	char label[MAX_LENGTH];
	int* program_memory_pointer;
	int size;
};

extern char space_declaration_codes[2][3];
extern char* arithmetic_operations_codes[10];
extern char* jump_operations_codes[4];
extern char* transmission_operations_codes[4];
extern int reg[20];
extern int old_reg[20];
extern int program_status_register;
extern int old_program_status_register;

extern int declaration_lines;
extern int order_lines;

#endif