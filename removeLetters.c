#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

char *ft_strchr(char *s, char a) {
    while (*s) {
        if (*s == a)
            return (s);
        s++;
    }
    return (NULL);
}

int	isEmpty(char toPlace[], int size) {
	while (size--) {
		if (toPlace[size])
			return (0);
	}
	return (1);
}

int	findThem(char toPlace[], char s[], char a) {
	int i = 0;
	int j;
	while (s[i]) {
		if (s[i] == a) {
			j = 0;
			while (j < 26) {
				if (toPlace[j] == 1 && ft_strchr(&s[i], j + 'a') == NULL)
					break ;
				j++;
			}
			if (j == 26)
				return (i);
		}
		i++;
	}
	return (-1);
}

char	*removeDuplicateLetters(char *s) {
    char    toPlace[26] = "";
	char	*res = s;

    // store the letters to place in final result
    int i = 0;
    while (s[i]) {
        toPlace[s[i++] - 'a'] = 1;
    }

	// select the letters to place in the right order
    char	*placeStatus;
    int 	resLen = 0;
	while (!isEmpty(toPlace, 26)) {
		i = 0;
		while (i < 26) {
			if (toPlace[i] == 1) {
				int index = findThem(toPlace, s, i + 'a');
				if (index >= 0) {
					s = s + index + 1;
					toPlace[i] = 0;
					res[resLen++] = i + 'a';
					break ;
				}
			}
			i++;
		}
    }
	res[resLen] = 0;
    return res;
}

int main(void) {
	char str[9] = "cbacdcbc";
	char *res;

	res = removeDuplicateLetters(str);
	printf("%s\n", res);
	return (0);
}
