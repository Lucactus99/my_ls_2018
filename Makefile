##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

.RECIPEPREFIX +=

CC      =       gcc

SRC     =   my_ls_main.c \
            my_ls_options.c \
            my_ls_put_space.c \
            my_ls_print_month.c \
            my_ls_display.c \
            my_ls_sorting.c \
            my_ls_display_l.c \
            my_ls_display_ls.c \
            my_ls_display_R.c \
            my_ls_get_info.c \
            src/my_strlen.c \
            src/my_strcat.c \
            src/my_strcpy.c \
            src/my_strlowcase.c \
            src/my_putstr.c \
            src/my_putchar.c \
            src/my_strcmp.c \
            src/my_put_nbr.c

OBJ     =       $(SRC:.c=.o)

NAME    =       my_ls

CFLAGS  =       -W -Wextra -Wall -Wparentheses -Wsign-compare -Wpointer-sign -Wuninitialized -Wunused-but-set-variable -ansi -pedantic -g -std=c99 -I ./include

all:    $(NAME)

$(NAME):	$(OBJ)
    $(CC) $(OBJ) -o $(NAME) $(CFLAGS)
    rm -f $(OBJ)

clean:
    rm -f $(OBJ)

fclean: clean
    rm -f $(NAME)

re:		fclean all