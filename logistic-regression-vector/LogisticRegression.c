#include "matrixoperations.h"
#include <math.h>

#define e 2.7182818284

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
	float max[columns];
	float min[columns];

	importCSV("features.csv", (float *)X, rows, columns, true, false);
	print_matrix(10, columns, X, "MATRIX IMPORTED");
	

	findMaxMins(rows, columns, X, max, min);
	print_vector(columns, max ,"MAXIMUMS");
	print_vector(columns, min ,"MINIMUMS");

	//NORMALIZING
	for(int i = 0; i < columns; i++){
		for(int j = 0; j < rows; j++){
			X[j][i] = X[j][i] - min[i];
			X[j][i] = X[j][i] / max[i];
		}
	}

	print_matrix(10, columns, X, "MATRIX IMPORTED");
	
	importCSV("labels.csv", (float *)y, 1, rows, true, false);
	print_vector(10, y, "IMPORTED LABELS");

	initializeWeights(columns, W);
	print_matrix(1, columns, W, "WEIGHTS INITIALIZE");
	
	b = initializeBias();
	printf("BIAS: %.2f\n", b);

	float W_transposed[columns][1];
	matrix_transpose(1, columns, W, W_transposed);
	print_matrix(columns, 1, W_transposed, "WEIGHTS TRANSPOSED");
	
	float prod_xw[rows][1];
	matrix_matrix_mul(rows, columns, 1, X, W_transposed, prod_xw);
	print_matrix(10, 1, prod_xw, "XW MULTIPLIED");
	
	float prod_xw_b[rows][1];
	matrix_scalar_add(rows, 1, prod_xw, b, prod_xw_b);
	print_matrix(10, 1, prod_xw_b, "XWB BIAS ADDED");
	
	float y_hat[rows][1];

	for(int i=0;i<rows;i++){
		y_hat[i][1] = 1/(1+pow(e,prod_xw_b[i][1]));
	}

	print_matrix(10, 1, y_hat, "SIGXWB SIGMOID");
	
	//PREDICTING
	float preds[rows];

	for(int i = 0; i < rows; i++){
		int label = 0;
		if(y_hat[i][1] >= 0.4)
			label = 1;
		
		preds[i] = label;
	}


	print_vector(20, preds, "PREDICTIONS");


	
}



