#ifndef ORDERS_H
#define ORDERS_H
#include "global_variables.h"

void execute_orders(struct Order orders[], int file_length, struct Variable variables[], int program_memory[], char** pseudocode);

void execute_AR(char arg1[], char arg2[]);
void execute_SR(char arg1[], char arg2[]);
void execute_MR(char arg1[], char arg2[]);
void execute_DR(char arg1[], char arg2[]);
void execute_CR(char arg1[], char arg2[]);
void execute_LR(char arg1[], char arg2[]);

void execute_A(char arg1[], char arg2[], struct Variable variables[], int program_memory[]);
void execute_S(char arg1[], char arg2[], struct Variable variables[], int program_memory[]);
void execute_M(char arg1[], char arg2[], struct Variable variables[], int program_memory[]);
void execute_D(char arg1[], char arg2[], struct Variable variables[], int program_memory[]);
void execute_C(char arg1[], char arg2[], struct Variable variables[], int program_memory[]);
void execute_L(char arg1[], char arg2[], struct Variable variables[], int program_memory[]);
void execute_LA(char arg1[], char arg2[], struct Variable variables[], int program_memory[]);

int execute_J(char arg1[], struct Order orders[], int file_length);
void execute_ST(char arg1[], char arg2[], struct Variable variables[], int program_memory[]);
void update_program_status_register(int result);

#endif