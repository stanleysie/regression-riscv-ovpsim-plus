#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_matrix_add(int row, int col, float A[][col], float B[][col], float C[][col]) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"lvadd:						\n"
			"	vsetvli		t0, %0, e32	\n"
			"	vlw.v		v0, (%1)	\n"
			"	sub			%0, %0, t0	\n"
			"	slli		t0, t0, 2	\n"
			"	add			%1, %1, t0	\n"
			"	vlw.v		v1, (%2)	\n"
			"	add			%2, %2, t0	\n"
			"	vfadd.vv	v2, v0, v1	\n"
			"	vsw.v		v2, (%3)	\n"
			"	add			%3, %3, t0	\n"
			"	bnez		%0, lvadd	\n"
			:
			: "r"(col), "r"(&A[i][0]), "r"(&B[i][0]), "r"(&C[i][0])
		);	
	}
}

int
main() {
	enableVEC();
	enableFP();
	
	int rowA = 10000, colA = 10000, rowB = 10000, colB = 10000;
	
	// load random data
	float A[rowA][colA];
	float B[rowB][colB];
	float C[rowA][colB];
	
	int i, j;
	for(i = 0; i < rowA; i++) {
		for(j = 0; j < colA; j++) {
			A[i][j] = i;
			B[i][j] = j;
		}
	}
	
	matrix_matrix_add(rowA, colB, A, B, C);
	
	return 0;
}
