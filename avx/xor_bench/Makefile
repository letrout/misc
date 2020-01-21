all: xor_bench

xor_bench: main.c xor.o xor.h
	${CC} -O3 ${CFLAGS} -o xor_bench main.c xor.o

xor.o: xor.c xor.h
	${CC} -O3 ${CFLAGS} -c xor.c

clean:
	-rm -f xor_bench
	-rm -f *.o
