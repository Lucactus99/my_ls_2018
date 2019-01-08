/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_display_ls
*/

#include "my.h"

void display_ls_2(struct options *opt, int i, struct stat statbuff)
{
    display_i(opt, statbuff);
    print_file(opt->files[i]);
    if (S_ISDIR(statbuff.st_mode) == 1 && opt->bool_p == 1)
        my_putchar('/');
    if (i + 1 < opt->nbr) {
        if (opt->bool_m == 1) {
            my_putchar(44);
            my_putchar(' ');
        } else if (opt->bool_1 == 1)
            my_putchar('\n');
        else {
            my_putchar(' ');
            my_putchar(' ');
        }
    }
}

void display_ls(struct options *opt)
{
    struct stat statbuff;
    char *path_file = malloc(sizeof(char) *
    (my_strlen(opt->path) + opt->len + 1));

    for (int i = 0; i < opt->nbr; i++) {
        path_file = my_strcpy(path_file, opt->path);
        path_file = my_strcat(path_file, opt->files[i]);
        stat(path_file, &statbuff);
        if (opt->files[i][0] != '.' || opt->bool_a == 1)
            display_ls_2(opt, i, statbuff);
    }
    my_putchar('\n');
    exit(0);
}

char *transform_ctime_2(char *date, int a, int i, char *str)
{
    int nb = 0;

    while (nb < 2) {
        date[a] = str[i];
        a++;
        i++;
        if (str[i] == ':')
            nb++;
    }
    i++;
    date[a] = ' ';
    a++;
    date[a] = '\0';
    return (date);
}

char *transform_ctime(char *str)
{
    char *date = malloc(sizeof(char) * my_strlen(str));
    int i = 0;
    int a = 0;

    while (str[i] != ' ')
        i++;
    i++;
    while (str[i] != ' ') {
        date[a] = str[i];
        a++;
        i++;
    }
    date[a] = ' ';
    return (transform_ctime_2(date, a, i, str));
}

void display_l_time(struct stat statbuff)
{
    my_putstr(transform_ctime(ctime(&statbuff.st_mtime)));
}