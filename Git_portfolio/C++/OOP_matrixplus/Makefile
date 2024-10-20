CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17
COVFLAGS=--coverage
OS=$(shell uname)
TEST_FLAGS = -lgtest

all: matrix.a

rebuild: clean matrix.a

matrix.a:
	$(CC) $(CFLAGS) -c matrix.cc
	ar rcs matrix.a matrix.o
	rm -rf matrix.o

test: matrix.a
	$(CC) $(CFLAGS) test.cc matrix.a -o test $(TEST_FLAGS)
	./test

clean:
	rm -f matrix.a test gcov*
	rm -rf report
