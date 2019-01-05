/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_display
*/

#include "my.h"

void display_ls(char **files, int nbr)
{
    for (int i = 0; i < nbr; i++) {
        if (files[i][0] != '.') {
            my_putstr(files[i]);
            if (i + 1 < nbr)
                my_putstr("  ");
        }
    }
    my_putchar('\n');
    exit(0);
}

void display_d(struct options *opt)
{
    my_putstr(opt->path);
    my_putchar('\n');
    exit(0);
}

void display_a_maj(char **files, int nbr)
{
    for (int i = 0; i < nbr; i++) {
        if (my_strcmp(files[i], ".") != 0 && my_strcmp(files[i], "..") != 0) {
            my_putstr(files[i]);
            my_putstr("  ");
        }
    }
    my_putchar('\n');
    exit(0);
}

void display_a(char **files, int nbr)
{
    for (int i = 0; i < nbr; i++) {
        my_putstr(files[i]);
        my_putstr("  ");
    }
    my_putchar('\n');
    exit(0);
}

void display_one(char **files, int nbr, struct options *opt)
{
    for (int i = 0; i < nbr; i++) {
        if (files[i][0] != '.' || opt->bool_a == 1) {
            my_putstr(files[i]);
            my_putchar('\n');
        }
    }
    exit(0);
}

void display_l(char **files, int nbr, struct options *opt)
{
    struct stat statbuff;
    struct passwd *pwd;
    struct group *gr;
    struct tm *timer;

    for (int i = 0; i < nbr; i++) {
        if (files[i][0] != '.' || opt->bool_a == 1) {
            stat(files[i], &statbuff);
            opt->total_size += statbuff.st_blocks / 2;
        }
    }
    pwd = getpwuid(statbuff.st_uid);
    gr = getgrgid(statbuff.st_gid);
    my_putstr("total ");
    my_put_nbr(opt->total_size);
    my_putchar('\n');
    for (int i = 0; i < nbr; i++) {
        if (files[i][0] != '.' || opt->bool_a == 1) {
            stat(files[i], &statbuff);
            my_putstr((S_ISDIR(statbuff.st_mode)) ? "d" : "-");
            my_putstr((statbuff.st_mode & S_IRUSR) ? "r" : "-");
            my_putstr((statbuff.st_mode & S_IWUSR) ? "w" : "-");
            my_putstr((statbuff.st_mode & S_IXUSR) ? "x" : "-");
            my_putstr((statbuff.st_mode & S_IRGRP) ? "r" : "-");
            my_putstr((statbuff.st_mode & S_IWGRP) ? "w" : "-");
            my_putstr((statbuff.st_mode & S_IXGRP) ? "x" : "-");
            my_putstr((statbuff.st_mode & S_IROTH) ? "r" : "-");
            my_putstr((statbuff.st_mode & S_IWOTH) ? "w" : "-");
            my_putstr((statbuff.st_mode & S_IXOTH) ? "x" : "-");
            my_putchar(' ');
            my_put_nbr(statbuff.st_nlink);
            my_putchar(' ');
            my_putstr(pwd->pw_name);
            my_putchar(' ');
            my_putstr(gr->gr_name);
            put_space_size(statbuff, nbr, files, i);
            my_put_nbr(statbuff.st_size);
            my_putchar(' ');
            timer = localtime(&(statbuff.st_mtime));
            print_month(timer);
            put_space_day(timer, nbr, opt);
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
            my_putstr(files[i]);
            my_putchar('\n');
        }
    }
    exit(0);
}