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
    if (opt->bool_tt == 1)
        opt->files = sort_by_time(opt);
}

void check_options_2(char const *const *av, struct options *opt, int i, int j)
{
    if (av[i][j] == 'f') {
        opt->bool_f = 1;
        opt->bool_a = 1;
    }
    if (av[i][j] == 'i')
        opt->bool_i = 1;
    if (av[i][j] == 'm') {
        opt->bool_1 = 0;
        opt->bool_m = 1;
    }
    if (av[i][j] == 'n')
        opt->bool_n = 1;
    if (av[i][j] == 'r')
        opt->bool_r = 1;
    if (av[i][j] == '1') {
        opt->bool_m = 0;
        opt->bool_1 = 1;
    }
    if (av[i][j + 1] != 0)
        check_options(av, opt, i, j + 1);
}

void check_options(char const *const *av, struct options *opt, int i, int j)
{
    if (av[i][j] == 'a')
        opt->bool_a = 1;
    if (av[i][j] == 'A')
        opt->bool_a_maj = 1;
    if (av[i][j] == 'o')
        opt->bool_o = 1;
    if (av[i][j] == 't')
        opt->bool_tt = 1;
    if (av[i][j] == 'p')
        opt->bool_p = 1;
    if (av[i][j] == 'd')
        opt->bool_d = 1;
    if (av[i][j] == 'l')
        opt->bool_l = 1;
    check_options_2(av, opt, i, j);
}

void analyse_path(int ac, char const *const *av, struct options *opt)
{
    int i = 1;

    if (ac < 2)
        return ;
    while (av[i][0] == '-' && i < ac - 1)
        i++;
    if (av[i][0] != '-') {
        opt->dir_bool = 1;
        opt->path = malloc(sizeof(char) * (my_strlen(av[i]) + 1));
        opt->path = my_strcpy(opt->path, av[i]);
        opt->path_av = malloc(sizeof(char) * (my_strlen(av[i]) + 1));
        opt->path_av = my_strcpy(opt->path_av, opt->path);
        if (opt->path[my_strlen(opt->path) - 1] != '/')
            opt->path = my_strcat(opt->path, "/");
    }
}

void analyse_arg(int ac, char const *const *av, struct options *opt)
{
    for (int i = 1; i < ac; i++) {
        if (av[i][0] == '-')
            check_options(av, opt, i, 1);
    }
    analyse_path(ac, av, opt);
}