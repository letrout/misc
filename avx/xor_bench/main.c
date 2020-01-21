#include "xor.h"

#define SIZE (32 * 1024 * 1024)

int main(int argc, char *argv[])
{
	char r1[SIZE+1] = "",
    r2[SIZE+1] = "",
    r3[SIZE+1] = "";
    xor_sse2(r1 ,r2, r3, SIZE);
}