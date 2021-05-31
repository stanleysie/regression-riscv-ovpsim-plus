#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrixOperations.h"

void vector_vector_add(int n, v512P A, v512P B, v512P C) {
	asm(
		"vsetvli	t0, %0, e32	\n"
		"vlw.v		v0, (%1)	\n"
		"vlw.v		v1, (%2)	\n"
		"vfadd.vv	v2, v0, v1	\n"
		"vsw.v		v2, (%3)	\n"
		:
		: "r"(n), "r"(A), "r"(B), "r"(C)
	);
}

void vector_vector_sub(int n, v512P A, v512P B, v512P C) {
	asm(
		"vsetvli	t0, %0, e32	\n"
		"vlw.v		v0, (%1)	\n"
		"vlw.v		v1, (%2)	\n"
		"vfsub.vv	v2, v0, v1	\n"
		"vsw.v		v2, (%3)	\n"
		:
		: "r"(n), "r"(A), "r"(B), "r"(C)
	);
}

void vector_scalar_add(int n, v512P A, float num, v512P C) {
	asm(
		"vsetvli	t0, %0, e32	\n"
		"vlw.v		v0, (%1)	\n"
		"flw		f0, 0(%2)	\n"
		"vfadd.vf	v1, v0, f0	\n"
		"vsw.v		v1, (%3)	\n"
		:
		: "r"(n), "r"(A), "r"(&num), "r"(C)
	);
}

void vector_scalar_sub(int n, v512P A, float num, v512P C) {
	asm(
		"vsetvli	t0, %0, e32	\n"
		"vlw.v		v0, (%1)	\n"
		"flw		f0, 0(%2)	\n"
		"vfsub.vf	v1, v0, f0	\n"
		"vsw.v		v1, (%3)	\n"
		:
		: "r"(n), "r"(A), "r"(&num), "r"(C)
	);
}

int
main() {
	enableVEC();
	enableFP();
	
	int row = 100, col = 16;
	float num = 100.5;
	if(col > VEC32) {
		printf("[Error] - number of columns exceed the capacity of registers.\n\n");
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
		
		// call functions here
		vector_vector_add(col, mA.mem[i], mB.mem[i], mC.mem[i]);
//		vector_scalar_add(col, mA.mem[i], num, mC.mem[i]);
	}
	
	// free allocated memory
	for(i = 0; i < row; i++) {
		free(mA.mem[i]);
		free(mB.mem[i]);
		free(mC.mem[i]);
	}
	
	return 0;
}
