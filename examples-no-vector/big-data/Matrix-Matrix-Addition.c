#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_matrix_add(int row, int col, float A[][col], float B[][col], float C[][col]) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
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
