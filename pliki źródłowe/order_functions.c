#pragma warning(disable:4996)
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "order_functions.h"
#include "global_variables.h"
#include "output_functions.h"
#include "check_functions.h"

void execute_orders(struct Order orders[], int file_length, struct Variable variables[], int program_memory[], char** pseudocode)
{
	int i = 0;
	char c = 'a';
	for (i; i < file_length - declaration_lines; i++)
	{
		int j = 0;
		for (j; j < 20; j++) old_reg[j] = reg[j];
		old_program_status_register = program_status_register;

		if (c != 'i')
		{
			c = getchar();
			while (c != 's' && c != 'i' && c != 'f') c = getchar();
			if (c == 's') exit(0);

			system("cls");
		}
		if (c != 'i') print_order_information(pseudocode, file_length, i);
		if (strcmp(orders[i].order, "AR") == 0) execute_AR(orders[i].arg1, orders[i].arg2);
		else if (strcmp(orders[i].order, "SR") == 0) execute_SR(orders[i].arg1, orders[i].arg2);
		else if (strcmp(orders[i].order, "MR") == 0) execute_MR(orders[i].arg1, orders[i].arg2);
		else if (strcmp(orders[i].order, "DR") == 0) execute_DR(orders[i].arg1, orders[i].arg2);
		else if (strcmp(orders[i].order, "CR") == 0) execute_CR(orders[i].arg1, orders[i].arg2);
		else if (strcmp(orders[i].order, "LR") == 0) execute_LR(orders[i].arg1, orders[i].arg2);

		else if (strcmp(orders[i].order, "A") == 0) execute_A(orders[i].arg1, orders[i].arg2, variables, program_memory);
		else if (strcmp(orders[i].order, "S") == 0) execute_S(orders[i].arg1, orders[i].arg2, variables, program_memory);
		else if (strcmp(orders[i].order, "M") == 0) execute_M(orders[i].arg1, orders[i].arg2, variables, program_memory);
		else if (strcmp(orders[i].order, "D") == 0) execute_D(orders[i].arg1, orders[i].arg2, variables, program_memory);
		else if (strcmp(orders[i].order, "C") == 0) execute_C(orders[i].arg1, orders[i].arg2, variables, program_memory);

		else if (strcmp(orders[i].order, "L") == 0) execute_L(orders[i].arg1, orders[i].arg2, variables, program_memory);
		else if (strcmp(orders[i].order, "LA") == 0) execute_LA(orders[i].arg1, orders[i].arg2, variables, program_memory);
		else if (strcmp(orders[i].order, "ST") == 0) execute_ST(orders[i].arg1, orders[i].arg2, variables, program_memory);

		else if (strcmp(orders[i].order, "J") == 0) { i = execute_J(orders[i].arg1, orders, file_length); goto the_end; }
		else if (strcmp(orders[i].order, "JP") == 0 && program_status_register == 1) { i = execute_J(orders[i].arg1, orders, file_length); goto the_end; }
		else if (strcmp(orders[i].order, "JN") == 0 && program_status_register == 2) { i = execute_J(orders[i].arg1, orders, file_length); goto the_end; }
		else if (strcmp(orders[i].order, "JZ") == 0 && program_status_register == 0) { i = execute_J(orders[i].arg1, orders, file_length); goto the_end; }

	the_end:
		if (c != 'i') { print_registers_values(); print_program_memory(variables, declaration_lines); }

		if (c != 'i' && i != file_length - declaration_lines - 1) printf("%s\n", "Press f to continue, s to quit or i for immediate execution");
	}
}

void execute_AR(char arg1[], char arg2[])
{
	int arg1_int = atoi(arg1);
	int arg2_int = atoi(arg2);

	reg[arg1_int] += reg[arg2_int];
	update_program_status_register(reg[arg1_int]);
	return;
}

void execute_A(char arg1[], char arg2[], struct Variable variables[], int program_memory[])
{
	int arg1_int = atoi(arg1);
	int i = 0;
	int optional_register_number;

	//there are 4 options for the second argument: label, label+register, address, address+register
	//first we check if there is an optional register number in brackets and we parse it
	int if_brackets = check_if_brackets(arg2);
	if (if_brackets != 0) optional_register_number = if_brackets;

	//then we check if the string before the optional brackets is one of the labels or not
	bool if_label = false;
	for (i = 0; i < declaration_lines; i++)
	{
		if (strcmp(arg2, variables[i].label) == 0)
		{
			if_label = true;
			if (if_brackets == 0) reg[arg1_int] += *(variables[i].program_memory_pointer + (reg[14] / 4));
			if (if_brackets != 0) reg[arg1_int] += *(variables[i].program_memory_pointer + (reg[optional_register_number] / 4) + (reg[14] / 4));
		}
	}

	//if it is not one of the labels then it's an address so we parse it
	if (if_label == false)
	{
		int address = parse_address(arg2);
		if (if_brackets == 0) reg[arg1_int] += *(program_memory + (address / 4));
		if (if_brackets != 0) reg[arg1_int] += *(program_memory + (address / 4) + (reg[optional_register_number] / 4));

	}

	update_program_status_register(reg[arg1_int]);
}

void execute_SR(char arg1[], char arg2[])
{
	int arg1_int = atoi(arg1);
	int arg2_int = atoi(arg2);

	reg[arg1_int] -= reg[arg2_int];
	update_program_status_register(reg[arg1_int]);
	return;
}

void execute_S(char arg1[], char arg2[], struct Variable variables[], int program_memory[])
{
	int arg1_int = atoi(arg1);
	int i = 0;
	int optional_register_number;

	//there are 4 options for the second argument: label, label+register, address, address+register
	//first we check if there is an optional register number in brackets and we parse it
	int if_brackets = check_if_brackets(arg2);
	if (if_brackets != 0) optional_register_number = if_brackets;
	//then we check if the string before the oprional brackets is one of the labels or not
	bool if_label = false;
	for (i = 0; i < declaration_lines; i++)
	{
		if (strcmp(arg2, variables[i].label) == 0)
		{
			if_label = true;
			if (if_brackets == 0) reg[arg1_int] -= *(variables[i].program_memory_pointer + (reg[14] / 4));
			if (if_brackets != 0) reg[arg1_int] -= *(variables[i].program_memory_pointer + (reg[optional_register_number] / 4) + (reg[14] / 4));
		}
	}

	//if it is not one of the labels then it's an address so we parse it
	if (if_label == false)
	{
		int address = parse_address(arg2);
		if (if_brackets == 0) reg[arg1_int] -= *(program_memory + (address / 4));
		if (if_brackets != 0) reg[arg1_int] -= *(program_memory + (address / 4) + (reg[optional_register_number] / 4));

	}

	update_program_status_register(reg[arg1_int]);
}

void execute_MR(char arg1[], char arg2[])
{
	int arg1_int = atoi(arg1);
	int arg2_int = atoi(arg2);

	reg[arg1_int] *= reg[arg2_int];
	update_program_status_register(reg[arg1_int]);
	return;
}

void execute_M(char arg1[], char arg2[], struct Variable variables[], int program_memory[])
{
	int arg1_int = atoi(arg1);
	int i = 0;
	int optional_register_number;

	//there are 4 options for the second argument: label, label+register, address, address+register
	//first we check if there is an optional register number in brackets and we parse it
	int if_brackets = check_if_brackets(arg2);
	if (if_brackets != 0) optional_register_number = if_brackets;
	//then we check if the string before the oprional brackets is one of the labels or not
	bool if_label = false;
	for (i = 0; i < declaration_lines; i++)
	{
		if (strcmp(arg2, variables[i].label) == 0)
		{
			if_label = true;
			if (if_brackets == 0) reg[arg1_int] *= *(variables[i].program_memory_pointer + (reg[14] / 4));
			if (if_brackets != 0) reg[arg1_int] *= *(variables[i].program_memory_pointer + (reg[optional_register_number] / 4) + (reg[14 / 4]));
		}
	}

	//if it is not one of the labels then it's an address so we parse it
	if (if_label == false)
	{
		int address = parse_address(arg2);
		if (if_brackets == 0) reg[arg1_int] *= *(program_memory + (address / 4));
		if (if_brackets != 0) reg[arg1_int] *= *(program_memory + (address / 4) + (reg[optional_register_number] / 4));

	}

	update_program_status_register(reg[arg1_int]);

}

void execute_DR(char arg1[], char arg2[])
{
	int arg1_int = atoi(arg1);
	int arg2_int = atoi(arg2);

	reg[arg1_int] /= reg[arg2_int];
	update_program_status_register(reg[arg1_int]);
	return;
}

void execute_D(char arg1[], char arg2[], struct Variable variables[], int program_memory[])
{
	int arg1_int = atoi(arg1);
	int i = 0;
	int optional_register_number;

	//there are 4 options for the second argument: label, label+register, address, address+register
	//first we check if there is an optional register number in brackets and we parse it
	int if_brackets = check_if_brackets(arg2);
	if (if_brackets != 0) optional_register_number = if_brackets;
	//then we check if the string before the oprional brackets is one of the labels or not
	bool if_label = false;
	for (i = 0; i < declaration_lines; i++)
	{
		if (strcmp(arg2, variables[i].label) == 0)
		{
			if_label = true;
			if (if_brackets == 0) reg[arg1_int] /= *(variables[i].program_memory_pointer + (reg[14] / 4));
			if (if_brackets != 0) reg[arg1_int] /= *(variables[i].program_memory_pointer + (reg[optional_register_number] / 4) + (reg[14] / 4));
		}
	}

	//if it is not one of the labels then it's an address so we parse it
	if (if_label == false)
	{
		int address = parse_address(arg2);
		if (if_brackets == 0) reg[arg1_int] /= *(program_memory + (address / 4));
		if (if_brackets != 0) reg[arg1_int] /= *(program_memory + (address / 4) + (reg[optional_register_number] / 4));

	}

	update_program_status_register(reg[arg1_int]);

}

void execute_CR(char arg1[], char arg2[])
{
	int arg1_int = atoi(arg1);
	int arg2_int = atoi(arg2);

	update_program_status_register(reg[arg1_int] - reg[arg2_int]);
}

void execute_C(char arg1[], char arg2[], struct Variable variables[], int program_memory[])
{
	int arg1_int = atoi(arg1);
	int i = 0;
	int optional_register_number;

	//there are 4 options for the second argument: label, label+register, address, address+register
	//first we check if there is an optional register number in brackets and we parse it
	int if_brackets = check_if_brackets(arg2);
	if (if_brackets != 0) optional_register_number = if_brackets;
	//then we check if the string before the oprional brackets is one of the labels or not
	bool if_label = false;
	for (i = 0; i < declaration_lines; i++)
	{
		if (strcmp(arg2, variables[i].label) == 0)
		{
			if_label = true;
			if (if_brackets == 0) update_program_status_register(reg[arg1_int] - *(variables[i].program_memory_pointer + (reg[14] / 4)));
			if (if_brackets != 0) update_program_status_register(reg[arg1_int] - *(variables[i].program_memory_pointer + (reg[optional_register_number] / 4) + (reg[14] / 4)));
		}
	}

	//if it is not one of the labels then it's an address so we parse it
	if (if_label == false)
	{
		int address = parse_address(arg2);
		if (if_brackets == 0) update_program_status_register(reg[arg1_int] - *(program_memory + (address / 4)));
		if (if_brackets != 0) update_program_status_register(reg[arg1_int] - *(program_memory + (address / 4) + (reg[optional_register_number] / 4)));

	}
}

void execute_LR(char arg1[], char arg2[])
{
	int arg1_int = atoi(arg1);
	int arg2_int = atoi(arg2);

	reg[arg1_int] = reg[arg2_int];
	return;
}

void execute_L(char arg1[], char arg2[], struct Variable variables[], int program_memory[])
{
	int arg1_int = atoi(arg1);
	int i = 0;
	int optional_register_number;

	//there are 4 options for the second argument: label, label+register, address, address+register
	//first we check if there is an optional register number in brackets and we parse it
	int if_brackets = check_if_brackets(arg2);
	if (if_brackets != 0) optional_register_number = if_brackets;
	//then we check if the string before the oprional brackets is one of the labels or not
	bool if_label = false;
	for (i = 0; i < declaration_lines; i++)
	{
		if (strcmp(arg2, variables[i].label) == 0)
		{
			if_label = true;
			if (if_brackets == 0) reg[arg1_int] = *(variables[i].program_memory_pointer + (reg[14] / 4));
			if (if_brackets != 0) reg[arg1_int] = *(variables[i].program_memory_pointer + (reg[optional_register_number] / 4) + (reg[14] / 4));
		}
	}

	//if it is not one of the labels then it's an address so we parse it
	if (if_label == false)
	{
		int address = parse_address(arg2);
		if (if_brackets == 0) reg[arg1_int] = *(program_memory + (address / 4));
		if (if_brackets != 0) reg[arg1_int] = *(program_memory + (address / 4) + (reg[optional_register_number] / 4));

	}

}

int execute_J(char arg1[], struct Order orders[], int file_length)
{
	int i = 0;
	for (i; i < file_length - declaration_lines; i++)
		if (strcmp(orders[i].label, arg1) == 0) return ((i - 1) + (reg[15] / 4));
}

void execute_ST(char arg1[], char arg2[], struct Variable variables[], int program_memory[])
{
	int arg1_int = atoi(arg1);
	int i = 0;
	int optional_register_number;

	//there are 4 options for the second argument: label, label+register, address, address+register
	//first we check if there is an optional register number in brackets and we parse it
	int if_brackets = check_if_brackets(arg2);
	if (if_brackets != 0) optional_register_number = if_brackets;
	//then we check if the string before the oprional brackets is one of the labels or not
	bool if_label = false;
	for (i = 0; i < declaration_lines; i++)
	{
		if (strcmp(arg2, variables[i].label) == 0)
		{
			if_label = true;
			if (if_brackets == 0) *(variables[i].program_memory_pointer + (reg[14] / 4)) = reg[arg1_int];
			if (if_brackets != 0) *(variables[i].program_memory_pointer + (reg[optional_register_number] / 4) + (reg[14] / 4)) = reg[arg1_int];
		}
	}

	//if it is not one of the labels then it's an address so we parse it
	if (if_label == false)
	{
		int address = parse_address(arg2);
		if (if_brackets == 0) *(program_memory + (address / 4)) = reg[arg1_int];
		if (if_brackets != 0)  *(program_memory + (address / 4) + (reg[optional_register_number] / 4)) = reg[arg1_int];

	}
}

void update_program_status_register(int result)
{
	if (result == 0) program_status_register = 0;
	else if (result > 0) program_status_register = 1;
	else if (result < 0) program_status_register = 2;
	else program_status_register = 3;
}

void execute_LA(char arg1[], char arg2[], struct Variable variables[], int program_memory[])
{
	int arg1_int = atoi(arg1);
	int i = 0;
	int optional_register_number;

	//there are 4 options for the second argument: label, label+register, address, address+register
	//first we check if there is an optional register number in brackets and we parse it
	int if_brackets = check_if_brackets(arg2);
	if (if_brackets != 0) optional_register_number = if_brackets;
	//then we check if the string before the oprional brackets is one of the labels or not
	bool if_label = false;
	for (i = 0; i < declaration_lines; i++)
	{
		if (strcmp(arg2, variables[i].label) == 0)
		{
			if_label = true;
			if (if_brackets == 0) reg[arg1_int] = 4 * (variables[i].program_memory_pointer - program_memory) + reg[14];
			if (if_brackets != 0) reg[arg1_int] = 4 * (variables[i].program_memory_pointer - program_memory) + reg[optional_register_number] + reg[14];
		}
	}

}

