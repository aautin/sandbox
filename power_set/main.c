#include <stdio.h>
#include <stdlib.h>

void print_subset(int* subset, int subset_size)
{
	if (subset_size > 0)
		printf("%d", subset[0]);
	for (int i = 1; i < subset_size; ++i)
		printf(" %d", subset[i]);
	if (subset_size > 0)
		printf("\n");
}

int calculate_subset(int* subset, int subset_size)
{
	int result = 0;
	for (int i = 0; i < subset_size; ++i)
		result += subset[i];
	return result;
}

void backtracking(int* set, int* subset, int index, int subset_size, int set_size, int target)
{
	if (index == set_size && calculate_subset(subset, subset_size) == target) {
		print_subset(subset, subset_size);
		return;
	}

	if (index == set_size)
		return;

	backtracking(set, subset, index + 1, subset_size, set_size, target);
	
	subset[subset_size] = set[index];
	backtracking(set, subset, index + 1, subset_size + 1, set_size, target);
}

int main(int argc, char *argv[]) {
	int*	set = malloc((argc - 2) * sizeof(int));
	int*	subset = malloc((argc - 2) * sizeof(int));
	int		target = atoi(argv[1]);
	int		set_size = argc - 2;
	for (int i = 0; i < set_size; ++i)
		set[i] = atoi(argv[i + 2]);

	backtracking(set, subset, 0, 0, set_size, target);

	return 0;
}
