#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv) {
	if (argc < 2)
		return 0;
	int	*nums = malloc((argc - 1) * sizeof(int));
	for (int i = 1; i < argc; i++)
		nums[i] = atoi(argv[i]);
	for (int i = 1; i < argc; i++)
		printf("[%d] : %s -> %d\n", i, argv[i], nums[i]);
	return 0;
}
