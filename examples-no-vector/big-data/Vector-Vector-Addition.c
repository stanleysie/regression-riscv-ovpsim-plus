#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"

void vector_vector_add(int col, float A[], float B[], float C[]) {
	int i;
	for(i = 0; i < col; i++) {
		C[i] = A[i] + B[i];
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
	float C[size];
	
	int i;
	for(i = 0; i < size; i++) {
		A[i] = i;
		B[i] = 0.5*i;
	}
	
	vector_vector_add(size, A, B, C);
	
	return 0;
}
