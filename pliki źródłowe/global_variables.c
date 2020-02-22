#include "global_variables.h"

HANDLE hStdout;

char space_declaration_codes[2][3] = { "DC", "DS" };
char* arithmetic_operations_codes[10] = { "A", "AR", "S", "SR", "M", "MR", "D", "DR", "C", "CR" };
char* jump_operations_codes[4] = { "J", "JP", "JN", "JZ" };
char* transmission_operations_codes[4] = { "L", "LR", "ST", "LA" };
int reg[20];
int old_reg[20];
int program_status_register;
int old_program_status_register;

int declaration_lines = 0;
int order_lines = 0;