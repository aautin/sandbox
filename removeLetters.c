#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>


int ft_strchr(char *s, char a) {
    while (*s) {
        if (*s == a)
            return (1);
        s++;
    }
    return (0);
}

int findThem(char *s, char *toPlace) {
    for (char i = 0; i < 26; i++) {
        if (toPlace[i] && ft_strchr(s, i + 'a') == 0)
            return (0);
        i++;
    }
    return (1);
}

int isEmpty(char *s, int size) {
    while (size--) {
        if (*s)
            return (0);
        s++;
    }
    return (1);
}

int tryPlace(char *s, char *toPlace, char a) {
    for (int i = 0; s[i]; i++) {
        if (s[i] == a && findThem(s + i, toPlace))
            return (i + 1);
    }
    return (0);
}

char *removeDuplicateLetters(char *s) {
    char    toPlace[26] = "";

    // store the letters to place in the final result
    int i = 0;
    while (s[i]) {
        toPlace[s[i++] - 'a'] = 1;
    }

    int placeStatus;
    while (!isEmpty(toPlace, 26)) {
        for (i = 0; i < 26; i++) {
            if (toPlace[i] == 1) {
                placeStatus = tryPlace(s, toPlace, 'a' + i);
                if (placeStatus) {
                    s = s + placeStatus;
                    printf("i=%d|status=%d|%c|%s\n", i, placeStatus, i + 'a', s);
                    toPlace[i] = 0;
                    i = 26;
                }
            }
        }
    }

    return s;
}

int main(void) {
	char str[9] = "cbacdcbc";
	char *res;

	res = removeDuplicateLetters(str);
	return (0);
}
