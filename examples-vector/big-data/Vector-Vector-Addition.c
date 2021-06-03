#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void vector_vector_add(int col, float A[], float B[], float C[]) {
	asm(
		"vvadd:						\n"
		"	vsetvli		t0, %0, e32	\n"
		"	vlw.v		v0, (%1)	\n"
		"	sub			%0, %0, t0	\n"
		"	slli		t0, t0, 2	\n"
		"	add			%1, %1, t0	\n"
		"	vlw.v		v1, (%2)	\n"
		"	add			%2, %2, t0	\n"
		"	vfadd.vv	v2, v0, v1	\n"
		"	vsw.v		v2, (%3)	\n"
		"	add			%3, %3, t0	\n"
		"	bnez		%0, vvadd	\n"
		:
		: "r"(col), "r"(&A[0]), "r"(&B[0]), "r"(&C[0])
	);	
}

int
main() {
	enableVEC();
	enableFP();
	
	int size = 10000000;
	
	// load random data
	float A[size];
	float B[size];
	float C[size];
	
	int i;
	for(i = 0; i < size; i++) {
		A[i] = i;
		B[i] = 0.5*i;
	}
	
	vector_vector_add(size, A, B, C);
	
	return 0;
}
