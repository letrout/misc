void xor_byte(
    char *r1,    /* region 1 */
    char *r2,   /* region 2 */
    char *r3,   /* r3 = r1 ^ r2 */
    int size    /* bytes of region */
    );

void xor_long(
    char *r1,    /* region 1 */
    char *r2,   /* region 2 */
    char *r3,   /* r3 = r1 ^ r2 */
    int size    /* bytes of region */
    );

void xor_sse2(
    char *r1,    /* region 1 */
    char *r2,   /* region 2 */
    char *r3,   /* r3 = r1 ^ r2 */
    int size    /* bytes of region */
    );

void xor_avx2(
    char *r1,    /* region 1 */
    char *r2,   /* region 2 */
    char *r3,   /* r3 = r1 ^ r2 */
    int size    /* bytes of region */
    );

void xor_avx512(
    char *r1,    /* region 1 */
    char *r2,   /* region 2 */
    char *r3,   /* r3 = r1 ^ r2 */
    int size    /* bytes of region */
    );