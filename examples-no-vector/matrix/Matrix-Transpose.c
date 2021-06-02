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
	
	int row = 7, col = 5;
	
	// load random data
	float A[7][5] = {
		{-28, -16, -13, -27, 41},
		{14, 24, -48, -1, -18},
		{20, -11, 32, -12, 12},
		{-50, 17, 16, -12, 50},
		{-20, 17, -36, -41, 49},
		{-25, 28, 42, -42, 32},
		{-9, 26, 48, 2, 38}
	};
	float B[col][row];
	
	print_matrix(row, col, A, "Matrix A");
	
	matrix_transpose(row, col, A, B);
	
	print_matrix(col, row, B, "Matrix B");
	
	return 0;
}
