CC = gcc

NAME_LIBA = libTries.a
NAME_LIB = Tries

all:
	$(CC) -c *.c
	ar rc $(NAME_LIBA) *.o
	ranlib $(NAME_LIBA)
	$(CC) main.o -L. -l$(NAME_LIB) -o start
	rm *.o *.a