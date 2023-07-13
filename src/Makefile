CC = gcc
FLAGS = -Wall -Wextra -g -std=c++17 -Werror
GCOV = --coverage
TEST = *.cc
A = s21_matrix_oop.a
O = *.o
GTEST = gtest
OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lstdc++
else
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest` -lm
endif

all: clean test leaks gcov_report

test:
	$(CC) $(FLAGS) $(TEST) $(LIBFLAGS) -o $(GTEST)
	./$(GTEST)

s21_matrix_oop.a: clean
	$(CC) $(FLAGS) -c $(TEST)
	ar rcs $(A) $(O)

gcov_report: s21_matrix_oop.a
	$(CC) $(FLAGS) $(GCOV) $(TEST) $(A) $(LIBFLAGS) -o $(GTEST)
	./$(GTEST)
	lcov -t "./test" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

leaks:
ifeq ($(OS), Darwin)
	leaks -atExit -- ./$(GTEST)
else
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(GTEST)
endif

style:
	clang-format -n *.cc *.h

clean:
	rm -rf *.a  *.o *.out gtest 
	rm -rf *.info  *.gcda *.gcno -rf *.gcov -rf *dSYM
	rm -rf report/ && rm -rf *.