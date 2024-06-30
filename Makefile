CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -x c++ -std=c++17 -pedantic
LIB_ADDITIONAL = -pthread
SOURCE = $(wildcard s21_*.cpp)
HEADER = $(wildcard s21_*.h)
OBJECTS = ${patsubst %.cpp,%.o, ${SOURCE}}
STATIC_LIB = s21_matrix_oop.a
TEST_DIR := tests
TEST_EXEC := test
TEST_MODULES_DIR = tests/classes tests/suites
TEST_SOURCE = $(shell find ${TEST_DIR} ${TEST_MODULES_DIR} -maxdepth 1 -name "*.cpp")
TEST_HEADERS = $(shell find ${TEST_DIR} ${TEST_MODULES_DIR} -maxdepth 1 -name "*.h")
TEST_OBJECTS = ${patsubst %.cpp,%.o, ${TEST_SOURCE}}
TEST_LIBS = -lgtest ${LIB_ADDITIONAL}
REPORT_DIR = report
LIBS_GCOV = -lgcov

UNAME_S := $(shell uname -s)

all: build

build: clean ${STATIC_LIB}

${STATIC_LIB}: ${SOURCE}
	${CXX} ${CXXFLAGS} -c ${SOURCE}
	ar rc $@ ${OBJECTS}
	ranlib $@ 

${TEST_EXEC}: ${STATIC_LIB} 
	@${CXX} ${TEST_LIBS} ${TEST_SOURCE} -l:${STATIC_LIB} -o ${TEST_EXEC}

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n ${SOURCE} ${HEADER} ${TEST_SOURCE}
	rm ./.clang-format

clangi:
	cp ../materials/linters/.clang-format .
	clang-format -i ${SOURCE} ${HEADER} ${TEST_SOURCE}
	rm ./.clang-format

cppcheck:
	cppcheck --enable=all --force --suppress=missingIncludeSystem --language=c++ --std=c++17 ${SOURCE} ${HEADER}

valgrind:
	valgrind --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(TEST_EXEC)



clean:
	rm -rf *.gch
	rm -rf *.a
	rm -rf ${OBJECTS}

.PHONY: all build clean cppcheck clangf clang valgrind

show:
	echo ${TEST_OBJECTS}