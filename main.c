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

int main(int ac, char const *const *av)
{
    DIR *rep = opendir(".");
    struct dirent *lecture = readdir(rep);
    int nbr = 0;
    int len = 0;
    char **files;

    while (lecture) {
        if (my_strlen(lecture->d_name) > len)
            len = my_strlen(lecture->d_name);
        lecture = readdir(rep);
        nbr++;
    }
    closedir(rep);
    files = malloc(sizeof(char *) * nbr);
    for (int i = 0; i < nbr; i++)
        files[i] = malloc(sizeof(char) * (len + 1));
    rep = opendir(".");
    lecture = readdir(rep);
    for (int i = 0; i < nbr; i++) {
        files[i] = my_strcpy(files[i], lecture->d_name);
        lecture = readdir(rep);
    }
    closedir(rep);
    if (ac == 1) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            if (files[i][0] != '.') {
                my_putstr(files[i]);
                if (i + 1 < nbr)
                    my_putstr("  ");
            }
        }
        my_putchar('\n');
    }
    if (ac == 2 && my_strcmp(av[1], "-1") == 0) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            if (files[i][0] != '.') {
                my_putstr(files[i]);
                my_putchar('\n');
            }
        }
    }
    if (ac == 2 && my_strcmp(av[1], "-a") == 0) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            my_putstr(files[i]);
            my_putstr("  ");
        }
        my_putchar('\n');
    }
    if (ac == 2 && my_strcmp(av[1], "-1a") == 0) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            my_putstr(files[i]);
            my_putchar('\n');
        }
    }
    if (ac == 3 && my_strcmp(av[1], "-a") == 0 && my_strcmp(av[2], "-1") == 0) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            my_putstr(files[i]);
            my_putchar('\n');
        }
    }
    if (ac == 3 && my_strcmp(av[1], "-1") == 0 && my_strcmp(av[2], "-a") == 0) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            my_putstr(files[i]);
            my_putchar('\n');
        }
    }
    return (0);
}