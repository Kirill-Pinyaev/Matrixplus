CC=g++
CFLAGS=-Wall -Werror -Wextra -g -lstdc++ -std=c++17
TFLAGS=-Wall -Werror -Wextra -g -lstdc++ -lgtest -Wuninitialized -pthread

all: s21_matrix_oop.a

clean:
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info
	rm -rf *.dSYM
	rm -rf tests
	rm -rf test
	rm -rf *.a

full_clean: clean
	rm -rf *.o

test: clean
	$(CC) $(TFLAGS) *.cpp -o tests -L/path/to/gtest/lib -lgtest -lgtest_main -Wl,-rpath=/usr/local/include/gtest && ./tests

s21_matrix_oop.a: build_lib

build_lib:
	$(CC) -g -c $(CFLAGS) *.cpp
	ar rcs s21_matrix_oop.a *.o
	ranlib s21_matrix_oop.a
	rm -rf *.o *.dSYM

gcov_report: clean
	$(CC) --coverage s21_*.cpp -o gcov_report -lgtest -lstdc++ 
	./gcov_report
	lcov -t "stest" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/src/index.html

clang_format:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config */*.cpp *.h
	cp ../materials/linters/.clang-format ../.clang-format

	clang-format -i *.cpp
	clang-format -n *.cpp
	clang-format -i *.h
	clang-format -n *.h

leaks:
	gcc -fsanitize=address -g -c $(CFLAGS) *.cpp
	ar rcs s21_matrix_oop.a *.o
	ranlib s21_matrix_oop.a
	$(CC) -fsanitize=address -g $(CFLAGS) s21_matrix_oop.a  $(TFLAGS) -o test
	leaks -atExit -- ./test