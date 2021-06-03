#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_scalar_sub(int row, int col, float A[][col], float num, float B[][col]) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			B[i][j] = A[i][j] - num;
		}
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
	
	matrix_scalar_sub(row, col, A, num, B);
	
	return 0;
}
