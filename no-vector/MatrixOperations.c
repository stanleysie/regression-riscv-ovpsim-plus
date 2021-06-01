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
	int i;
	for(i = 0; i < col; i++) {
		C[i] = A[i] + B[i];
	}
}

void vector_vector_sub(int col, float A[], float B[], float C[]) {
	int i;
	for(i = 0; i < col; i++) {
		C[i] = A[i] - B[i];
	}	
}

void vector_vector_mul(int col, float A[], float B[], float C[]) {
	int i;
	for(i = 0; i < col; i++) {
		C[i] = A[i] * B[i];
	}
}

void vector_scalar_add(int col, float A[], float num, float C[]) {
	int i;
	for(i = 0; i < col; i++) {
		C[i] = A[i] + num;
	}
}

void vector_scalar_sub(int col, float A[], float num, float C[]) {
	int i;
	for(i = 0; i < col; i++) {
		C[i] = A[i] - num;
	}
}

void vector_scalar_mul(int col, float A[], float num, float C[]) {
	int i;
	for(i = 0; i < col; i++) {
		C[i] = A[i] * num;
	}
}

void matrix_matrix_add(int row, int col, float A[][col], float B[][col], float C[][col]) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

void matrix_matrix_sub(int row, int col, float A[][col], float B[][col], float C[][col]) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

void matrix_matrix_mul(int row, int col, int len, float A[][len], float B[][col], float C[][col]) {
	int i, j, k;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = 0;
			for(k = 0; k < len; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
}

void matrix_scalar_add(int row, int col, float A[][col], float num, float C[][col]) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = A[i][j] + num;
		}
	}
}

void matrix_scalar_sub(int row, int col, float A[][col], float num, float C[][col]) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = A[i][j] - num;
		}
	}
}

void matrix_scalar_mul(int row, int col, float A[][col], float num, float C[][col]) {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			C[i][j] = A[i][j] * num;
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
