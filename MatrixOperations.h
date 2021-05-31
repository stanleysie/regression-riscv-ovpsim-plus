#include "vsupport.h"
#define MAX_SIZE 1024

typedef struct {
	v512P mem[MAX_SIZE];
} MATRIX;

void vector_vector_add(int n, v512P A, v512P B, v512P C);
void vector_vector_sub(int n, v512P A, v512P B, v512P C);
void vector_scalar_add(int n, v512P A, float num, v512P C);
void vector_scalar_sub(int n, v512P A, float num, v512P C);