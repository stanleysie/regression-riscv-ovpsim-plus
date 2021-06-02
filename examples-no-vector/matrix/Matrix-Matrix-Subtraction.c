#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void matrix_matrix_sub(int row, int col, float A[][col], float B[][col], float C[][col]) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = A[i][j] - B[i][j];
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
	
	int rowA = 6, colA = 4, rowB = 6, colB = 4;
	
	// load random data
	float A[6][4] = {
		{61, -18, -49, 45}, 
		{-87, 29, 28, 23}, 
		{67, -24, -45, -47}, 
		{79, 53, -3, -21}, 
		{49, 46, 59, 45}, 
		{-27, -17, 87, 84}
	};
	float B[6][4] = {
		{23, 43, 88, 38}, 
		{-69, -57, 63, -32}, 
		{-42, -8, -35, 19}, 
		{89, 31, 16, -10}, 
		{34, 19, -99, 98}, 
		{3, -92, -39, -100}
	};
	float C[rowA][colB];
	
	print_matrix(rowA, colA, A, "Matrix A");
	print_matrix(rowB, colB, B, "Matrix B");
	
	matrix_matrix_sub(rowA, colB, A, B, C);
	
	print_matrix(rowA, colB, C, "Matrix C");
	
	return 0;
}
