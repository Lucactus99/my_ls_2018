##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

.RECIPEPREFIX +=

CC      =       gcc

SRC     =   main.c \
            my_strlen.c \
            my_strcpy.c \
            my_strlowcase.c

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
