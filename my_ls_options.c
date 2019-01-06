/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_options
*/

#include "my.h"

char **is_sorted(char **files, int h, int i, int len, int j)
{
    char *tmp = malloc(sizeof(char) * (len + 1));

    if (my_strlowcase(files[h][j]) > my_strlowcase(files[i + 1][j])) {
        tmp = my_strcpy(tmp, files[h]);
        files[h] = my_strcpy(files[h], files[i + 1]);
        files[i + 1] = my_strcpy(files[i + 1], tmp);
        h--;
        return (files);
    } else if (my_strlowcase(files[h][j]) == my_strlowcase(files[i + 1][j]))
        return (is_sorted(files, h, i, len, j + 1));
    return (files);
}

char **reverse_str(char **files, int len, int nbr)
{
    char *tmp = malloc(sizeof(char) * (len + 1));

    for (int h = 0; h < nbr / 2; h++) {
        tmp = files[nbr - h - 1];
        files[nbr - h - 1] = files[h];
        files[h] = tmp;
    }
    return (files);
}

char **option_a(char **files, int nbr, int len, struct options *opt)
{
    for (int h = 0; h < nbr; h++) {
        for (int i = h; i < nbr - 1; i++) {
            if (opt->bool_f == 0)
                files = is_sorted(files, h, i, len, 0);
        }
    }
    if (opt->bool_r == 1 && opt->bool_f == 0)
        files = reverse_str(files, len, nbr);
    return (files);
}

void check_options(char const *const *av, struct options *opt, int i)
{
    if (av[i][1] == 'f') {
        opt->bool_f = 1;
        opt->bool_a = 1;
    }
    if (av[i][1] == 'i')
        opt->bool_i = 1;
    if (av[i][1] == 'm')
        opt->bool_m = 1;
    if (av[i][1] == 'r')
        opt->bool_r = 1;
    if (av[i][1] == '1')
        opt->bool_1 = 1;
    if (av[i][1] == 'a')
        opt->bool_a = 1;
    if (av[i][1] == 'A')
        opt->bool_a_maj = 1;
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
}

void analyse_arg(int ac, char const *const *av, struct options *opt)
{
    for (int i = 1; i < ac; i++) {
        if (my_strlen(av[i]) < 4 && av[i][0] != '.') {
            check_options(av, opt, i);
        } else {
            opt->dir_bool = 1;
            opt->path = my_strcpy(opt->path, av[i]);
        }
    }
}