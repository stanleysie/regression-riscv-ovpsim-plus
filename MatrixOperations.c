#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrixOperations.h"

void matrix_matrix_add(int row, int col, MATRIX A, MATRIX B, MATRIX C) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"vsetvli	t0, %0, e32	\n"
			"vlw.v		v0, (%1)	\n"
			"vlw.v		v1, (%2)	\n"
			"vfadd.vv	v2, v0, v1	\n"
			"vsw.v		v2, (%3)	\n"
			:
			: "r"(col), "r"(A.mem[i]), "r"(B.mem[i]), "r"(C.mem[i])
		);	
	}
}

void matrix_matrix_sub(int row, int col, MATRIX A, MATRIX B, MATRIX C) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"vsetvli	t0, %0, e32	\n"
			"vlw.v		v0, (%1)	\n"
			"vlw.v		v1, (%2)	\n"
			"vfsub.vv	v2, v0, v1	\n"
			"vsw.v		v2, (%3)	\n"
			:
			: "r"(col), "r"(A.mem[i]), "r"(B.mem[i]), "r"(C.mem[i])
		);	
	}
}

void matrix_scalar_add(int row, int col, MATRIX A, float num, MATRIX C) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"vsetvli	t0, %0, e32	\n"
			"vlw.v		v0, (%1)	\n"
			"flw		f0, 0(%2)	\n"
			"vfadd.vf	v1, v0, f0	\n"
			"vsw.v		v1, (%3)	\n"
			:
			: "r"(col), "r"(A.mem[i]), "r"(&num), "r"(C.mem[i])
		);
	}
}

void matrix_scalar_sub(int row, int col, MATRIX A, float num, MATRIX C) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"vsetvli	t0, %0, e32	\n"
			"vlw.v		v0, (%1)	\n"
			"flw		f0, 0(%2)	\n"
			"vfsub.vf	v1, v0, f0	\n"
			"vsw.v		v1, (%3)	\n"
			:
			: "r"(col), "r"(A.mem[i]), "r"(&num), "r"(C.mem[i])
		);
	}
}

void matrix_scalar_mul(int row, int col, MATRIX A, float num, MATRIX C) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"vsetvli	t0, %0, e32	\n"
			"vlw.v		v0, (%1)	\n"
			"flw		f0, 0(%2)	\n"
			"vfmul.vf	v1, v0, f0	\n"
			"vsw.v		v1, (%3)	\n"
			:
			: "r"(col), "r"(A.mem[i]), "r"(&num), "r"(C.mem[i])
		);
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
