#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_matrix_mul(int row, int col, int len, float A[][len], float B[][col], float C[][col]) {
	int i, j, k;
	printf("\nMatrix C\n");
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = 0;
			for(k = 0; k < len; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
			printf("%.2f \t", C[i][j]);
		}
		printf("\n");
	}
	printf("\n");
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
	
	int rowA = 6, colA = 4, rowB = 4, colB = 3;
	
	// load random data
	float A[6][4] = {
		{33, -48, -39, 40}, 
		{50, 40, 25, 14}, 
		{-28, 27, 38, -11}, 
		{8, 38, -21, 48}, 
		{39, -28, -39, -50}, 
		{26, -13, -3, 46}
	};
	float B[4][3] = {
		{49, -46, -38}, 
		{-45, 14, 36}, 
		{-10, 36, 7}, 
		{46, -34, 44}, 
	};
	float C[rowA][colB];
	
	print_matrix(rowA, colA, A, "Matrix A");
	print_matrix(rowB, colB, B, "Matrix B");
	
	matrix_matrix_mul(rowA, colB, colA, A, B, C);
	
	return 0;
}
