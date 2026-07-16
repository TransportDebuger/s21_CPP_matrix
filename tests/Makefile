# Makefile for s21_matrix+ unit tests
# Usage: make test (builds and runs tests)
#        make clean (removes build files)

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic -g
LDFLAGS = -pthread

# Google Test paths
GTEST_ROOT ?= /usr/src/googletest
GTEST_INCLUDE ?= /usr/include
GTEST_LIBS ?= -lgtest -lgtest_main -lpthread

# Directories
SRC_DIR = ../src
INC_DIR = ../include
TEST_DIR = .
BUILD_DIR = build

# Source files
SRC_FILES = $(SRC_DIR)/s21_matrix+.cpp
TEST_FILES = $(wildcard $(TEST_DIR)/test_*.cpp)

# Output
TARGET = $(BUILD_DIR)/test_runner
TARGET_DIR = $(BUILD_DIR)

# Default target
all: $(TARGET_DIR) $(TARGET)

# Create build directory
$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

# Build test runner
$(TARGET): $(TEST_FILES) $(SRC_FILES) | $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) --coverage -I$(INC_DIR) -I$(GTEST_INCLUDE) \
		$(TEST_FILES) $(SRC_FILES) -o $(TARGET) $(LDFLAGS) $(GTEST_LIBS)

# Run tests
test: $(TARGET)
	./$(TARGET)

# Run with Valgrind
mem-test: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./$(TARGET)

# Generate coverage report
coverage: $(TARGET)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report

# Clean
clean:
	rm -rf $(BUILD_DIR) coverage.info coverage_report

# Rebuild
rebuild: clean all

.PHONY: all test mem-test coverage clean rebuild
