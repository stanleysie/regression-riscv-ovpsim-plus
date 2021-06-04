#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_matrix_mul(int row, int col, int len, float A[][len], float B[][col], float C[][col]) {
	int i, j, k;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = 0;
			for(k = 0; k < len; k++) {
				C[i][j] += A[i][k] * B[k][j];
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
