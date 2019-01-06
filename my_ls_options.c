/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_options
*/

#include "my.h"

void option_a(struct options *opt)
{
    for (int h = 0; h < opt->nbr && opt->bool_f == 0; h++) {
        for (int i = h; i < opt->nbr - 1; i++)
            opt->files = is_sorted(opt, h, i, 0);
    }
    if (opt->bool_r == 1 && opt->bool_f == 0)
        opt->files = reverse_str(opt->files, opt->len, opt->nbr);
}

void check_options_2(char const *const *av, struct options *opt, int i)
{
    if (av[i][1] == 'f') {
        opt->bool_f = 1;
        opt->bool_a = 1;
    }
    if (av[i][1] == 'i')
        opt->bool_i = 1;
    if (av[i][1] == 'm') {
        opt->bool_1 = 0;
        opt->bool_m = 1;
    }
    if (av[i][1] == 'n')
        opt->bool_n = 1;
    if (av[i][1] == 'r')
        opt->bool_r = 1;
    if (av[i][1] == '1') {
        opt->bool_m = 0;
        opt->bool_1 = 1;
    }
    if (av[i][1] == 'a')
        opt->bool_a = 1;
}

void check_options(char const *const *av, struct options *opt, int i)
{
    if (av[i][1] == 'A')
        opt->bool_a_maj = 1;
    if (av[i][1] == 'o')
        opt->bool_o = 1;
    if (av[i][1] == 'd')
        opt->bool_d = 1;
    if (av[i][1] == 'l')
        opt->bool_l = 1;
    if (my_strcmp(av[i], "-la") == 0) {
        opt->bool_l = 1;
        opt->bool_a = 1;
    }
    if (my_strcmp(av[i], "-1a") == 0) {
        opt->bool_1 = 1;
        opt->bool_a = 1;
    }
    check_options_2(av, opt, i);
}

void analyse_arg(int ac, char const *const *av, struct options *opt)
{
    for (int i = 1; i < ac; i++) {
        if (my_strlen(av[i]) < 4 && av[i][0] != '.' && av[i][0] == '-') {
            check_options(av, opt, i);
        } else {
            opt->dir_bool = 1;
            opt->path = malloc(sizeof(char) * (my_strlen(av[i]) + 1));
            opt->path = my_strcpy(opt->path, av[i]);
        }
    }
}