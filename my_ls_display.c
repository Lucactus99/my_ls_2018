/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_display
*/

#include "my.h"

void display_i(struct options *opt, struct stat statbuff)
{
    if (opt->bool_i == 1) {
        my_put_nbr(statbuff.st_ino);
        my_putchar(' ');
    }
}

void display_d(struct options *opt)
{
    struct stat statbuff;

    find_path(&statbuff, opt, -1);
    if (opt->bool_l == 1) {
        display_i(opt, statbuff);
        display_l_permissions(statbuff, opt, 0);
        display_l_links(statbuff, opt, -1);
        display_l_owner_user(statbuff, opt);
        display_l_size(statbuff, opt, -1);
        display_l_time(statbuff);
    }
    if (my_strcmp(opt->path, "./") == 0)
        my_putchar('.');
    else
        my_putstr(opt->path_av);
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

void print_file(char *file)
{
    int ok = 0;

    for (int i = 0; file[i] != 0; i++) {
        if (file[i] == ' ') {
            ok = 1;
            break;
        }
    }
    if (ok == 1)
        my_putchar(39);
    my_putstr(file);
    if (ok == 1)
        my_putchar(39);
}

void display_l(struct options *opt)
{
    struct stat statbuff;

    display_l_total_size(opt->nbr, opt, statbuff);
    for (int i = 0; i < opt->nbr; i++) {
        if (opt->files[i][0] != '.' || opt->bool_a == 1) {
            find_path(&statbuff, opt, i);
            display_i(opt, statbuff);
            display_l_permissions(statbuff, opt, i);
            display_l_links(statbuff, opt, i);
            display_l_owner_user(statbuff, opt);
            display_l_size(statbuff, opt, i);
            display_l_time(statbuff);
            print_file(opt->files[i]);
            my_putchar('\n');
        }
    }
    exit(0);
}