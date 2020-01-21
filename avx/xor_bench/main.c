#include <stdio.h>
#include <sys/time.h>

#include "util.h"
#include "xor.h"

#define SIZE (64 * 1024)
#define LOOPS 1024 * 1024

int main(int argc, char *argv[])
{
	char r1[SIZE+1] = "",
    r2[SIZE+1] = "",
    r3[SIZE+1] = "";
    int j;
    double t_before, t_elapsed;

    t_before = gettime();
    for (j=0; j<LOOPS; j++)
    {
        xor_byte(r1 ,r2, r3, SIZE);
    }
    t_elapsed = gettime() - t_before;
    printf("Byte-wise XOR completed: %f\n", t_elapsed);

    t_before = gettime();
    for (j=0; j<LOOPS; j++)
    {
        xor_sse2(r1 ,r2, r3, SIZE);
    }
    t_elapsed = gettime() - t_before;
    printf("SSE2 XOR completed: %f\n", t_elapsed);

#ifdef __AVX2__
    t_before = gettime();
    for (j=0; j<LOOPS; j++)
    {
        xor_avx2(r1 ,r2, r3, SIZE);
    }
    t_elapsed = gettime() - t_before;
    printf("AVX2 XOR completed: %f\n", t_elapsed);
#endif

#ifdef __AVX512DQ__
    t_before = gettime();
    for (j=0; j<LOOPS; j++)
    {
        xor_avx512(r1 ,r2, r3, SIZE);
    }
    t_elapsed = gettime() - t_before;
    printf("AVX512 XOR completed: %f\n", t_elapsed);
#endif

}