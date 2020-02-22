#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<windows.h>

#include "order_functions.h"
#include "global_variables.h"
#include "output_functions.h"
#include "check_functions.h"
#include "parsing_and_loading_functions.h"

#define DEBUG printf("%s\n", "test");


int main(int argc, char* argv[])
{
	//setup of the ouput console properties
	int i = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	char name[MAX_LENGTH];
	if (argc == 1)
	{
		print_filename_missing_message();
		scanf("%s", name);
	}
	else strcpy(name, argv[1]);
	char path[] = "..\\programy\\";
	char* filename = malloc(strlen(name) + strlen(path) + 1);
	strcpy(filename, path);
	strcat(filename, name);

	int file_length = read_source_file_length(filename);
	//initialize space for the content of the input file and load it

	char** pseudocode = malloc(file_length * sizeof(char*));
	for (i = 0; i < file_length; i++) pseudocode[i] = malloc(MAX_LENGTH * sizeof(char));
	load_pseudocode(filename, file_length, pseudocode);
	print_starting_message(pseudocode, file_length);

	//read how many 4 bytes variables are initialized at the start of the program
	//and allocate required space for them 
	int required_space = read_required_space(pseudocode, file_length);
	int* program_memory = malloc(required_space * sizeof(int));

	//follow declaration instructions at the beginning of the program
	struct Variable* variables = malloc(declaration_lines * sizeof(struct Variable));
	set_default_variable_values(variables, declaration_lines);
	allocate_program_memory(filename, variables, program_memory);

	//parse orders and store them in a table of structs 
	struct Order* orders = malloc(order_lines * sizeof(struct Order));

	set_default_order_values(orders, order_lines);
	load_orders(pseudocode, file_length, orders);

	//execute orders stored in previously filled table of structs
	execute_orders(orders, file_length, variables, program_memory, pseudocode);
	print_program_final_state(orders, file_length, variables, declaration_lines, pseudocode);

	free(filename);
	free(pseudocode);
	free(program_memory);
	free(variables);
	free(orders);
	return 0;
}




