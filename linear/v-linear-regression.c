#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vsupport.h"
#define DATA_SIZE 30

typedef struct {
	float yearsExperience;
	float salary;
} DATA;

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

void vsum_x2(int n, v512P src, v512P des) {
	asm(
		"vsetvli	t0, %0, e32	\n"
		"vlw.v		v0, (%1)	\n"
		"vmul.vv	v1, v0, v0	\n"
		"vsw.v		v1, (%2)	\n"
		:
		: "r"(n), "r"(src), "r"(des)
	);
}

int
main() {
	enableVEC();
	enableFP();
	
	DATA dataset[DATA_SIZE];
	load_data(dataset);
	
	v512P X = malloc(sizeof(v512T));
	v512P Y = malloc(sizeof(v512T));
	v512P SUM_X2 = malloc(sizeof(v512T));
//	v512P SUM_XY = malloc(sizeof(v512T));
	
	int i;
	for(i = 0; i < DATA_SIZE; i++) {
		X->vf8[i] = dataset[i].yearsExperience;
		Y->vf8[i] = dataset[i].salary;
	}
	
	vsum_x2(DATA_SIZE, X, SUM_X2);
	
	for(i = 0; i < DATA_SIZE; i++) {
		printf("%f\n", SUM_X2->vf8[i]);
	}
	
	return 0;
}
