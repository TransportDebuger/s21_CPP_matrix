CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -x c++ -std=c++17 -c
LIB_ADDITIONAL = -pthread
SOURCE = s21_matrix_oop.cpp
HEADER = $(wildcard s21_*.h)
OBJECTS = ${SOURCE:%.cpp=%.o}
STATIC_LIB = s21_matrix_oop.a
STATIC_LIB_GCOV = s21_matrix_oop_gcov.a
TEST_DIR := tests
TEST_EXEC := test
OBJ_DIR := obj
TEST_OBJ_DIR = ${OBJ_DIR}/tests
TEST_MODULES_DIR = tests/classes tests/suites ${TEST_DIR}
TEST_SOURCE = $(notdir $(shell find ${TEST_MODULES_DIR} -maxdepth 1 -name "*.cpp"))
TEST_HEADERS = $(shell find ${TEST_MODULES_DIR} -maxdepth 1 -name "*.h")
TEST_OBJECTS = $(addprefix ${TEST_OBJ_DIR}/, $(notdir $(TEST_SOURCE:%.cpp=%.o)))
TEST_LIBS = -lgtest ${LIB_ADDITIONAL}
REPORT_DIR = report
GCOV_EXEC := gcov_report
GCOV_OBJ_DIR = ${OBJ_DIR}/gcov
GCOV_LIBS = ${TEST_LIBS} -lgcov
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
GCOV_OBJECTS = $(addprefix ${GCOV_OBJ_DIR}/, $(notdir $(SOURCE:%.cpp=%.o)))
CMD_OPEN = xdg-open
CPP_H_FILES = $(shell find . -type f | grep "\.(cpp|cc|h|hpp)$$" -E)

UNAME_S := $(shell uname -s)

vpath %.cpp ${TEST_MODULES_DIR}
vpath %.o ${OBJ_DIR}

all: clean clang ${TEST_EXEC} ${GCOV_EXEC}

build: ${STATIC_LIB}

${STATIC_LIB}: ${OBJ_DIR} ${OBJECTS}
	@ar rc $@ $(addprefix ${OBJ_DIR}/, ${OBJECTS})
	@ranlib $@ 

${STATIC_LIB_GCOV}: ${GCOV_OBJ_DIR} ${GCOV_OBJECTS}
	@ar rc $@ $(addprefix ${GCOV_OBJ_DIR}/, ${OBJECTS})
	@ranlib $@ 

${TEST_EXEC}: ${OBJ_DIR} ${TEST_OBJ_DIR} ${STATIC_LIB} ${TEST_OBJECTS}
	@${CXX} ${TEST_OBJECTS} ${STATIC_LIB} ${TEST_LIBS} -o ${TEST_EXEC}
	./${TEST_EXEC}


${GCOV_EXEC}: ${OBJ_DIR} $(GCOV_OBJ_DIR) $(TEST_OBJ_DIR) ${REPORT_DIR} ${TEST_OBJECTS} ${STATIC_LIB_GCOV}
	@${CXX} ${TEST_OBJECTS} ${STATIC_LIB_GCOV} ${GCOV_LIBS} -o ${GCOV_EXEC}
	@./${GCOV_EXEC}
	@gcov -o ${GCOV_OBJ_DIR} ${SOURCE}
	@lcov -b ./ -d ${GCOV_OBJ_DIR} --gcov-tool /usr/bin/gcov -c -o output.info --no-external
	@genhtml -o ${REPORT_DIR} output.info
	@$(CMD_OPEN) $(REPORT_DIR)/index.html

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(GCOV_OBJ_DIR):
	@mkdir -p $(GCOV_OBJ_DIR)

$(TEST_OBJ_DIR):
	@mkdir -p $(TEST_OBJ_DIR)

$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)

%.o: %.cpp ${HEADER}
	@${CXX} ${CXXFLAGS} -o $(addprefix $(OBJ_DIR)/, $@) $<

${TEST_OBJ_DIR}/%.o: %.cpp ${HEADER} ${TEST_HEADERS}
	@${CXX} ${CXXFLAGS} -o $@ $<

${GCOV_OBJ_DIR}/%.o: %.cpp ${HEADER} ${TEST_HEADERS}
	@${CXX} ${CXXFLAGS} ${GCOV_FLAGS} -o $@ $<

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n ${CPP_H_FILES}
	rm ./.clang-format

clangi:
	cp ../materials/linters/.clang-format .
	clang-format -i ${CPP_H_FILES}
	rm ./.clang-format

cppcheck:
	cppcheck --enable=all --force --suppress=missingIncludeSystem --language=c++ --std=c++17 ${SOURCE} ${HEADER} ${TEST_SOURCE} ${TEST_HEADERS}

valgrind: ${TEST_EXEC}
	valgrind --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(TEST_EXEC)

clean:
	@rm -f ${GCOV_EXEC}
	@rm -f *.gch
	@rm -f *.gcov
	@rm -f *.info
	@rm -f *.a
	@rm -f ${TEST_EXEC}
	@rm -rf ${OBJECTS}
	@rm -rf ${OBJ_DIR}
	@rm -rf ${REPORT_DIR}

.PHONY: all build clean cppcheck clangf clang valgrind