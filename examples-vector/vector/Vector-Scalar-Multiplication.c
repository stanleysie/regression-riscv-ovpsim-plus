#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void vector_scalar_mul(int col, float A[], float num, float B[]) {
	asm(
		"vsmul:						\n"
		"	vsetvli		t0, %0, e32	\n"
		"	vlw.v		v0, (%1)	\n"
		"	sub			%0, %0, t0	\n"
		"	slli		t0, t0, 2	\n"
		"	add			%1, %1, t0	\n"
		"	flw			f0, 0(%2)	\n"
		"	vfmul.vf	v1, v0, f0	\n"
		"	vsw.v		v1, (%3)	\n"
		"	add			%3, %3, t0	\n"
		"	bnez		%0, vsmul	\n"
		:
		: "r"(col), "r"(&A[0]), "r"(&num), "r"(&B[0])
	);
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
	
	vector_scalar_mul(size, A, num, B);
	
	print_vector(size, B, "Matrix B");
	
	return 0;
}
