SOURCE = s21_matrix_err.h s21_matrix_oop.h s21_matrix_oop.cpp

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n ${SOURCE}
	rm ./.clang-format

clangf:
	cp ../materials/linters/.clang-format .
	clang-format -i ${SOURCE}
	rm ./.clang-format

cppcheck:
	cppcheck --enable=all --force --suppress=missingIncludeSystem --language=c++ ${SOURCE}