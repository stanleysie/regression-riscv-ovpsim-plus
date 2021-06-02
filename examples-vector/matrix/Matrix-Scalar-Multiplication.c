#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_scalar_mul(int row, int col, float A[][col], float num, float B[][col]) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"lsmul:						\n"
			"	vsetvli		t0, %0, e32	\n"
			"	vlw.v		v0, (%1)	\n"
			"	sub			%0, %0, t0	\n"
			"	slli		t0, t0, 2	\n"
			"	add			%1, %1, t0	\n"
			"	flw			f0, 0(%2)	\n"
			"	vfmul.vf	v1, v0, f0	\n"
			"	vsw.v		v1, (%3)	\n"
			"	add			%3, %3, t0	\n"
			"	bnez		%0, lsmul	\n"
			:
			: "r"(col), "r"(&A[i][0]), "r"(&num), "r"(&B[i][0])
		);
	}
}

void print_matrix(int row, int col, float M[][col], char s[]) {
	int i, j;
	printf("\n%s\n", s);
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			printf("%.2f\t", M[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int
main() {
	enableVEC();
	enableFP();
	
	int row = 6, col = 4;
	float num = 45.12;
	
	float A[6][4] = {
		{-32, -6, -21, 34},
		{9, -21, 31, -27},
		{13, 2, 31, -18},
		{17, 11, 7, -7},
		{5, -20, 36, 29},
		{-34, 32, 33, -14}
	};
	float B[row][col];
	
	print_matrix(row, col, A, "Matrix A");
	printf("Num: %.2f\n", num);
	
	matrix_scalar_mul(row, col, A, num, B);
	
	print_matrix(row, col, B, "Matrix B");
	
	return 0;
}
