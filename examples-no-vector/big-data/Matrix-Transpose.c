#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_transpose(int row, int col, float A[][col], float B[][row]) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			B[j][i] = A[i][j];
		}
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
}
