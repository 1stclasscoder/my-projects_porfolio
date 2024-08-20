GCC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11 
LDFLAGS = -Wall -Werror -Wextra -std=c11
SOURCE = $(filter-out ./test/test_s21_string.c, $(wildcard s21_*.c))
HEADER = $(wildcard s21_*.h)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})
TESTS_SOURCE = ./test/test_s21_string.c
UNAME_S := $(shell uname -s)
UNAME_O := $(shell uname -o)
BIN = s21_string_test

GCOV = gcovr
GCOV_FLAGS = -fprofile-arcs -ftest-coverage --coverage
REPORT_FILE = report.html
OPEN_REPORT = open $(REPORT_FILE)

ifeq ($(UNAME_S),Linux)
	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread 
	BREW = .
	OPEN_REPORT = firefox $(REPORT_FILE)
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB =
	BREW := ${HOME}/homebrew
endif

ifeq ($(UNAME_O), Linux)
	ADD_LIB += -DALPINE
endif

PATH := $(BREW)/bin:$(PATH)

all: s21_string.a

s21_string.a: clean ${SOURCE} 
	$(CC) $(CFLAGS) $(ADD_LIB) $(SOURCE)
	ar rc $@ $(OBJECTS)
	ranlib $@
	cp $@ lib$@

test: ${TESTS_SOURCE} s21_string.a
	${CC} $(LDFLAGS) -o $(BIN) $^ -lcheck -lm
	./$(BIN)

gcov_report:
	gcc -c -Wall -Werror -Wextra  -fprofile-arcs -ftest-coverage --coverage *.c
	ar cr s21_string.a *.o
	gcc -o $(BIN) $(LDFLAGS) -lcheck $(ADD_LIB) -Wall -Werror -Wextra -fprofile-arcs -ftest-coverage --coverage test/test_s21_string.c -L. s21_string.a
	./$(BIN)
	gcovr -r . --html --html-details -o report.html 
	$(OPEN_REPORT)


valgrind: clean
	make s21_string.a
	gcc -g ${TESTS_SOURCE} s21_string.a -o $(BIN) -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt ./$(BIN)

style: clean
	clang-format -i -style='{BasedOnStyle: Google}' *.c  *.h */*.c

style_check: clean
	clang-format -i -style='{BasedOnStyle: Google}' *.c  *.h */*.c
	
clean:
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf s21_test
	-rm -rf RESULT_VALGRIND.txt
	-rm -rf $(BIN)
	-rm -rf *.css *.html

.PHONY: all clean check lcov
