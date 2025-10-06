# commands 
clang -g main.c lexer.c -o a.out
leaks --atExit -- ./a.out

gcc -fsanitize=address lexer.c main.c -o a.out
