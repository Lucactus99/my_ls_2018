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

char **option_a(char **files, int nbr, int len)
{
    char *tmp = malloc(sizeof(char) * (len + 1));

    for (int h = 0; h < nbr; h++) {
        for (int i = h; i < nbr - 1; i++) {
            if (my_strlowcase(files[h][0]) > my_strlowcase(files[i + 1][0])) {
                tmp = my_strcpy(tmp, files[h]);
                files[h] = my_strcpy(files[h], files[i + 1]);
                files[i + 1] = my_strcpy(files[i + 1], tmp);
                h--;
                break;
            } else if (my_strlowcase(files[h][0]) ==
                       my_strlowcase(files[i + 1][0])) {
                if (my_strlowcase(files[h][1]) >
                    my_strlowcase(files[i + 1][1])) {
                    tmp = my_strcpy(tmp, files[h]);
                    files[h] = my_strcpy(files[h], files[i + 1]);
                    files[i + 1] = my_strcpy(files[i + 1], tmp);
                    h--;
                    break;
                }
            }
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
    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'a')
        files = option_a(files, nbr, len);
    for (int i = 0; i < nbr; i++)
        printf("%s  ", files[i]);
    printf("\n");
    return (0);
}