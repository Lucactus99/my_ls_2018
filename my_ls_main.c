/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_main
*/

#include "my.h"

void print_invalid_option(int ac, char const* const* av)
{
    for (int i = 0; i < ac; i++) {
        for (int j = 0; av[i][j] != 0; j++) {
            if (av[i][j] == '-') {
                my_putstr("ls: invalid option -- '");
                my_putchar(av[i][j + 1]);
                my_putstr("'\nTry 'ls --help' for more information.\n");
            }
        }
    }
}

void condition_display(int ac, struct options *opt, int nbr, char **files,
                       char const* const* av)
{
    if (opt->bool_d == 1)
        display_d(opt);
    if (opt->bool_l == 1 || opt->bool_n == 1)
        display_l(files, nbr, opt);
    if (opt->bool_1 == 1)
        display_one(files, nbr, opt);
    if (opt->bool_a == 1 || opt->bool_f == 1)
        display_a(files, nbr, opt);
    if (opt->bool_a_maj == 1)
        display_a_maj(files, nbr);
    if (ac == 1 || (ac == 2 && opt->dir_bool == 1) || opt->bool_r == 1 ||
        opt->bool_i == 1 || opt->bool_m == 1)
        display_ls(files, nbr, opt);
    else
        print_invalid_option(ac, av);
}

int main(int ac, char const *const *av)
{
    struct options *opt = malloc(sizeof(struct options));
    DIR *rep;
    struct dirent *lecture;
    int nbr = 0;
    int len = 0;
    int total = 0;
    char **files;

    opt->path = malloc(sizeof(char) * 10);
    analyse_arg(ac, av, opt);
    if (opt->dir_bool == 0) {
        opt->path = my_strcpy(opt->path, ".");
    }
    rep = opendir(opt->path);
    if (rep == NULL) {
        my_putstr("my_ls: cannot access '");
        my_putstr(opt->path);
        my_putstr("': ");
        my_putstr(strerror(errno));
        my_putchar('\n');
        return (84);
    }
    lecture = readdir(rep);
    while (lecture) {
        if (my_strlen(lecture->d_name) > len)
            len = my_strlen(lecture->d_name);
        total += my_strlen(lecture->d_name) + 2;
        lecture = readdir(rep);
        nbr++;
    }
    closedir(rep);
    if (total >= 212)
        opt->lines_display /= 212;
    opt->lines_display += 1;
    files = malloc(sizeof(char *) * nbr);
    for (int i = 0; i < nbr; i++)
        files[i] = malloc(sizeof(char) * (len + 1));
    rep = opendir(opt->path);
    lecture = readdir(rep);
    for (int i = 0; i < nbr; i++) {
        files[i] = my_strcpy(files[i], lecture->d_name);
        lecture = readdir(rep);
    }
    closedir(rep);
    files = option_a(files, nbr, len, opt);
    condition_display(ac, opt, nbr, files, av);
    return (0);
}
