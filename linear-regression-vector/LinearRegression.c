#include "matrixoperations.h"

void load_data(float X[], float Y[]) {
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
					X[row - 2] = atof(data);
				} else if(column == 1) {
					Y[row - 2] = atof(data);
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
	
	int i, n = 30;
	
	float X[n];
	float Y[n];
	float XX[n];
	float XY[n];
	
	load_data(X, Y);
	
	vector_vector_mul(n, X, X, XX);
	vector_vector_mul(n, X, Y, XY);
	
	float sumX = 0, sumY = 0, sumXX = 0, sumXY = 0;
	for(i = 0; i < n; i++) {
		sumX += X[i];
		sumY += Y[i];
		sumXX += XX[i];
		sumXY += XY[i];
	}
	
	float b = (n*sumXY - sumX*sumY) / (n*sumXX - sumX*sumX);
	float a = (sumY - b*sumX) / n;
	
 	printf("\nEquation of best fit is: y = %0.2fx + %0.2f\n\n", a, b);
	
	return 0;
}
