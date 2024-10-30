CC= g++ 
CFLAGS= -Wall -Wextra -Werror
STANDART= -std=c++17
TESTFLAGS=-lgtest
TESTFILES= tests/*.cpp

all: test

test: clean
	$(CC) $(CFLAGS) $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test

clean:
	rm -rf *.out *.o s21_matrix_oop.a *.gcda *.gcno *.info test main
	rm -rf report