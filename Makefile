CC=g++
CFLAGS=-c -Wall -Werror -Wextra
all: karatsuba_multiplier

karatsuba_multiplier: karatsuba_multiplier.o
	$(CC) karatsuba_multiplier.o -o $@

karatsuba_multiplier.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o $@

clean:
	rm -f karatsuba_multiplier karatsuba_multiplier.*  karatsuba_tests.* tests

rebuild: clean all