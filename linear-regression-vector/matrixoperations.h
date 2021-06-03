#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void enableVEC();
void enableFP();

int importCSV(const char* path, float *matrix, int rows, int columns, bool strict, bool verbose);

void vector_vector_add(int col, float A[], float B[], float C[]) ;

void vector_vector_sub(int col, float A[], float B[], float C[]) ;

void vector_vector_mul(int col, float A[], float B[], float C[]) ;

void vector_scalar_add(int col, float A[], float num, float B[]) ;

void vector_scalar_sub(int col, float A[], float num, float B[]) ;

void vector_scalar_mul(int col, float A[], float num, float B[]) ;

void print_vector(int col, float V[], char s[]) ;

void matrix_matrix_add(int row, int col, float A[][col], float B[][col], float C[][col]) ;

void matrix_matrix_sub(int row, int col, float A[][col], float B[][col], float C[][col]) ;

void matrix_matrix_mul(int row, int col, int len, float A[][len], float B[][col], float C[][col]) ;

void matrix_scalar_add(int row, int col, float A[][col], float num, float B[][col]) ;

void matrix_scalar_sub(int row, int col, float A[][col], float num, float B[][col]) ;

void matrix_scalar_mul(int row, int col, float A[][col], float num, float B[][col]) ;

void matrix_transpose(int row, int col, float A[][col], float B[][row]) ;

void print_matrix(int row, int col, float M[][col], char s[]) ;

void initializeWeights(int num, float weights[][num]);

float initializeBias();