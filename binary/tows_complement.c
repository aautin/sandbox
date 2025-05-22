#define CHAR_MIN_VALUE -128
#define CHAR_MAX_VALUE 127

#include <stdio.h>

int	main()
{
	for (int nb = CHAR_MIN_VALUE; nb <= CHAR_MAX_VALUE; ++nb) {
		for (int i = 7; i >= 0; i--) {
			printf("%d", (nb & (1 << i)) != 0);
		}
		printf("\n");
	}
	int nb1 = 50;
	for (int i = 7; i >= 0; i--) {
		printf("%d", (nb1 & (1 << i)) != 0);
	}
	printf("\n");

	int nb2 = -50;
	for (int i = 7; i >= 0; i--) {
		printf("%d", (nb2 & (1 << i)) != 0);
	}
	printf("\n");
}
