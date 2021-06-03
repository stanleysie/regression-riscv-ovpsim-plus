#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "vsupport.h"
#include <math.h>

#define e 2.718281828459

int importCSV(const char* path, float *matrix, int rows, int columns, bool strict, bool verbose){
    char buffer[1024] ;
    char *record,*line;
    int i=0,j=0;
    FILE *fstream = fopen(path,"r");
    if(fstream == NULL){
        printf("file opening failed\n");
        return -1;
    }

 
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL){
        if(i>=rows){
            printf("rows exceeded row limit\n");
            return -1;
        }
        j=0;
        record = strtok(line,",");
        while(record != NULL){
            if(j>=columns){
                printf("columns exceeded column limit\n");
                return -1;
            }

            *((matrix+i*columns) + j) = atof(record);
                
            if(verbose){
                printf("%f, ", atof(record)); 
            }
            record = strtok(NULL,",");
            j++;
        }
        if(strict && j != columns){
            printf("columns should exactly be column limit: %d", columns);
            return -1;
        }

        if(verbose){
            printf("%d, \n", i);
        }
         
        i++;
        
    }
    return 0;
}

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

void vector_scalar_add(int col, float A[], float num, float B[]) {
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
		: "r"(col), "r"(&A[0]), "r"(&num), "r"(&B[0])
	);
}

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

void vector_scalar_mul(int col, float A[], float num, float B[]) {
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
		: "r"(col), "r"(&A[0]), "r"(&num), "r"(&B[0])
	);
}

void print_vector(int col, float V[], char s[]) {
	int i;
	printf("\n%s\n", s);
	for(i = 0; i < col; i++) {
		printf("%.2f\t", V[i]);
	}
	printf("\n");
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

void matrix_scalar_add(int row, int col, float A[][col], float num, float B[][col]) {
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
			: "r"(col), "r"(&A[i][0]), "r"(&num), "r"(&B[i][0])
		);
	}
}

void matrix_scalar_sub(int row, int col, float A[][col], float num, float B[][col]) {
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
			: "r"(col), "r"(&A[i][0]), "r"(&num), "r"(&B[i][0])
		);
	}
}

void matrix_scalar_mul(int row, int col, float A[][col], float num, float B[][col]) {
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
			: "r"(col), "r"(&A[i][0]), "r"(&num), "r"(&B[i][0])
		);
	}
}

void matrix_transpose(int row, int col, float A[][col], float B[][row]) {
	int i;
	for(i = 0; i < row; i++) {
		asm(
			"ltrans:					\n"
			"	vsetvli		t0, %0, e32	\n"
			"	vlw.v		v0, (%1)	\n"
			"	sub			%0, %0, t0	\n"
			"	slli		t0, t0, 2	\n"
			"	add			%1, %1, t0	\n"
			"	vssw.v		v0, (%2), %3\n"
			"	add			%2, %2, t0	\n"
			"	bnez		%0, ltrans	\n"
			:
			: "r"(col), "r"(&A[i][0]), "r"(&B[0][i]), "r"(row*4)
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

void initializeWeights(int num, float weights[][num]){
    int i=0;
    srand((unsigned int)time(NULL));

    for(i=0;i<num;i++){
        float x = (rand()%1000000);
        x = x/1000000;
        weights[0][i] = x;
    }
}

float initializeBias(){
    float x = (rand()%1000000);
    return x/1000000;
}

void getGradientWeights(int row, int col, float X[][col], float y[row], float y_hat[row] ){
	float Xtransposed[row][col];
	float loss[row];
	matrix_transpose(row, col, X, Xtransposed);
	vector_vector_sub(row, y, y_hat, loss);
	// matrix_scalar_mul(row, col, X, );
}

void findMaxMins(int rows, int cols, float mat[][cols], float max[], float min[]){
    for (int i = 0; i < cols; i++) {
        float maxm = mat[0][i];
		float minm = mat[0][i];
        for (int j = 1; j < rows; j++) {
            if (mat[j][i] > maxm){
                maxm = mat[j][i];
			}
			if (mat[j][i] < minm){
				minm = mat[j][i];
			}
        }
        max[i] = maxm;
		min[i] = minm;
    }
}

// void applySigmoid();
// void loss();

int main() {
	enableVEC();
	enableFP();

		int rows = 303, columns = 13;
		float X[rows][columns];
		float y[rows];
		float W[1][columns];
		float b;
		// float max[columns];
		// float min[columns];

		importCSV("features.csv", (float *)X, rows, columns, true, false);
		print_matrix(10, columns, X, "MATRIX IMPORTED");
		
		// findMaxMins(rows, columns, X, max, min);
		// print_vector(columns, max ,"MAXIMUMS");
		// print_vector(columns, min ,"MINIMUMS");

		// for(int i=0; i<)

		importCSV("labels.csv", (float *)y, 1, rows, true, false);
		print_vector(10, y, "IMPORTED FEATURES");

		initializeWeights(columns, W);
		print_matrix(1, columns, W, "WEIGHTS INITIALIZE");
		
		b = initializeBias();
		printf("BIAS: %.2f\n", b);

		float W_transposed[columns][1];
		matrix_transpose(1, columns, W, W_transposed);
		print_matrix(columns, 1, W_transposed, "WEIGHTS TRANSPOSED");
		for(int epochs=0; epochs<100;epochs++){
			float prod_xw[rows][1];
			matrix_matrix_mul(rows, columns, 1, X, W_transposed, prod_xw);
			print_matrix(10, 1, prod_xw, "XW MULTIPLIED");
			// float matprod[];
			
			float prod_xw_b[rows][1];
			matrix_scalar_add(rows, 1, prod_xw, b, prod_xw_b);
			print_matrix(10, 1, prod_xw_b, "XWB BIAS ADDED");
			
		}
		// float y_hat[rows][1];

		// for(int i=0;i<rows;i++){
		// 	y_hat[i][1] = 1/(1+pow(e,prod_xw_b[i][1]));

		// print_matrix(10, 1, y_hat, "SIGXWB SIGMOID");

	
}



