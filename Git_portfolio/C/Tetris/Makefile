TARGET = SimpleTetris
CC = gcc -Wall -Werror -Wextra

PREF_SRC = ./
PREF_OBJ = ./

SRC = ./brick_game/tetris/S21_backend.c ./gui/cli/S21_frontend.c ./tetris.c

OS = $(shell uname)

ifeq ($(OS),Linux)
    det_OS = -lcheck -lm -lrt -lpthread -lsubunit
else
    det_OS = -lcheck -lm -lpthread
endif

all: $(TARGET)

$(TARGET) : object
	$(CC) S21_backend.o tetris.o S21_frontend.o -o $(TARGET) -lncurses
	./SimpleTetris

install: object
	$(CC) main.o tetris.o cli.o -o $(TARGET) -lncurses
	./SimpleTetris

uninstall:
	rm *.o SimpleTetris

object :
	$(CC) -c $(SRC) 
	# -lncurses

clean :
	rm -rf *.o SimpleTetris dist *.a *.gcda *.gcno report

dist: clean
	mkdir dist
	tar -czvf dist/dist.tar.gz brick_game/tetris/*.c gui/cli/*.c documentation_tetris.md Makefile brick_game/tetris/*.h gui/cli/*.h
.PHONY: dist

add_db_flag:
	$(eval FLAGS += $(DB))
test: 
	$(CC) $(CFLAGS) --coverage ./brick_game/tetris/S21_backend.c tests/test.c -lncurses -o test.a $(det_OS)
	./test.a

gcov_report: test
	./test.a
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html	




