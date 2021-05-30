#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MatrixOperations.h"

void vector_vector_add(int col, v512P A, v512P B, v512P C) {
	asm(
		"l1:					\n"
		"vsetvli	t0, %0, e32	\n"
		"vlw.v		v0, (%1)	\n"
		"sub		%0, %0, t0	\n"
        "slli		t0, t0, 2	\n"
        "add		%1, %1, t0	\n"
		"vlw.v		v1, (%2)	\n"
		"add		%2, %2, t0	\n"
		"vfadd.vv	v2, v0, v1	\n"
		"vsw.v		v2, (%3)	\n"
		"add		%3, %3, t0	\n"
        "bnez    	%0, l1		\n"
		:
		: "r"(col), "r"(A), "r"(B), "r"(C)
	);
}

void vector_vector_sub(int col, v512P A, v512P B, v512P C) {
	asm(
		"l2:					\n"
		"vsetvli	t0, %0, e32	\n"
		"vlw.v		v0, (%1)	\n"
		"sub		%0, %0, t0	\n"
        "slli		t0, t0, 2	\n"
        "add		%1, %1, t0	\n"
		"vlw.v		v1, (%2)	\n"
		"add		%2, %2, t0	\n"
		"vfsub.vv	v2, v0, v1	\n"
		"vsw.v		v2, (%3)	\n"
		"add		%3, %3, t0	\n"
        "bnez    	%0, l2		\n"
		:
		: "r"(col), "r"(A), "r"(B), "r"(C)
	);
}

//void vector_scalar_add(int col, v512P A, float num, v512P C) {
//	asm(
//		"l3:					\n"
//		"vsetvli	t0, %0, e32	\n"
//		"vlw.v		v0, (%1)	\n"
//		"sub		%0, %0, t0	\n"
//        "slli		t0, t0, 2	\n"
//        "add		%1, %1, t0	\n"
//		"vfadd.vx	v1, v0, %2	\n"
//		"vsw.v		v1, (%3)	\n"
//		"add		%3, %3, t0	\n"
//        "bnez    	%0, l3		\n"
//		:
//		: "r"(col), "r"(A), "r"(num), "r"(C)
//	);
//}
//
//void vector_scalar_sub(int col, v512P A, float num, v512P C) {
//	asm(
//		"l4:					\n"
//		"vsetvli	t0, %0, e32	\n"
//		"vlw.v		v0, (%1)	\n"
//		"sub		%0, %0, t0	\n"
//        "slli		t0, t0, 2	\n"
//        "add		%1, %1, t0	\n"
//		"vfsub.vx	v1, v0, %2	\n"
//		"vsw.v		v1, (%3)	\n"
//		"add		%3, %3, t0	\n"
//        "bnez    	%0, l4		\n"
//		:
//		: "r"(col), "r"(A), "r"(num), "r"(C)
//	);
//}

int
main() {
	enableVEC();
	enableFP();
	
	int row = 25, col = 25;
	int i, j;
	
	float A[row][col];
	float B[row][col];
	
	MATRIX mA, mB, mC;
	
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			A[i][j] = i + j;
			B[i][j] = i + j;
		}
	}
	
	for(i = 0; i < row; i++) {
		mA.el[i] = malloc(sizeof(v512T));
		mB.el[i] = malloc(sizeof(v512T));
		mC.el[i] = malloc(sizeof(v512T));
		for(j = 0; j < col; j++) {
			mA.el[i]->vf32[j] = A[i][j];
			mB.el[i]->vf32[j] = B[i][j];
		}
		vector_vector_add(col, mA.el[i], mB.el[i], mC.el[i]);
	}
	
	// check
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			printf("[%d,%d] %f %f %f \n", i, j, mA.el[i]->vf32[j], mB.el[i]->vf32[j], mC.el[i]->vf32[j]);
		}
	}
	
	// free allocated memory
	for(i = 0; i < row; i++) {
		free(mA.el[i]);
		free(mB.el[i]);
		free(mC.el[i]);
	}
	
	return 0;
}
