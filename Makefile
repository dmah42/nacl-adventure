# Colossal Cave Adventure Makefile

CFLAGS= -g -Wall -Werror
LDFLAGS=
CC= cc

all: advtxt_to_c

advtxt_to_c: advtxt_to_c.o
	$(CC) -o advtxt_to_c $(CFLAGS) $(LDFLAGS) advtxt_to_c.o

clean:
	rm -f advtxt_to_c.o advtxt_to_c advent1.c advent1.h advent2.c advent2.h \
        advent3.c advent3.h advent4.c advent4.h

