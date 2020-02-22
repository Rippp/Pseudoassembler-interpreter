#pragma warning(disable:4996)
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "check_functions.h"
#include "global_variables.h"

bool check_if_space_declaration(char code_line[])
{
	char chars[3] = { "AA" };
	int i = 0;

	//omitting the white characters at the beginning
	while ((int)code_line[i] < 33) i++;
	//omitting the first word 
	while ((int)code_line[i] >= 33) i++;
	//omitting the white characters between the first and the second word
	while ((int)code_line[i] < 33) i++;

	chars[0] = code_line[i];
	chars[1] = code_line[i + 1];

	if (strcmp(space_declaration_codes[0], chars) == 0 || strcmp(space_declaration_codes[1], chars) == 0)
		return true;

	return false;
}

bool check_if_arithmetic_operation_code(char chars[])
{
	int i = 0;
	for (i; i < 10; i++) if (strcmp(chars, arithmetic_operations_codes[i]) == 0) return true;

	return false;
}

bool check_if_jump_operation_code(char chars[])
{
	int i = 0;
	for (i; i < 4; i++) if (strcmp(chars, jump_operations_codes[i]) == 0) return true;

	return false;
}

bool check_if_transmission_operation_code(char chars[])
{
	int i = 0;
	for (i; i < 4; i++) if (strcmp(chars, transmission_operations_codes[i]) == 0) return true;

	return false;
}

int check_if_brackets(char arg2[])
{
	int i = 0;
	while (arg2[i] != '\0')
	{
		if (arg2[i] == '(')
		{
			char number[4] = { "000" };
			i++;
			while ((int)arg2[i] >= 48) i++;
			i--;
			int k = 2;
			while ((int)arg2[i] >= 48)
			{
				number[k] = arg2[i];
				k--; i--;
			}

			arg2[i] = '\0';
			int optional_register_number;
			sscanf(number, "%d", &optional_register_number);
			return optional_register_number;
		}
		i++;
	}

	return 0;
}