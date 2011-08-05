# Colossal Cave Adventure Makefile

DATA= advent1.txt advent2.txt advent3.txt advent4.txt

CFLAGS= -g -Wall -Werror
LDFLAGS=
CC= cc

all: advent0 advtxt_to_c

advent0: advent0.o
	$(CC) -o advent0 $(CFLAGS) $(LDFLAGS) advent0.o

advtxt_to_c: advtxt_to_c.o
	$(CC) -o advtxt_to_c $(CFLAGS) $(LDFLAGS) advtxt_to_c.o

clean:
	rm -f advent0.o *.err advent0 advtext.h advtxt_to_c.o advtxt_to_c

