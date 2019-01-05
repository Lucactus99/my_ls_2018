/*
** EPITECH PROJECT, 2018
** h
** File description:
** h
*/

#ifndef MY_H_
#define MY_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>

struct options
{
    int dir_bool;
    int bool_a;
    int bool_a_maj;
    int bool_d;
    int bool_1;
    int bool_l;
    long total_size;
    char *path;
    int lines_display;
};

void my_putchar(char);
int my_putstr(char const *);
int my_strlen(char const *);
char *my_strcpy(char *dest, char const *src);
char my_strlowcase(char str);
int my_strcmp(char const *s1, char const *s2);
char *my_strcat(char *dest, char const *src);
int my_getnbr(char *str);
int my_put_nbr(int nb);


#endif //MY_H_
