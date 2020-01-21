#include <x86intrin.h>

void xor_sse2(
    char *r1,    /* region 1 */
    char *r2,   /* region 2 */
    char *r3,   /* r3 = r1 ^ r2 */
    int size    /* bytes of region */
    )
{
    __m128i *b1, *b2, *b3;
    int vec_width = 16, j;
    int loops = size / vec_width;
    for(j = 0;j<loops;j++)
    {
        b1 = (__m128i *)(r1 + j*vec_width);
        b2 = (__m128i *)(r2 + j*vec_width);
        b3 = (__m128i *)(r3 + j*vec_width);
        *b3 = _mm_xor_si128(*b1, *b2);
    }
}