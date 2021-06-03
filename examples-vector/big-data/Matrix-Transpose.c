#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_transpose(int row, int col, float A[][col], float B[][row]) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"ltrans:					\n"
			"	vsetvli		t0, %0, e32	\n"
			"	vlw.v		v0, (%1)	\n"
			"	sub			%0, %0, t0	\n"
			"	slli		t0, t0, 2	\n"
			"	add			%1, %1, t0	\n"
			"	vssw.v		v0, (%2), %3\n"
			"	add			%2, %2, t0	\n"
			"	bnez		%0, ltrans	\n"
			:
			: "r"(col), "r"(&A[i][0]), "r"(&B[0][i]), "r"(row*4)
		);
	}
}

int
main() {
	enableVEC();
	enableFP();
	
	int row = 10000, col = 10000;
	
	// load random data
	float A[row][col];
	float B[col][row];
	
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			A[i][j] = i;
		}
	}
	
	matrix_transpose(row, col, A, B);
	
	return 0;
	
	return 0;
}
