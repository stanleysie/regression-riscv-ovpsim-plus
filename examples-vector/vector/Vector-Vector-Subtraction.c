#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void vector_vector_sub(int col, float A[], float B[], float C[]) {
	asm(
		"vvsub:						\n"
		"	vsetvli		t0, %0, e32	\n"
		"	vlw.v		v0, (%1)	\n"
		"	sub			%0, %0, t0	\n"
		"	slli		t0, t0, 2	\n"
		"	add			%1, %1, t0	\n"
		"	vlw.v		v1, (%2)	\n"
		"	add			%2, %2, t0	\n"
		"	vfsub.vv	v2, v0, v1	\n"
		"	vsw.v		v2, (%3)	\n"
		"	add			%3, %3, t0	\n"
		"	bnez		%0, vvsub	\n"
		:
		: "r"(col), "r"(&A[0]), "r"(&B[0]), "r"(&C[0])
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
	float B[20] = {25, 3, 1, -39, 17, 44, -13, -22, 22, 35, 3, 6, -33, -45, 11, 34, 20, 19, -6 , -40};
	float C[size];
	
	print_vector(size, A, "Matrix A");
	print_vector(size, B, "Matrix B");
	
	vector_vector_sub(size, A, B, C);
	
	print_vector(size, C, "Matrix C");
	
	return 0;
}
