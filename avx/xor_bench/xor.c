#include <immintrin.h> //avx2

void xor_byte(
    char *r1,   /* region 1 */
    char *r2,   /* region 2 */
    char *r3,   /* r3 = r1 ^ r2 */
    int size    /* bytes of region */
)
{
    int j;
    for(j=0; j<size; j++)
    {
        r3[j] = r1[j] ^ r2[j];
    }
}

void xor_long(
    char *r1,   /* region 1 */
    char *r2,   /* region 2 */
    char *r3,   /* r3 = r1 ^ r2 */
    int size    /* bytes of region */
)
{
    int vec_width = sizeof(long), j;
    int loops = size / vec_width;
    for(j=0; j<loops; j++)
    {
        r3[j] = r1[j] ^ r2[j];
    }
}

#ifdef __SSE2__
void xor_sse2(
    char *r1,   /* region 1 */
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
#endif

#ifdef __AVX2__
void xor_avx2(
    char *r1,   /* region 1 */
    char *r2,   /* region 2 */
    char *r3,   /* r3 = r1 ^ r2 */
    int size    /* bytes of region */
    )
{
    __m256i *b1, *b2, *b3;
    int vec_width = 32, j;
    int loops = size / vec_width;
    for(j = 0;j<loops;j++)
    {
        b1 = (__m256i *)(r1 + j*vec_width);
        b2 = (__m256i *)(r2 + j*vec_width);
        b3 = (__m256i *)(r3 + j*vec_width);
        *b3 = _mm256_xor_si256(*b1, *b2);
    }
}
#endif

#ifdef __AVX512DQ__
void xor_avx512(
    char *r1,   /* region 1 */
    char *r2,   /* region 2 */
    char *r3,   /* r3 = r1 ^ r2 */
    int size    /* bytes of region */
    )
{
    __m512i *b1, *b2, *b3;
    int vec_width = 64, j;
    int loops = size / vec_width;
    for(j = 0;j<loops;j++)
    {
        b1 = (__m512i *)(r1 + j*vec_width);
        b2 = (__m512i *)(r2 + j*vec_width);
        b3 = (__m512i *)(r3 + j*vec_width);
        *b3 = _mm512_xor_epi32(*b1, *b2);
    }
}
#endif