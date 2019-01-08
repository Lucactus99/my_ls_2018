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
    long stamp = *timestamp;
    int test = 0;

    while (*timestamp > 31556926) {
        test++;
        *timestamp -= 31556926;
    }
    timer->tm_year = test + 1970;
    test = 0;
    while (*timestamp > 2629743) {
        test++;
        *timestamp -= 2629743;
    }
    timer->tm_mon = test;
    test = 0;
    while (*timestamp > 604800) {
        test++;
        *timestamp -= 604800;
    }
    timer->tm_wday = test;
    test = 0;
    while (*timestamp > 86400) {
        test++;
        *timestamp -= 86400;
    }
    if (timer->tm_wday < test)
        test++;
    timer->tm_mday = test + timer->tm_wday * 6 + timer->tm_wday;
    test = 0;
    while (*timestamp > 3600) {
        test++;
        *timestamp -= 3600;
    }
    stamp = (stamp / 60);
    timer->tm_min = stamp % 60;
    stamp = (stamp / 60);
    timer->tm_hour = stamp % 24 + 1;
    if (timer->tm_hour == 24)
        timer->tm_hour = 00;
    if (timer->tm_hour == 0 || timer->tm_hour == 1)
        timer->tm_mday++;
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