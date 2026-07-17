cmake_minimum_required(VERSION 3.20)
project(s21_matrix+ VERSION 2.0 LANGUAGES CXX)

# --------------------------------------
# Базовые настройки и стандарты
# --------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Флаги компиляции (аналог CXXFLAGS в Makefile)
add_compile_options(-Wall -Wextra -Werror -pedantic)

# --------------------------------------
# Настройка путей и файлов
# --------------------------------------
set(SRC_DIR src)
set(INC_DIR include/s21) # Указываем include/s21, как в вашем Makefile
set(TEST_DIR tests)

file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")
file(GLOB INC_FILES "${INC_DIR}/*.hpp")
file(GLOB TEST_SRC_FILES "${TEST_DIR}/test_*.cpp")

# --------------------------------------
# Конфигурация типа библиотеки (static, dynamic, all)
# --------------------------------------
set(LIBTYPE "static" CACHE STRING "Library type: static, dynamic, or all")
set_property(CACHE LIBTYPE PROPERTY STRINGS static dynamic all)

if(LIBTYPE STREQUAL "static" OR LIBTYPE STREQUAL "all")
    add_library(s21_matrix+_static STATIC ${SRC_FILES})
    target_include_directories(s21_matrix+_static PUBLIC ${INC_DIR})
    set_target_properties(s21_matrix+_static PROPERTIES OUTPUT_NAME s21_matrix+)
endif()

if(LIBTYPE STREQUAL "dynamic" OR LIBTYPE STREQUAL "all")
    add_library(s21_matrix+_shared SHARED ${SRC_FILES})
    target_include_directories(s21_matrix+_shared PUBLIC ${INC_DIR})
    set_target_properties(s21_matrix+_shared PROPERTIES OUTPUT_NAME s21_matrix+)
endif()

# Определение библиотеки для линковки тестов
if(LIBTYPE STREQUAL "static")
    set(S21_MATRIX_LIB s21_matrix+_static)
elseif(LIBTYPE STREQUAL "dynamic")
    set(S21_MATRIX_LIB s21_matrix+_shared)
else()
    set(S21_MATRIX_LIB s21_matrix+_static) # При 'all' для тестов используем статическую
endif()

# --------------------------------------
# Установка и удаление (install / uninstall)
# --------------------------------------
install(FILES ${INC_FILES} DESTINATION include/s21_matrix+)
if(TARGET s21_matrix+_static)
    install(TARGETS s21_matrix+_static ARCHIVE DESTINATION lib)
endif()
if(TARGET s21_matrix+_shared)
    install(TARGETS s21_matrix+_shared LIBRARY DESTINATION lib)
endif()

# Кастомная цель для удаления (аналог make uninstall)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_INSTALL_PREFIX}/include/s21_matrix+"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/lib/libs21_matrix+.a"
    COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_INSTALL_PREFIX}/lib/libs21_matrix+.so"
    COMMENT "Uninstalling s21_matrix+"
)

# --------------------------------------
# Тестирование и покрытие (unit-test / gcov-report)
# --------------------------------------
enable_testing()
find_package(GTest REQUIRED)

# В CMake покрытие включается на этапе конфигурации
option(ENABLE_COVERAGE "Enable coverage reporting (adds --coverage flags)" ON)

add_executable(test_runner ${TEST_SRC_FILES})
target_link_libraries(test_runner PRIVATE ${S21_MATRIX_LIB} GTest::gtest GTest::gtest_main pthread)
target_include_directories(test_runner PRIVATE ${INC_DIR} ${TEST_DIR})

if(ENABLE_COVERAGE)
    target_compile_options(${S21_MATRIX_LIB} PRIVATE --coverage)
    target_link_options(${S21_MATRIX_LIB} PRIVATE --coverage)
    target_compile_options(test_runner PRIVATE --coverage)
    target_link_options(test_runner PRIVATE --coverage)
endif()

add_test(NAME s21_matrix_tests COMMAND test_runner)

# Цель unit-test (запуск ctest)
add_custom_target(unit-test
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS test_runner
    COMMENT "Running unit tests"
)

# --------------------------------------
# Линтеры (linter-test: clang-format & cppcheck)
# --------------------------------------
find_program(CLANG_FORMAT clang-format)
find_program(CPPCHECK cppcheck)

if(CLANG_FORMAT)
    add_custom_target(clang-format-check
        COMMAND ${CLANG_FORMAT} --style=Google --dry-run --Werror ${SRC_FILES} ${INC_FILES}
        COMMENT "Checking code style with clang-format"
    )
else()
    add_custom_target(clang-format-check
        COMMAND ${CMAKE_COMMAND} -E echo "Error: clang-format not found."
        COMMAND ${CMAKE_COMMAND} -E false
    )
endif()

if(CPPCHECK)
    add_custom_target(cppcheck
        COMMAND ${CPPCHECK} --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --language=c++ --std=c++20 --error-exitcode=1 ${SRC_FILES} ${INC_FILES}
        COMMENT "Running cppcheck"
    )
else()
    add_custom_target(cppcheck
        COMMAND ${CMAKE_COMMAND} -E echo "Error: cppcheck not found."
        COMMAND ${CMAKE_COMMAND} -E false
    )
endif()

add_custom_target(linter-test DEPENDS clang-format-check cppcheck)

# --------------------------------------
# Проверка памяти (mem-test: Valgrind)
# --------------------------------------
find_program(VALGRIND valgrind)

if(VALGRIND)
    add_custom_target(mem-test
        COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 $<TARGET_FILE:test_runner>
        DEPENDS test_runner
        COMMENT "Running Valgrind memory check"
    )
else()
    add_custom_target(mem-test
        COMMAND ${CMAKE_COMMAND} -E echo "Error: Valgrind not found."
        COMMAND ${CMAKE_COMMAND} -E false
    )
endif()

# --------------------------------------
# Отчет о покрытии (gcov-report: lcov & genhtml)
# --------------------------------------
find_program(LCOV lcov)
find_program(GENHTML genhtml)

if(LCOV AND GENHTML)
    add_custom_target(gcov-report
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        COMMAND ${LCOV} --capture --directory ${CMAKE_BINARY_DIR} --output-file ${CMAKE_BINARY_DIR}/coverage/coverage.info
        COMMAND ${GENHTML} ${CMAKE_BINARY_DIR}/coverage/coverage.info --output-directory ${CMAKE_BINARY_DIR}/coverage/report
        DEPENDS test_runner
        COMMENT "Generating coverage report"
    )
else()
    add_custom_target(gcov-report
        COMMAND ${CMAKE_COMMAND} -E echo "Error: lcov or genhtml not found."
        COMMAND ${CMAKE_COMMAND} -E false
    )
endif()

# --------------------------------------
# Документация (dvi: Doxygen)
# --------------------------------------
find_package(Doxygen)

if(DOXYGEN_FOUND)
    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    add_custom_target(dvi
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
    )
else()
    add_custom_target(dvi
        COMMAND ${CMAKE_COMMAND} -E echo "Error: Doxygen not found."
        COMMAND ${CMAKE_COMMAND} -E false
    )
endif()

# --------------------------------------
# Глобальные цели (test-all, clean, help)
# --------------------------------------
# ИСПРАВЛЕНИЕ: Переименовываем 'test' в 'test-all', так как 'test' зарезервирован CTest
add_custom_target(test-all 
    DEPENDS linter-test unit-test mem-test gcov-report
    COMMENT "Running all tests: linters, unit tests, memory check, coverage"
)

# Расширение стандартной цели clean
set_property(DIRECTORY PROPERTY ADDITIONAL_CLEAN_FILES 
    "${CMAKE_BINARY_DIR}/coverage"
    "${CMAKE_BINARY_DIR}/docbuild"
    "${CMAKE_BINARY_DIR}/Testing"
)

# Кастомная цель usage (имя 'help' зарезервировано CMake)
add_custom_target(usage
    COMMAND ${CMAKE_COMMAND} -E echo "Доступные цели CMake (используйте: cmake --build . --target <цель>):"
    COMMAND ${CMAKE_COMMAND} -E echo "  build         - сборка библиотеки (при конфигурации: -DLIBTYPE=static|dynamic|all)"
    COMMAND ${CMAKE_COMMAND} -E echo "  install       - установка заголовков и библиотеки"
    COMMAND ${CMAKE_COMMAND} -E echo "  uninstall     - удаление установленной библиотеки"
    COMMAND ${CMAKE_COMMAND} -E echo "  dvi           - генерация документации (Doxygen)"
    COMMAND ${CMAKE_COMMAND} -E echo "  test-all      - запуск всех тестов: линтеры, юнит-тесты, valgrind, покрытие"
    COMMAND ${CMAKE_COMMAND} -E echo "  linter-test   - проверка стиля (clang-format) и статический анализ (cppcheck)"
    COMMAND ${CMAKE_COMMAND} -E echo "  unit-test     - сборка и запуск юнит-тестов (Google Test)"
    COMMAND ${CMAKE_COMMAND} -E echo "  mem-test      - проверка утечек памяти через valgrind"
    COMMAND ${CMAKE_COMMAND} -E echo "  gcov-report   - генерация отчёта о покрытии кода тестами"
    COMMAND ${CMAKE_COMMAND} -E echo "  clean         - удаление всех сгенерированных файлов"
    COMMAND ${CMAKE_COMMAND} -E echo "  usage         - вывод этой справки"
)
