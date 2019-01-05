##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

.RECIPEPREFIX +=

CC      =       gcc

SRC     =   main.c \
            src/my_strlen.c \
            src/my_strcpy.c \
            src/my_strlowcase.c \
            src/my_putstr.c \
            src/my_putchar.c \
            src/my_strcmp.c \
            src/my_put_nbr.c

OBJ     =       $(SRC:.c=.o)

NAME    =       my_ls

CFLAGS  =       -W -Werror -Wextra -Wall -Wparentheses -Wsign-compare -Wpointer-sign -Wuninitialized -Wunused-but-set-variable -ansi -pedantic -g -std=c99 -I ./include

all:    $(NAME)

$(NAME):	$(OBJ)
    $(CC) $(OBJ) -o $(NAME) $(CFLAGS)
    rm -f $(OBJ)

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)

re:		fclean all
