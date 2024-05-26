clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cpp *.h
	rm ./.clang-format

clangf:
	cp ../materials/linters/.clang-format .
	clang-format -i *.cpp *.h
	rm ./.clang-format