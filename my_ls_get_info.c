/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_get_info
*/

#include "my.h"

void swap_str(char **str1, char **str2)
{
    char *tmp;

    if (my_strlen(*str1) > my_strlen(*str2))
        tmp = malloc(sizeof(char) * (my_strlen(*str1) + 1));
    else
        tmp = malloc(sizeof(char) * (my_strlen(*str2) + 1));
    tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}

void find_path(struct stat *statbuff, struct options *opt, int i)
{
    char *path_file =
    malloc(sizeof(char) * (my_strlen(opt->path) + opt->len + 1));

    if (i > -1) {
        path_file = my_strcpy(path_file, opt->path);
        path_file = my_strcat(path_file, opt->files[i]);
        if (stat(path_file, statbuff) < 0)
            exit(84);
    } else {
        if (stat(opt->path, statbuff) < 0)
            exit(84);
    }
}

void condition_display(int ac, struct options *opt, char const *const *av)
{
    if (opt->bool_R == 1)
        display_r(opt, -1);
    if (opt->bool_d == 1)
        display_d(opt);
    if ((opt->bool_l == 1 && opt->bool_tt == 1) || opt->bool_l == 1 ||
        opt->bool_n == 1 || opt->bool_o == 1)
        display_l(opt);
    if (opt->bool_a_maj == 1)
        display_a_maj(opt->files, opt->nbr);
    if (ac == 1 || (ac == 2 && opt->dir_bool == 1) || opt->bool_r == 1 ||
        opt->bool_i == 1 || opt->bool_m == 1 || opt->bool_f == 1 ||
        opt->bool_a == 1 || opt->bool_1 == 1 || opt->bool_p == 1 ||
        opt->bool_tt == 1)
        display_ls(opt);
    else
        check_invalid_option(ac, av);
}