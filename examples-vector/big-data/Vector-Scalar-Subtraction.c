#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"


void vector_scalar_sub(int col, float A[], float num, float B[]) {
	asm(
		"vssub:						\n"
		"	vsetvli		t0, %0, e32	\n"
		"	vlw.v		v0, (%1)	\n"
		"	sub			%0, %0, t0	\n"
		"	slli		t0, t0, 2	\n"
		"	add			%1, %1, t0	\n"
		"	flw			f0, 0(%2)	\n"
		"	vfsub.vf	v1, v0, f0	\n"
		"	vsw.v		v1, (%3)	\n"
		"	add			%3, %3, t0	\n"
		"	bnez		%0, vssub	\n"
		:
		: "r"(col), "r"(&A[0]), "r"(&num), "r"(&B[0])
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
	float num = 12.97;
	
	int i;
	for(i = 0; i < size; i++) {
		A[i] = i;
	}
	
	vector_scalar_sub(size, A, num, B);
	
	return 0;
}
