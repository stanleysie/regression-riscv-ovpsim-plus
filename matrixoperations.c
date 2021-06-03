#include "vsupport.h"
#include "matrixoperations.h"

// Need to enable the Vector Context Status in mstatus
void enableVEC() {
    asm(
        "    csrr      t0, mstatus       \n"
        "    li        t1, (0x1 << 23)   \n"
        "    or        t1, t1, t0        \n"
        "    csrw      mstatus, t1       \n"
    );
    return;
}

void enableFP() {
    // enable floating point instructions
    asm (
        "    csrr s4, mstatus  \n"
        "    li   s5, 1<<13    \n"
        "    or   s4, s4, s5   \n"
        "    csrw mstatus, s4  \n"
    );
}

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
        float x = (rand()%10000000);
        x -= 5000000;
        x = x/10000000;
        weights[0][i] = x;
    }
}

float initializeBias(){
    srand((unsigned int)time(NULL));
    float x = (rand()%10000000);
    x -= 5000000;
    return x/10000000;
}