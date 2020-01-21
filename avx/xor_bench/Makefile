all: xor_bench

xor_bench: main.c xor.o xor.h util.c util.o util.h
	${CC} -O3 ${CFLAGS} -o xor_bench main.c xor.o util.o

xor.o: xor.c xor.h
	${CC} -O3 ${CFLAGS} -c xor.c

util.o: util.c util.h
	${CC} -O3 ${CFLAGS} -c util.c

clean:
	-rm -f xor_bench
	-rm -f *.o
