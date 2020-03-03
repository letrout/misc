#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include "util.h"
#include "xor.h"

#define SIZE (64 * 1024)
#define LOOPS 1024 * 1024

char *progname;

static void
usage()
{
	fprintf(stderr, "usage: %s [-b -s buffer size -l loop count]\n",
	    progname);
	fprintf(stderr, "\t-b Include Bytewise xor test <false>\n");
	fprintf(stderr, "\t-s Memory buffer size in Bytes <%d>\n", SIZE);
	fprintf(stderr, "\t-l Loop count <%d>\n", LOOPS);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	char r1[SIZE+1] = "",
    r2[SIZE+1] = "",
    r3[SIZE+1] = "";
    int j;
    double t_before, t_elapsed;
    int bytewise = 0;
    int bufsize = SIZE;
    int loops = LOOPS;
    int ch;

    progname = argv[0];

	while ((ch = getopt(argc, argv, "hb:l:s:")) != -1) {
		switch (ch) {
		case 'b':
		    bytewise = 1;
			break;
		case 'l':
		    loops = atoi(optarg);
			break;
		case 's':
		    bufsize = atoi(optarg);
			break;
		case 'h':
		    usage();
		}
	}

    t_before = gettime();
    for (j=0; j<loops; j++)
    {
        xor_byte(r1 ,r2, r3, SIZE);
    }
    t_elapsed = gettime() - t_before;
    printf("Byte-wise XOR completed: %f\n", t_elapsed);

    t_before = gettime();
    for (j=0; j<loops; j++)
    {
        xor_long(r1 ,r2, r3, SIZE);
    }
    t_elapsed = gettime() - t_before;
    printf("long XOR completed: %f\n", t_elapsed);

#ifdef __SSE2__
    t_before = gettime();
    for (j=0; j<loops; j++)
    {
        xor_sse2(r1 ,r2, r3, SIZE);
    }
    t_elapsed = gettime() - t_before;
    printf("SSE2 XOR completed: %f\n", t_elapsed);
#endif

#ifdef __AVX2__
    t_before = gettime();
    for (j=0; j<loops; j++)
    {
        xor_avx2(r1 ,r2, r3, SIZE);
    }
    t_elapsed = gettime() - t_before;
    printf("AVX2 XOR completed: %f\n", t_elapsed);
#endif

#ifdef __AVX512DQ__
    t_before = gettime();
    for (j=0; j<loops; j++)
    {
        xor_avx512(r1 ,r2, r3, SIZE);
    }
    t_elapsed = gettime() - t_before;
    printf("AVX512 XOR completed: %f\n", t_elapsed);
#endif

}