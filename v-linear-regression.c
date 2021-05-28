#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vsupport.h"

void vvmulint32(int n, v512P x, v512P y, v512P z) {
	// sample program
    asm(
    	"vsetvli t0, %0, e32	\n"	// Set vector length based on 32-bit vectors
        "vlw.v v0, (%1)			\n" // load the first vector
        "vlw.v v1, (%2)			\n" // load the second vector
        "vmul.vv v2, v0, v1		\n" // perform vector multiplication
        "vsw.v v2, (%3)			\n" // store to the third vector
        :
        : "r" (n), "r" (x), "r" (y), "r" (z)
    );
}

int
main() {
	enableVEC();
	
	v512P a = malloc(sizeof(v512T));
    v512P b = malloc(sizeof(v512T));
    v512P c = malloc(sizeof(v512T));
    
    int i, j;
    for (j = 0; j < 500000; j++) {
        for (i = 0; i < VEC32; i++) {
            a->vu32[i] = rand();
            b->vu32[i] = rand();
        }

        // v2 = v0 * v1;
        vvmulint32(VEC32, a, b, c);
    }
	
	return 0;
}
