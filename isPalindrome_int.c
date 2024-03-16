int power(int nbr, char power)
{
    if (power == 0)
        return (1);
    while (--power)
        nbr *= nbr;
    return (nbr);
}

int isPalindrome(int x) {
    int     temp = 1;
    int     xReverse = x;
    char    xSize = 1;

    while (xReverse / 10)
    {
        xReverse /= 10;
        xSize++;
    }
    xReverse = 0;
    while (xSize)
    {
        xReverse = xReverse + ((x / power(10, xSize - 1)) % temp);
        xSize--;
        temp = temp * 10;
    }
    return (xReverse);
}

#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		printf("[%s]: %d\n", argv[i], isPalindrome(atoi(argv[i])));
	}
	return (0);
}
