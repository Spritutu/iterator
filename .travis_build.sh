cd test
clang++ -lgtest -stdlib=libc++ -Wall -Wextra -o test.o -c test.cpp
./test -v
