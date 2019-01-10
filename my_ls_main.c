/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_main
*/

#include "my.h"

void print_invalid_option(char const *const *av, int i, int j)
{
    if (av[i][j] == '-') {
        my_putstr("my_ls: invalid option -- '");
        my_putchar(av[i][j + 1]);
        my_putstr("'\nTry './my_ls --help' for more information.\n");
        exit(84);
    }
}

void check_null_rep(DIR *rep, struct options *opt)
{
    if (rep == NULL) {
        my_putstr("my_ls: cannot access '");
        my_putstr(opt->path);
        my_putstr("': ");
        my_putstr(strerror(errno));
        my_putchar('\n');
        exit(84);
    }
}

void check_invalid_option(int ac, char const *const *av)
{
    for (int i = 0; i < ac; i++) {
        for (int j = 0; av[i][j] != 0; j++)
            print_invalid_option(av, i, j);
    }
}

void get_elements(struct options *opt, int i, char *str)
{
    DIR *rep;
    struct dirent *lecture;
    opt->nbr = 0;
    opt->len = 0;
    char *tmp;

    if (i == -1)
        rep = opendir(opt->path);
    else {
        tmp = malloc(sizeof(char) * 100);
        tmp = my_strcpy(tmp, opt->path);
        if (str != NULL) {
            tmp = my_strcat(tmp, str);
        }
        tmp = my_strcat(tmp, opt->files[i]);
        rep = opendir(tmp);
    }
    check_null_rep(rep, opt);
    lecture = readdir(rep);
    while (lecture) {
        if (my_strlen(lecture->d_name) > opt->len)
            opt->len = my_strlen(lecture->d_name);
        lecture = readdir(rep);
        opt->nbr++;
    }
    if (i == -1)
        opt->maxNbr = opt->nbr;
    else
        free(tmp);
    closedir(rep);
}

int main(int ac, char const *const *av)
{
    struct options *opt = malloc(sizeof(struct options));

    opt->nbr = 0;
    opt->len = 0;
    opt->path = malloc(sizeof(char) * 1);
    analyse_arg(ac, av, opt);
    if (opt->dir_bool == 0)
        opt->path = my_strcpy(opt->path, "./");
    get_elements(opt, -1, NULL);
    create_files(opt, -1, NULL);
    option_a(opt);
    condition_display(ac, opt, av);
    return (0);
}