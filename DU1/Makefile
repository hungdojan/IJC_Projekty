CC=gcc
CFLAGS=-g -std=c11 -pedantic -Wall -Wextra
LDLIBS=-lm
TARGET=primes primes-i steg-decode steg-encode

CFLAGS += -O2
#CFLAGS += -m32
#LDFLAGS += -m32
#CFLAGS += -fsanitize=address -static-libasan
#LDFLAGS += -fsanitize=address -static-libasan

.PHONY: run clean

# Linkovani vsech binarek
all: $(TARGET)

run: $(TARGET)
	ulimit -s 65000 && ./primes
	ulimit -s 65000 && ./primes-i

primes: primes.o eratosthenes.o error.o

primes-i: primes-i.o eratosthenes-i.o error.o bitset-i.o

%-i.o: %.c
	$(CC) -DUSE_INLINE $(CFLAGS) -c -o $@ $<

#-------------------------------------------------------

steg-decode: steg-decode.o eratosthenes.o error.o ppm.o

steg-encode: steg-encode.o eratosthenes.o error.o ppm.o

clean:
	rm -f *.o $(TARGET)
