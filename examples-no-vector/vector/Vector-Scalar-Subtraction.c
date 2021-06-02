#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"


void vector_scalar_sub(int col, float A[], float num, float B[]) {
	int i;
	for(i = 0; i < col; i++) {
		B[i] = A[i] - num;
	}
}

void print_vector(int col, float V[], char s[]) {
	int i;
	printf("\n%s\n", s);
	for(i = 0; i < col; i++) {
		printf("%.2f\t", V[i]);
	}
	printf("\n\n");
}

int
main() {
	enableVEC();
	enableFP();
	
	int size = 20;
	
	// load random data
	float A[20] = {-24, 41, 15, -48, -43, 7, -34, 35, -10, -42, 33, 30, 27, -43, 48, -5, -6, -17, -8, -2};
	float B[size];
	float num = 12.97;
	
	print_vector(size, A, "Matrix A");
	printf("Num: %.2f\n", num);
	
	vector_scalar_sub(size, A, num, B);
	
	print_vector(size, B, "Matrix B");
	
	return 0;
}
