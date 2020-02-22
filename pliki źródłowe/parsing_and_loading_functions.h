#ifndef PARSING_AND_LOADING_FUNCTIONS_H
#define PARSING_AND_LOADING_FUNCTIONS_H
#include<windows.h>

void set_default_order_values(struct Order orders[], int n);
void set_default_variable_values(struct Variable variables[], int n);
int read_source_file_length(const char filename[]);
int read_required_space(char** pseudocode, int file_length);
void load_pseudocode(const char filename[], int file_length, char** pseudocode);
void allocate_program_memory(const char filename[], struct Variable variables[], int program_memory[]);
void parse_order(char code_line[], int order_number, struct Order orders[]);
void load_orders(char** pseudocode, int file_length, struct Order orders[]);
int parse_address(char arg2[]);
COORD get_desktop_resolution(void);

#endif