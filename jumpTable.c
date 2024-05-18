#include <stdio.h>
#include <stdlib.h>

void	v1() {
	printf("[1]\n");
}
void	v2() {
	printf("[2]\n");
}
void	v3() {
	printf("[3]\n");
}

int	i1(int i) {
	return i * 1;
}
int	i2(int i) {
	return i * 2;
}
int	i3(int i) {
	return i * 3;
}
int	i4(int i) {
	return i * 4;
}
int	i5(int i) {
	return i * 5;
}
int	i6(int i) {
	return i * 6;
}
int	i7(int i) {
	return i * 7;
}
int	i8(int i) {
	return i * 8;
}
int	i9(int i) {
	return i * 9;
}
int	i10(int i) {
	return i * 10;
}
int	i11(int i) {
	return i * 11;
}
int	i12(int i) {
	return i * 12;
}

int	main(void) {
	void	(*jumpTable1[3])() = {&v1, &v2, &v3};
	for (int i = 0; i < 3; i++) {
		jumpTable1[i]();
	}

	int	(*jumpTable2[3])() = {&i1, &i2, &i3};
	for (int i = 0; i < 3; i++) {
		printf("%d\n", jumpTable2[i](i));
	}

	int	(**jumpTable3)() = malloc(jumpTable2[2](4) * sizeof(void *));
	jumpTable3[0] = &i1;
	jumpTable3[1] = &i2;
	jumpTable3[2] = &i3;
	jumpTable3[3] = &i4;
	jumpTable3[4] = &i5;
	jumpTable3[5] = &i6;
	jumpTable3[6] = &i7;
	jumpTable3[7] = &i8;
	jumpTable3[8] = &i9;
	jumpTable3[9] = &i10;
	jumpTable3[10] = &i11;
	jumpTable3[11] = &i12;
	for (int i = 0; i < 12; i++) {
		printf("%d\n", jumpTable3[i](i));
	}
	return 0;
}