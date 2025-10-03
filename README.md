# dragon
clang -g main.c lexer.c -o a.out
leaks --atExit -- ./a.out
