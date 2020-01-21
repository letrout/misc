#include "xor.h"

#define SIZE (64 * 1024)

int main(int argc, char *argv[])
{
	char r1[SIZE+1] = "",
    r2[SIZE+1] = "",
    r3[SIZE+1] = "";
    xor_byte(r1 ,r2, r3, SIZE);
    xor_sse2(r1 ,r2, r3, SIZE);
}