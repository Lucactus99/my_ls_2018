/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** main
*/

#include "my.h"
#include <dirent.h>
#include <pwd.h>
#include <sys/types.h>
#include <time.h>

char **is_sorted(char **files, int h, int i, int len, int j)
{
    char *tmp = malloc(sizeof(char) * (len + 1));

    if (my_strlowcase(files[h][j]) > my_strlowcase(files[i + 1][j])) {
        tmp = my_strcpy(tmp, files[h]);
        files[h] = my_strcpy(files[h], files[i + 1]);
        files[i + 1] = my_strcpy(files[i + 1], tmp);
        h--;
        return (files);
    } else if (my_strlowcase(files[h][j]) == my_strlowcase(files[i + 1][j])) {
        return (is_sorted(files, h, i, len, j + 1));
    }
    return (files);
}

char **option_a(char **files, int nbr, int len)
{
    for (int h = 0; h < nbr; h++) {
        for (int i = h; i < nbr - 1; i++) {
            files = is_sorted(files, h, i, len, 0);
        }
    }
    return (files);
}

void analyse_arg(int ac, char const *const *av, struct options *opt)
{
    for (int i = 1; i < ac; i++) {
        if (my_strlen(av[i]) == 2 && av[i][0] != '.') {
            if (av[i][1] == '1') {
                opt->bool_1 = 1;
            }
            if (av[i][1] == 'a') {
                opt->bool_a = 1;
            }
            if (av[i][1] == 'A') {
                opt->bool_a_maj = 1;
            }
            if (av[i][1] == 'd') {
                opt->bool_d = 1;
            }
        } else {
            opt->dir_bool = 1;
            opt->path = my_strcpy(opt->path, av[i]);
        }
    }
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
    if (rep == NULL)
        return (84);
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
    if (opt->bool_d == 1) {
        my_putstr(opt->path);
        my_putchar('\n');
        return (0);
    }
    if (ac == 1 || (ac == 2 && opt->dir_bool == 1)) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            if (files[i][0] != '.') {
                my_putstr(files[i]);
                if (i + 1 < nbr)
                    my_putstr("  ");
            }
        }
        my_putchar('\n');
        return (0);
    }
    if (opt->bool_1 == 1 && opt->bool_a == 1) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            my_putstr(files[i]);
            my_putchar('\n');
        }
        return (0);
    }
    if (opt->bool_1 == 1) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            if (files[i][0] != '.') {
                my_putstr(files[i]);
                my_putchar('\n');
            }
        }
        return (0);
    }
    if (opt->bool_a == 1) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            my_putstr(files[i]);
            my_putstr("  ");
        }
        my_putchar('\n');
        return (0);
    }
    if (opt->bool_a_maj == 1) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            if (my_strcmp(files[i], ".") != 0 && my_strcmp(files[i], "..") != 0) {
                my_putstr(files[i]);
                my_putstr("  ");
            }
        }
        my_putchar('\n');
        return (0);
    }
    if (ac == 2 && my_strcmp(av[1], "-1a") == 0) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            my_putstr(files[i]);
            my_putchar('\n');
        }
    }
    return (0);
}