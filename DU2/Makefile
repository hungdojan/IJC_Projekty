CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -fPIC
MODULES=htab_item_init.o htab_item_free.o htab_hash_function.o htab_init.o htab_move.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o
TARGET=wordcount wordcount-dynamic libhtab.so tail libhtab.a
LOGIN=xdohun00

CFLAGS+=-O2
#CFLAGS+=-DHASHTEST
#CFLAGS+=-DMOVETEST

.PHONY: clean all zip

# --------------------------------------

all: $(TARGET)

tail: tail.o

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) -o $@ wordcount.o io.o -L. -lhtab

wordcount: wordcount.o io.o libhtab.a
	$(CC) -static -o $@ wordcount.o io.o -L. -lhtab

libhtab.so: $(MODULES)
	$(CC) $(CFLAGS) -shared -o $@ $^

libhtab.a: $(MODULES)
	ar crs $@ $^

# -------------------------------------

pack:
	zip $(LOGIN) *.h *.c Makefile

upload:
	scp $(LOGIN).zip $(LOGIN)@eva.fit.vutbr.cz:/homes/eva/xd/$(LOGIN)/ijc

clean:
	rm -f *.o $(TARGET)

