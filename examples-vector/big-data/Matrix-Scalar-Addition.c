#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_scalar_add(int row, int col, float A[][col], float num, float B[][col]) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"lsadd:						\n"
			"	vsetvli		t0, %0, e32	\n"
			"	vlw.v		v0, (%1)	\n"
			"	sub			%0, %0, t0	\n"
			"	slli		t0, t0, 2	\n"
			"	add			%1, %1, t0	\n"
			"	flw			f0, 0(%2)	\n"
			"	vfadd.vf	v1, v0, f0	\n"
			"	vsw.v		v1, (%3)	\n"
			"	add			%3, %3, t0	\n"
			"	bnez		%0, lsadd	\n"
			:
			: "r"(col), "r"(&A[i][0]), "r"(&num), "r"(&B[i][0])
		);
	}
}

int
main() {
	enableVEC();
	enableFP();
	
	int row = 10000, col = 10000;
	float num = 45.12;
	
	// load random data
	float A[row][col];
	float B[row][col];
	
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			A[i][j] = i + j;
		}
	}
	
	matrix_scalar_add(row, col, A, num, B);
	
	return 0;
}
