#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define UNDEFINED -1

bool	is_valid(char set[], size_t set_length, bool solution[])
{
	int opened_parentheses = 0;
	for (size_t index = 0; index < set_length; index++) {
		if (solution[index]) {
			if (set[index] == '(')
				opened_parentheses++;
			else if (set[index] == ')' && opened_parentheses > 0)
				opened_parentheses--;
			else if (set[index] == ')' && opened_parentheses == 0)
				return false;
		}
	}
	return opened_parentheses == 0;
}

void	print_solution(char set[], size_t set_length, bool solution[])
{
	for (size_t index = 0; index < set_length; index++) {
		if (solution[index])
			printf("%c", set[index]);
		else
			printf("_");
	}
	printf("\n");
}

bool	is_minimum_removed(bool solution[], size_t set_length, int* minimal_size)
{
	int removed_count = 0;
	for (size_t index = 0; index < set_length; index++) {
		if (!solution[index])
			removed_count++;
	}

	if (*minimal_size == UNDEFINED) {
		*minimal_size = removed_count;
		return true;
	}
	if (removed_count <= *minimal_size) {
		*minimal_size = removed_count;
		return true;
	}
	return false;
}

void	go_deeper(size_t index, char set[], size_t set_length, bool solution[], int* minimal_size)
{
	if (index >= set_length) {
		if (is_valid(set, set_length, solution) && is_minimum_removed(solution, set_length, minimal_size))
			print_solution(set, set_length, solution);
		return;
	}

	if (set[index] == '(' || set[index] == ')') {
		solution[index] = true;
		go_deeper(index + 1, set, set_length, solution, minimal_size);

		solution[index] = false;
		go_deeper(index + 1, set, set_length, solution, minimal_size);
	}
	else {
		solution[index] = true;
		go_deeper(index + 1, set, set_length, solution, minimal_size);
	}
}


char** removeInvalidParentheses(char* s) {
	size_t	set_length = strlen(s);
	char*	set = s;
	bool*	solution = calloc(set_length, sizeof(bool));

	int minimal_size = UNDEFINED;
	go_deeper(0, set, set_length, solution, &minimal_size);

	return NULL;
}

int main(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
		removeInvalidParentheses(argv[i]);
	return (0);
}
