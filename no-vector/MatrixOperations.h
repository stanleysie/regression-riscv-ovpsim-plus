#include "vsupport.h"
#define MAX_SIZE 1024

typedef struct {
	v512P mem[MAX_SIZE];
} MATRIX;

void vector_vector_add(int row, int col, MATRIX A, v512P B, MATRIX C);
void vector_vector_sub(int row, int col, MATRIX A, v512P B, MATRIX C);
void vector_scalar_add(int row, int col, MATRIX A, float num, MATRIX C);
void vector_scalar_sub(int row, int col, MATRIX A, float num, MATRIX C);
void vector_scalar_mul(int row, int col, MATRIX A, float num, MATRIX C);
