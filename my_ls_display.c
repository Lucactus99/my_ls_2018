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

void display_l(struct options *opt)
{
    struct stat statbuff;
    char *path_file = malloc(sizeof(char) *
    (my_strlen(opt->path) + opt->len + 1));

    display_l_total_size(opt->nbr, opt, statbuff);
    for (int i = 0; i < opt->nbr; i++) {
        if (opt->files[i][0] != '.' || opt->bool_a == 1) {
            path_file = my_strcpy(path_file, opt->path);
            path_file = my_strcat(path_file, opt->files[i]);
            if (stat(path_file, &statbuff) < 0)
                exit(84);
            display_i(opt, statbuff);
            display_l_permissions(statbuff);
            display_l_links(statbuff, opt, i);
            display_l_owner_user(statbuff, opt);
            display_l_size(statbuff, opt, i);
            display_l_time(statbuff, opt, i);
            my_putstr(opt->files[i]);
            my_putchar('\n');
        }
    }
    exit(0);
}

void condition_display(int ac, struct options *opt, char const *const *av)
{
    if (opt->bool_d == 1)
        display_d(opt);
    if (opt->bool_l == 1 || opt->bool_n == 1 || opt->bool_o == 1)
        display_l(opt);
    if (opt->bool_a_maj == 1)
        display_a_maj(opt->files, opt->nbr);
    if (ac == 1 || (ac == 2 && opt->dir_bool == 1) || opt->bool_r == 1 ||
        opt->bool_i == 1 || opt->bool_m == 1 || opt->bool_f == 1 ||
        opt->bool_a == 1 || opt->bool_1 == 1)
        display_ls(opt);
    else
        check_invalid_option(ac, av);
}