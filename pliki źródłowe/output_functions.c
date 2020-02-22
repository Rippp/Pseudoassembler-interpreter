#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<windows.h>
#include "global_variables.h"

void print_program_memory(struct Variable variables[], int declaration_lines)
{
	int i = 0, j = 0;
	for (i; i < declaration_lines; i++)
	{	
		if(variables[i].size == 1)
			printf("%s \t %10d\n", variables[i].label, *(variables[i].program_memory_pointer));
		else
			for (j = 0; j < variables[i].size; j++) 
				printf("%s[%d] \t %10d\n", variables[i].label, j, *(variables[i].program_memory_pointer + j));
	}
}


void print_registers_values(void)
{
	int i = 0;
	printf("\n%s\n", "Registers values after executing an order:");

	printf(".");
	for (i = 0; i < 68; i++) printf("_");
	printf(".");
	printf("\n");

	for (i = 0; i < 7; i++) printf("|   R%d   |", i);
	printf("\n");
	for (i = 0; i < 7; i++)
	{
		if (reg[i] == old_reg[i]) printf("|%08d|", reg[i]);
		else
		{
			SetConsoleTextAttribute(hStdout, 11);
			printf("|%08d|", reg[i]);
			SetConsoleTextAttribute(hStdout, 15);
		}
	}
	printf("\n");

	printf(".");
	for (i = 0; i < 68; i++) printf("_");
	printf(".");
	printf("\n");

	for (i = 7; i < 10; i++) printf("|   R%d   |", i);
	for (i = 10; i < 14; i++) printf("|   R%d  |", i);
	printf("\n");
	for (i = 7; i < 14; i++)
	{
		if (reg[i] == old_reg[i]) printf("|%08d|", reg[i]);
		else
		{
			SetConsoleTextAttribute(hStdout, 11);
			printf("|%08d|", reg[i]);
			SetConsoleTextAttribute(hStdout, 15);
		}
	}
	printf("\n\nProgram_status_register: ");

	if (old_program_status_register != program_status_register) SetConsoleTextAttribute(hStdout, 11);
	if (program_status_register == 0) printf("00\n");
	else if (program_status_register == 1) printf("01\n");
	else if (program_status_register == 2) printf("10\n");
	else if (program_status_register == 3) printf("11\n");
	SetConsoleTextAttribute(hStdout, 15);
}

void print_starting_message(char** pseudocode, int file_length)
{
	printf("%s\n\n", "This program executes given pseudoassembler code and after\n"
		"every command it prints out the value of registers. \n\n"
		"To execute the next command please press f as in forward.\n"
		"To immediately stop the execution of the program press s as in stop.\n\n"
		"Press f to start the execution, s to quit or i for immediate execution till the end\n\n"
		"Here is the code loaded to the interpreter");

	int i = 0;
	for (i; i < file_length; i++) printf("%s", pseudocode[i]);
	printf("\n");
}

void print_order_information(char** pseudocode, int file_length, int current_line)
{
	int i = 0;
	for (i; i < file_length; i++)
	{
		int j = 0;
		while (pseudocode[i][j] != '\n') j++;
		while (j < MAX_LENGTH) { pseudocode[i][j] = '\0'; j++; }
	}
	if (current_line < file_length) {
		printf("Now executing: ");
		SetConsoleTextAttribute(hStdout, 11);
		printf("%s\n", pseudocode[declaration_lines + current_line]);
		SetConsoleTextAttribute(hStdout, 15);
	}

	for (i = 0; i < file_length; i++)
	{
		if (i == (declaration_lines + current_line))
		{
			SetConsoleTextAttribute(hStdout, 11);
			printf("%s\n", pseudocode[i]);
			SetConsoleTextAttribute(hStdout, 15);
		}
		else printf("%s\n", pseudocode[i]);
	}
	printf("\n");
}

void print_file_error(void)
{
	printf("%s\n", "An error occurred while opening a file.");
	char c = getchar();
	c = getchar();
	exit(1);
}

void print_filename_missing_message(void) {
	printf("Please type in the name of the pseudoassembler file.\n"
		"The file must be in the 'programy' directory\n"
		"For example 'example.txt' (without the quotes)\n"
		"\nHere is the list of available pseudoassembler files:\n");

	system("dir ..\\programy /b");
}

void print_program_final_state(struct Order orders[], int file_length, struct Variable variables[], int declaration_lines, char** pseudocode) {
	system("cls");
	print_order_information(pseudocode, file_length, file_length);
	print_registers_values();
	print_program_memory(variables, declaration_lines);

	char c = getchar();
	c = getchar();
}