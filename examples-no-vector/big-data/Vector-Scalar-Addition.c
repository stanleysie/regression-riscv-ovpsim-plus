#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void vector_scalar_add(int col, float A[], float num, float B[]) {
	int i;
	for(i = 0; i < col; i++) {
		B[i] = A[i] + num;
	}
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
	
	vector_scalar_add(size, A, num, B);
	
	return 0;
}
