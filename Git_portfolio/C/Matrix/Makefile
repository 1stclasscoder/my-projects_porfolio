CC := gcc
CFLAGS := -Wall -Werror -Wextra -std=c11

NAME := s21_matrix

INCDIR := ./
INC += $(INCDIR)/s21_matrix.h 

DECDIR := ./.
HELPDIR := $(DECDIR)/help_functions
MATRIX := $(DECDIR)/matrix_functions

HELP += $(HELPDIR)/s21_check_matrix.c
HELP += $(HELPDIR)/s21_equal_columns_rows.c
HELP += $(HELPDIR)/s21_remove_matrix.c
HELP += $(HELPDIR)/s21_create_matrix.c

MATR += $(MATRIX)/s21_eq_matrix.c 
MATR += $(MATRIX)/s21_sub_matrix.c 
MATR += $(MATRIX)/s21_sum_matrix.c 
MATR += $(MATRIX)/s21_mult_number.c 
MATR += $(MATRIX)/s21_mult_matrix.c 
MATR += $(MATRIX)/s21_transpose.c 
MATR += $(MATRIX)/s21_minor_matrix.c 
MATR += $(MATRIX)/s21_count_determinant.c 
MATR += $(MATRIX)/s21_determinant.c 
MATR += $(MATRIX)/s21_calc_complements.c 
MATR += $(MATRIX)/s21_inverse_matrix.c 

SOURCE := $(HELP) $(MATR)

TARGET := $(NAME).a

SRCEXT := .c
SRC := 
OBJDIR := ./Bin

all: clean $(TARGET)

obj: $(HELP) $(MATR)
	$(CC) $(CFLAGS) -c $^
 

AR := ar
ARFLAGS := rc	
RLIB := ranlib

all: clean $(TARGET)

$(TARGET): obj
	$(AR) $(ARFLAGS) $@ *.o
	$(RLIB) $@ 
	rm -f *.o


TSTDIR := ./Tests
TSTEXT := c
TST := $(shell find $(TSTDIR) -depth -name '*.$(TSTEXT)')
TESTER := test_$(NAME)
CHECK_FLAGS := -lcheck

ifeq ($(shell uname -s),Linux)
	CHECK_FLAGS +=  -lcheck_pic -pthread -lrt -lm -lsubunit
endif

ifeq ($(shell uname -o),Linux)
	CHECK_FLAGS := -lcheck
endif

test: $(TST) $(TARGET)
	$(CC) $(CFLAGS) $^ -o $(TESTER) $(CHECK_FLAGS)
	./$(TESTER) 


GCOV := gcovr
GCOV_CFLAGS := -fprofile-arcs -ftest-coverage --coverage
GCOV_RFLAGS := -r . --html --html-details 
REPORT = report.html
OPEN_REPORT := open $(REPORT)
GCOV_EXTS := *.gcno *.gcda *.gcov *.css *.html

ifeq ($(shell uname -s),Linux)
	OPEN_REPORT := firefox $(REPORT)
endif

gcov_report:
	$(CC) -c $(CFLAGS) $(GCOV_CFLAGS) $(SOURCE)
	$(AR) $(ARFLAGS) $(TARGET) *.o
	$(RLIB) $(TARGET)
	$(CC) -lcheck $(GCOV_CFLAGS) $(TST) $(TARGET) -o $(TESTER) $(CHECK_FLAGS)
	./$(TESTER)
	$(GCOV) $(GCOV_RFLAGS) -o $(REPORT)
	$(OPEN_REPORT)
	

clean:
	rm -f *.o $(TARGET) $(TESTER) logs/*/*.log $(GCOV_EXTS)
	rm -rf *.dSYM

rebuild: clean test

.PHONY: clean all rebuild gcov_report
