#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrixOperations.h"

void matrix_matrix_add(int row, int col, MATRIX A, MATRIX B, MATRIX C) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C.mem[i]->vf32[j] = A.mem[i]->vf32[j] + B.mem[i]->vf32[j];
		}
	}
}

void matrix_matrix_sub(int row, int col, MATRIX A, MATRIX B, MATRIX C) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C.mem[i]->vf32[j] = A.mem[i]->vf32[j] - B.mem[i]->vf32[j];
		}	
	}
}

void matrix_scalar_add(int row, int col, MATRIX A, float num, MATRIX C) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C.mem[i]->vf32[j] = A.mem[i]->vf32[j] + num;
		}
	}
}

void matrix_scalar_sub(int row, int col, MATRIX A, float num, MATRIX C) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C.mem[i]->vf32[j] = A.mem[i]->vf32[j] - num;
		}
	}
}

void matrix_scalar_mul(int row, int col, MATRIX A, float num, MATRIX C) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C.mem[i]->vf32[j] = A.mem[i]->vf32[j] * num;
		}
	}
}

int
main() {
	enableVEC();
	enableFP();
	
	int row = 100, col = 16;
//	float num = 100.0;
	if(col > VEC32) {
		printf("[Error] - number of columns exceeded the capacity of registers.\n\n");
		return 1;
	}
	
	int i, j;
	
	float A[row][col];
	float B[row][col];
	
	MATRIX mA, mB, mC;
	
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			A[i][j] = i + j;
			B[i][j] = i;
		}
	}
	
	for(i = 0; i < row; i++) {
		mA.mem[i] = malloc(sizeof(v512T));
		mB.mem[i] = malloc(sizeof(v512T));
		mC.mem[i] = malloc(sizeof(v512T));
		
		for(j = 0; j < col; j++) {
			mA.mem[i]->vf32[j] = A[i][j];
			mB.mem[i]->vf32[j] = B[i][j];
		}
	}
	
	// call functions here
	matrix_matrix_add(row, col, mA, mB, mC);
//	matrix_scalar_add(row, col, mA, num, mC);
	
	// free allocated memory
	for(i = 0; i < row; i++) {
		free(mA.mem[i]);
		free(mB.mem[i]);
		free(mC.mem[i]);
	}
	
	return 0;
}
