#ifndef OUTPUT_H
#define OUTPUT_H
#include "global_variables.h"
void print_order_information(char** pseudocode, int file_length, int current_line);
void print_starting_message(char** pseudocode, int file_length);
void print_file_error(void);
void print_registers_values(void);
void print_program_memory(struct Variable variables[], int declaration_lines);
void print_filename_missing_message(void);
void print_program_final_state(struct Order orders[], int file_length, struct Variable variables[], int declaration_lines, char** pseudocode);
#endif