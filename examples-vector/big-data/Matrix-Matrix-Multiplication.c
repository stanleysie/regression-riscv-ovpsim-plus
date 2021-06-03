#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_matrix_mul(int row, int col, int len, float A[][len], float B[][col], float C[][col]) {
	float tempC[row][col][len];
	
	int i, j, k;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = 0;
			asm(
				"lvmul:						\n"
				"	vsetvli		t0, %0, e32	\n"
				"	vlw.v		v0, (%1)	\n"
				"	sub			%0, %0, t0	\n"
				"	slli		t0, t0, 2	\n"
				"	add			%1, %1, t0	\n"
				"	vlsw.v		v1, (%2), %4\n"
				"	add			%2, %2, t0	\n"
				"	vfmul.vv	v2, v0, v1	\n"
				"	vsw.v		v2, (%3)	\n"
				"	add			%3, %3, t0	\n"
				"	bnez		%0, lvmul	\n"
				:
				: "r"(len), "r"(&A[i][0]), "r"(&B[0][j]), "r"(&tempC[i][j][0]), "r"(col*4)
			);
			for(k = 0; k < len; k++) {
				C[i][j] += tempC[i][j][k];
			}
		}
	}
}

int
main() {
	enableVEC();
	enableFP();
	
	int rowA = 1000, colA = 1000, rowB = 1000, colB = 1000;
	
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
	
	matrix_matrix_mul(rowA, colB, colA, A, B, C);
	
	return 0;
}
