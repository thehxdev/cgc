CC=gcc
FLAGS=-std=c17 -Wall -Wextra -pedantic
FLAGS+=-Werror -Wno-unused-but-set-variable -Wno-unused-variable
INPUT=main.c gc.c


default:
	$(CC) $(FLAGS) $(INPUT)

check:
	valgrind --leak-check=full ./a.out
