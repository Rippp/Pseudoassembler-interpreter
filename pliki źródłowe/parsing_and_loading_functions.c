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


void set_default_order_values(struct Order orders[], int n)
{
	int i = 0;
	for (i; i < n; i++)
	{
		int j = 0;
		for (j; j < MAX_LENGTH; j++) orders[i].label[j] = '\0';
		for (j = 0; j < 10; j++) orders[i].order[j] = '\0';
		for (j = 0; j < 35; j++)
		{
			orders[i].arg1[j] = '\0';
			orders[i].arg2[j] = '\0';
		}
	}
}

void set_default_variable_values(struct Variable variables[], int n)
{
	int i = 0;
	for (i; i < n; i++)
	{
		int j = 0;
		for (j; j < MAX_LENGTH; j++) variables[i].label[j] = '\0';
		variables[i].program_memory_pointer = NULL;
		variables[i].size = 1;
	}
}

int read_source_file_length(const char filename[])
{
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) print_file_error();


	int file_length = 0;
	char trash_buffor[MAX_LENGTH];
	while (fgets(trash_buffor, MAX_LENGTH, fp) != NULL) file_length++;

	fclose(fp);
	return file_length;
}

int read_required_space(char** pseudocode, int file_length)
{
	int required_space = 0;
	int i = 0;
	for (i; i < file_length; i++)
	{

		if (check_if_space_declaration(pseudocode[i]))
		{
			declaration_lines++;

			int j = 0;
			//omitting white characters at the beginning
			while ((int)pseudocode[i][j] < 33) j++;
			//omitting the first word
			while ((int)pseudocode[i][j] >= 33) j++;
			//omitting white characters between first and second word
			while ((int)pseudocode[i][j] < 33) j++;
			//omitting the second word
			while ((int)pseudocode[i][j] >= 33) j++;
			//omitting white characters between second and third word
			while ((int)pseudocode[i][j] < 33) j++;

			if (pseudocode[i][j] == 'I') required_space++;

			else
			{
				//int this case there is an array declaration
				char number[10] = { "000000000" };
				int k = 8;
				while ((int)pseudocode[i][j] != 42) j++;
				j--;
				while ((int)pseudocode[i][j] >= 48)
				{
					number[k] = pseudocode[i][j];
					k--;
					j--;
				}

				int table_size;
				sscanf(number, "%d", &table_size);
				required_space += table_size;
			}
		}
		else
		{
			order_lines++;
		}
	}

	return required_space;
}

void load_pseudocode(const char filename[], int file_length, char** pseudocode)
{
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) print_file_error();

	int i = 0, j = 0;
	for (i; i < file_length; i++)
		for (j; j < MAX_LENGTH; j++)
			pseudocode[i][j] = '\0';

	for (i = 0; i < file_length; i++) fgets(pseudocode[i], MAX_LENGTH, fp);

	fclose(fp);
	return;
}

void allocate_program_memory(const char filename[], struct Variable variables[], int program_memory[])
{
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL) print_file_error();

	char code[MAX_LENGTH];
	char size[MAX_LENGTH];
	char initial_value[MAX_LENGTH];

	int i = 0, shift = 0;
	for (i; i < declaration_lines; i++)
	{
		//loading the label
		fscanf(fp, "%s", variables[i].label);
		//loading the declaration order
		fscanf(fp, "%s", code);
		fscanf(fp, "%s", size);

		//if code is DC then we load the initial value
		if (strcmp(code, space_declaration_codes[0]) == 0)
			fscanf(fp, "%s", initial_value);

		//memory initialization if it is a single 4byte integer
		if (size[0] == 'I')
		{
			variables[i].program_memory_pointer = (program_memory + shift);
			variables[i].size = 1;
		}
		//memory initialization if it is an array of integers
		else
		{
			int j = 0, k = 8;
			char number[10] = { "000000000" };
			while ((int)size[j] != 42) j++;

			j--;
			while (j >= 0) {
				number[k] = size[j];
				k--;
				j--;
			}

			int table_size;
			sscanf(number, "%d", &table_size);

			variables[i].program_memory_pointer = (program_memory + shift);
			variables[i].size = table_size;
		}

		//setting the initial value
		if (strcmp(code, space_declaration_codes[0]) == 0)
		{
			char number[12] = { "00000000000" };
			int j = 1, k = 10;

			if (initial_value[j] == '-')
			{
				number[0] = '-';
				j++;
			}
			while ((int)initial_value[j] >= 43) j++;

			j--;
			while (j > 0 && (int)initial_value[j] >= 48)
			{
				number[k] = initial_value[j];
				k--; j--;
			}

			int temp;
			sscanf(number, "%d", &temp);

			j = 0;
			for (j; j < variables[i].size; j++) *(variables[i].program_memory_pointer + j) = temp;
		}

		shift += variables[i].size;
	}
}

void parse_order(char code_line[], int order_number, struct Order orders[])
{
	int i = 0, how_many_letters = 0;
	char chars[30];
	for (i; i < 30; i++) chars[i] = '\0';
	i = 0;

	while ((int)code_line[i] < 33) i++;
	while ((int)code_line[i] >= 33)
	{
		i++;
		how_many_letters++;
	}

	memcpy(chars, code_line + i - how_many_letters, how_many_letters);

	bool check_if_not_label = check_if_arithmetic_operation_code(chars);
	check_if_not_label |= check_if_jump_operation_code(chars);
	check_if_not_label |= check_if_transmission_operation_code(chars);

	if (check_if_not_label == false)
	{
		strcpy(orders[order_number].label, chars);
		while ((int)code_line[i] < 33) i++;
		how_many_letters = 0;
		while ((int)code_line[i] >= 33)
		{
			i++;
			how_many_letters++;
		}
		memcpy(chars, code_line + i - how_many_letters, how_many_letters);
		chars[how_many_letters] = '\0';
	}

	strcpy(orders[order_number].order, chars);

	while ((int)code_line[i] < 33) i++;
	how_many_letters = 0;
	while ((int)code_line[i] >= 48)
	{
		i++;
		how_many_letters++;
	}
	memcpy(chars, code_line + i - how_many_letters, how_many_letters);
	chars[how_many_letters] = '\0';
	strcpy(orders[order_number].arg1, chars);

	if (code_line[i] == ',')
	{
		i++;
		while ((int)code_line[i] < 33) i++;
		how_many_letters = 0;
		while ((int)code_line[i] >= 40)
		{
			i++;
			how_many_letters++;
		}
		memcpy(chars, code_line + i - how_many_letters, how_many_letters);
		chars[how_many_letters] = '\0';
		strcpy(orders[order_number].arg2, chars);
	}
}

void load_orders(char** pseudocode, int file_length, struct Order orders[])
{
	int i = declaration_lines, order_number = 0;
	for (i; i < file_length; i++)
	{
		parse_order(pseudocode[i], order_number, orders);
		order_number++;
	}
}

COORD get_desktop_resolution(void)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);

	COORD ret;
	ret.X = desktop.right;
	ret.Y = desktop.bottom;

	return ret;
}

int parse_address(char arg2[])
{
	char number[10] = { "000000000" };
	int address;
	int k = 8;
	int i = 0;
	while (arg2[i] != '\0') i++;
	i--;
	while (i >= 0)
	{
		number[k] = arg2[i];
		k--; i--;
	}

	sscanf(number, "%d", &address);
	return address;
}