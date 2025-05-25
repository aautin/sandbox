#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define BITS_PER_BYTE 8
#define BYTE_PER_INT 4
#define BITS_PER_INT (BYTE_PER_INT * BITS_PER_BYTE)
#define ARRAY_SIZE 2

bool get_bit(int number, int bit_index) {
    return (number >> (BITS_PER_INT - bit_index - 1)) & 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3)
        return 1;

    int number[ARRAY_SIZE] = { atoi(argv[1]), atoi(argv[2]) };
    printf("Array %p: \n", number);
    for(int i = 0; i < BITS_PER_INT * ARRAY_SIZE; i++) {
        if (i % 32 == 0)
            printf("\n[%d](%p): \n", i / 32, &number[i / 32]);
        
        printf("%d", get_bit(number[i / 32], i % 32));
        if (i % 8 == 7)
            printf(" ");
    }
    printf("\n");
    return 0;
}
