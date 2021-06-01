#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsupport.h"
#include "MatrixOperations.h"

#define DATA_SIZE 30

typedef struct {
	float yearsExperience;
	float salary;
} DATA;

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

void vector_vector_sub(int col, float A[], float B[], float C[]) {
	asm(
		"vvsub:						\n"
		"	vsetvli		t0, %0, e32	\n"
		"	vlw.v		v0, (%1)	\n"
		"	sub			%0, %0, t0	\n"
		"	slli		t0, t0, 2	\n"
		"	add			%1, %1, t0	\n"
		"	vlw.v		v1, (%2)	\n"
		"	add			%2, %2, t0	\n"
		"	vfsub.vv	v2, v0, v1	\n"
		"	vsw.v		v2, (%3)	\n"
		"	add			%3, %3, t0	\n"
		"	bnez		%0, vvsub	\n"
		:
		: "r"(col), "r"(&A[0]), "r"(&B[0]), "r"(&C[0])
	);	
}

void vector_vector_mul(int col, float A[], float B[], float C[]) {
	asm(
		"vvmul:						\n"
		"	vsetvli		t0, %0, e32	\n"
		"	vlw.v		v0, (%1)	\n"
		"	sub			%0, %0, t0	\n"
		"	slli		t0, t0, 2	\n"
		"	add			%1, %1, t0	\n"
		"	vlw.v		v1, (%2)	\n"
		"	add			%2, %2, t0	\n"
		"	vfmul.vv	v2, v0, v1	\n"
		"	vsw.v		v2, (%3)	\n"
		"	add			%3, %3, t0	\n"
		"	bnez		%0, vvmul	\n"
		:
		: "r"(col), "r"(&A[0]), "r"(&B[0]), "r"(&C[0])
	);	
}

void vector_scalar_add(int col, float A[], float num, float C[]) {
	asm(
		"vsadd:						\n"
		"	vsetvli		t0, %0, e32	\n"
		"	vlw.v		v0, (%1)	\n"
		"	sub			%0, %0, t0	\n"
		"	slli		t0, t0, 2	\n"
		"	add			%1, %1, t0	\n"
		"	flw			f0, 0(%2)	\n"
		"	vfadd.vf	v1, v0, f0	\n"
		"	vsw.v		v1, (%3)	\n"
		"	add			%3, %3, t0	\n"
		"	bnez		%0, vsadd	\n"
		:
		: "r"(col), "r"(&A[0]), "r"(&num), "r"(&C[0])
	);
}

void vector_scalar_sub(int col, float A[], float num, float C[]) {
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
		: "r"(col), "r"(&A[0]), "r"(&num), "r"(&C[0])
	);
}

void vector_scalar_mul(int col, float A[], float num, float C[]) {
	asm(
		"vsmul:						\n"
		"	vsetvli		t0, %0, e32	\n"
		"	vlw.v		v0, (%1)	\n"
		"	sub			%0, %0, t0	\n"
		"	slli		t0, t0, 2	\n"
		"	add			%1, %1, t0	\n"
		"	flw			f0, 0(%2)	\n"
		"	vfmul.vf	v1, v0, f0	\n"
		"	vsw.v		v1, (%3)	\n"
		"	add			%3, %3, t0	\n"
		"	bnez		%0, vsmul	\n"
		:
		: "r"(col), "r"(&A[0]), "r"(&num), "r"(&C[0])
	);
}

void matrix_matrix_add(int row, int col, float A[][col], float B[][col], float C[][col]) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"lvadd:						\n"
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
			"	bnez		%0, lvadd	\n"
			:
			: "r"(col), "r"(&A[i][0]), "r"(&B[i][0]), "r"(&C[i][0])
		);	
	}
}

void matrix_matrix_sub(int row, int col, float A[][col], float B[][col], float C[][col]) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"lvsub:						\n"
			"	vsetvli		t0, %0, e32	\n"
			"	vlw.v		v0, (%1)	\n"
			"	sub			%0, %0, t0	\n"
			"	slli		t0, t0, 2	\n"
			"	add			%1, %1, t0	\n"
			"	vlw.v		v1, (%2)	\n"
			"	add			%2, %2, t0	\n"
			"	vfsub.vv	v2, v0, v1	\n"
			"	vsw.v		v2, (%3)	\n"
			"	add			%3, %3, t0	\n"
			"	bnez		%0, lvsub	\n"
			:
			: "r"(col), "r"(&A[i][0]), "r"(&B[i][0]), "r"(&C[i][0])
		);	
	}
}

void matrix_matrix_mul(int row, int col, int len, float A[][len], float B[][col], float C[][col]) {
	float tempC[row][col][len];
	
	int i, j, k;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			asm(
				"lvmul:						\n"
				"	vsetvli		t0, %0, e32	\n"
				"	vlw.v		v0, (%1)	\n"
				"	sub			%0, %0, t0	\n"
				"	slli		t0, t0, 2	\n"
				"	add			%1, %1, t0	\n"
				"	vlsw.v		v1, (%2), %4\n"
				"	add			%2, %2, t0	\n"
				"	vfmul.vv	v2, v0, v1	\n"
				"	vsw.v		v2, (%3)	\n"
				"	add			%3, %3, t0	\n"
				"	bnez		%0, lvmul	\n"
				:
				: "r"(len), "r"(&A[i][0]), "r"(&B[0][j]), "r"(&tempC[i][j][0]), "r"(col*4)
			);		
		}
	}
	
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			float sum = 0;
			for(k = 0; k < col; k++) {
				sum += tempC[i][j][k];
			}
			C[i][j] = sum;
		}
	}
}

void matrix_scalar_add(int row, int col, float A[][col], float num, float C[][col]) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"lsadd:						\n"
			"	vsetvli		t0, %0, e32	\n"
			"	vlw.v		v0, (%1)	\n"
			"	sub			%0, %0, t0	\n"
			"	slli		t0, t0, 2	\n"
			"	add			%1, %1, t0	\n"
			"	flw			f0, 0(%2)	\n"
			"	vfadd.vf	v1, v0, f0	\n"
			"	vsw.v		v1, (%3)	\n"
			"	add			%3, %3, t0	\n"
			"	bnez		%0, lsadd	\n"
			:
			: "r"(col), "r"(&A[i][0]), "r"(&num), "r"(&C[i][0])
		);
	}
}

void matrix_scalar_sub(int row, int col, float A[][col], float num, float C[][col]) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"lssub:						\n"
			"	vsetvli		t0, %0, e32	\n"
			"	vlw.v		v0, (%1)	\n"
			"	sub			%0, %0, t0	\n"
			"	slli		t0, t0, 2	\n"
			"	add			%1, %1, t0	\n"
			"	flw			f0, 0(%2)	\n"
			"	vfsub.vf	v1, v0, f0	\n"
			"	vsw.v		v1, (%3)	\n"
			"	add			%3, %3, t0	\n"
			"	bnez		%0, lssub	\n"
			:
			: "r"(col), "r"(&A[i][0]), "r"(&num), "r"(&C[i][0])
		);
	}
}

void matrix_scalar_mul(int row, int col, float A[][col], float num, float C[][col]) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"lsmul:						\n"
			"	vsetvli		t0, %0, e32	\n"
			"	vlw.v		v0, (%1)	\n"
			"	sub			%0, %0, t0	\n"
			"	slli		t0, t0, 2	\n"
			"	add			%1, %1, t0	\n"
			"	flw			f0, 0(%2)	\n"
			"	vfmul.vf	v1, v0, f0	\n"
			"	vsw.v		v1, (%3)	\n"
			"	add			%3, %3, t0	\n"
			"	bnez		%0, lsmul	\n"
			:
			: "r"(col), "r"(&A[i][0]), "r"(&num), "r"(&C[i][0])
		);
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

void load_data(DATA *dataset) {
	FILE *fp;
	
	fp = fopen("linear_dataset.csv", "r");
	if (fp == NULL) {
		printf("Error in reading file.\n");
	} else {
		char line[1024];
		int row = 0, column = 0;
		
		while(fgets(line, sizeof(line), fp)) {
			column = 0;
	        row++;
	        
			if(row == 0) continue;
		
			char *data = strtok(line, ",");
			
			while(data) {
				if(column == 0) {
					dataset[row - 2].yearsExperience = atof(data);
				} else if(column == 1) {
					dataset[row - 2].salary = atof(data);
				}
				data = strtok(NULL, ", ");
				column++;
			}
		}
		
		fclose(fp);
	}
}

int
main() {
	enableVEC();
	enableFP();
	
	DATA dataset[DATA_SIZE];
	load_data(dataset);
	
	float X[DATA_SIZE];
	float Y[DATA_SIZE];
	float XX[DATA_SIZE];
	float XY[DATA_SIZE];
	
	int i;
	for(i = 0; i < DATA_SIZE; i++) {
		X[i] = dataset[i].yearsExperience;
		Y[i] = dataset[i].salary;
	}
	
	vector_vector_mul(DATA_SIZE, X, X, XX);
	vector_vector_mul(DATA_SIZE, X, Y, XY);
	
	float sumX = 0, sumY = 0, sumXX = 0, sumXY = 0;
	for(i = 0; i < DATA_SIZE; i++) {
		sumX += X[i];
		sumY += Y[i];
		sumXX += XX[i];
		sumXY += XY[i];
	}
	
	float b = (DATA_SIZE*sumXY - sumX*sumY) / (DATA_SIZE*sumXX - sumX*sumX);
	float a = (sumY - b*sumX) / DATA_SIZE;
	
	printf("\nValues are: a = %0.2f and b = %0.2f\n",a,b);
 	printf("Equation of best fit is: y = %0.2f + %0.2fx\n\n",a,b);
	
	return 0;
}
