/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_display_ls
*/

#include "my.h"

struct tm *my_localtime(long *timestamp)
{
    struct tm *timer = malloc(sizeof(struct tm));

    *timestamp = (*timestamp / 60);
    timer->tm_min = *timestamp % 60;
    *timestamp = (*timestamp / 60);
    timer->tm_hour = *timestamp % 24 + 1;
    if (timer->tm_hour == 24)
        timer->tm_hour = 00;
    return (timer);
}

void display_ls_2(struct options *opt, int i, struct stat statbuff)
{
    display_i(opt, statbuff);
    my_putstr(opt->files[i]);
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

void display_l_time(struct stat statbuff, struct options *opt, int i)
{
    struct tm *timer = my_localtime(&(statbuff.st_mtime));

    print_month(timer);
    put_space_day(statbuff, opt->nbr, i, opt);
    my_put_nbr(timer->tm_mday);
    my_putchar(' ');
    if (timer->tm_hour < 10)
        my_putchar('0');
    my_put_nbr(timer->tm_hour);
    my_putchar(':');
    if (timer->tm_min < 10)
        my_putchar('0');
    my_put_nbr(timer->tm_min);
    my_putchar(' ');
}

void display_l_total_size(int nbr, struct options *opt, struct stat statbuff)
{
    char *path_file = malloc(sizeof(char) *
    (my_strlen(opt->path) + opt->len + 1));

    for (int i = 0; i < nbr; i++) {
        if (opt->files[i][0] != '.' || opt->bool_a == 1) {
            path_file = my_strcpy(path_file, opt->path);
            path_file = my_strcat(path_file, opt->files[i]);
            stat(path_file, &statbuff);
            opt->total_size += statbuff.st_blocks / 2;
        }
    }
    my_putstr("total ");
    my_put_nbr(opt->total_size);
    my_putchar('\n');
}