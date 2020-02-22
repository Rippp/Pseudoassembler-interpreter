#ifndef CHECK_FUNCTIONS_H
#define CHECK_FUNCTIONS_H
#include<stdbool.h>

bool check_if_space_declaration(char code_line[]);
bool check_if_arithmetic_operation_code(char chars[]);
bool check_if_jump_operation_code(char chars[]);
bool check_if_transmission_operation_code(char chars[]);
int check_if_brackets(char arg2[]);

#endif