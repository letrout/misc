#include <getopt.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include "util.h"
#include "xor.h"

#define SIZE (64 * 1024)
#define LOOPS 1024 * 1024

char *progname;
static int run_bytewise = 0;
static int run_long = 0;
static int run_sse2 = 0;
static int run_avx2 = 0;
static int run_avx512 = 0;

static void
usage()
{
	fprintf(stderr, "usage: %s [-b -s buffer size -l loop count]\n",
	    progname);
	fprintf(stderr, "\t-s Memory buffer size in Bytes <%d>\n", SIZE);
	fprintf(stderr, "\t-l Loop count <%d>\n", LOOPS);
    fprintf(stderr, "\t--run_bytewise Include Bytewise xor test <false>\n");
    fprintf(stderr, "\t--run_long Include long int xor test <false>\n");
    fprintf(stderr, "\t--run_sse2 Include SSE2 xor test <false>\n");
    fprintf(stderr, "\t--run_avx2 Include AVX2 xor test <false>\n");
    fprintf(stderr, "\t--run_avx512 Include AVX512 xor test <false>\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int j;
    double t_before, t_elapsed;
    int bufsize = SIZE;
    int loops = LOOPS;
    int c;

    progname = argv[0];

    while (1) {
        static struct option long_options[] = {
            {"run_bytewise", no_argument, &run_bytewise, 1},
            {"run_long", no_argument, &run_long, 1},
            {"run_sse2", no_argument, &run_sse2, 1},
            {"run_avx2", no_argument, &run_avx2, 1},
            {"run_avx512", no_argument, &run_avx512, 1},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;
        c = getopt_long (argc, argv, "hl:s:", long_options, &option_index);
        if (c == -1)
            break;
        switch (c) {
            case 0:
                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;
            case 'l':
		        loops = atoi(optarg);
			    break;
            case 's':
		        bufsize = atoi(optarg);
			    break;
		    case 'h':
		        usage();
            default:
                abort();
        }
    }

    char r1[bufsize+1],
    r2[bufsize+1],
    r3[bufsize+1];

    if (run_bytewise)
    {
        t_before = gettime();
        for (j=0; j<loops; j++)
        {
            xor_byte(r1 ,r2, r3, bufsize);
        }
        t_elapsed = gettime() - t_before;
        printf("Byte-wise XOR completed: %f\n", t_elapsed);
    }

    if (run_long)
    {
        t_before = gettime();
        for (j=0; j<loops; j++)
        {
            xor_long(r1 ,r2, r3, bufsize);
        }
        t_elapsed = gettime() - t_before;
        printf("long XOR completed: %f\n", t_elapsed);
    }

#ifdef __SSE2__
    if (run_sse2)
    {
        t_before = gettime();
        for (j=0; j<loops; j++)
        {
            xor_sse2(r1 ,r2, r3, bufsize);
        }
        t_elapsed = gettime() - t_before;
        printf("SSE2 XOR completed: %f\n", t_elapsed);
    }
#endif

#ifdef __AVX2__
    if (run_avx2)
    {
        t_before = gettime();
        for (j=0; j<loops; j++)
        {
            xor_avx2(r1 ,r2, r3, bufsize);
        }
        t_elapsed = gettime() - t_before;
        printf("AVX2 XOR completed: %f\n", t_elapsed);
    }
#endif

#ifdef __AVX512DQ__
    if (run_avx512)
    {
        t_before = gettime();
        for (j=0; j<loops; j++)
        {
            xor_avx512(r1 ,r2, r3, bufsize);
        }
        t_elapsed = gettime() - t_before;
        printf("AVX512 XOR completed: %f\n", t_elapsed);
    }
#endif

}