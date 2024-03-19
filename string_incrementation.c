#include <stdio.h>

static void	incremente(char **arg)
{
	(*arg)++;
}

int middle_function(char *argv)
{
	printf("%s\n", argv);
	incremente(&argv);
	printf("%s\n", argv);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		printf("[main]%s\n", argv[argc - 1]);
		middle_function(argv[argc - 1]);
		printf("[main]%s\n", argv[argc - 1]);
	}
	return (0);
}
