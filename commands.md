# commands 
on mac
clang -g main.c lexer.c -o a.out
leaks --atExit -- ./a.out
gcc -fsanitize=address lexer.c main.c -o a.out

on linux(for memory leak)
gcc -g file.c -o file
then use valgrind
valgring ./file


with the makefile 
make //to compile
make test // This will recompile if necessary and then run Valgrind with the proper leak-check flags.
make clean // to reset
