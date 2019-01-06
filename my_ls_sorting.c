/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_sorting
*/

#include "my.h"

char **is_sorted(struct options *opt, int h, int i, int j)
{
    char *tmp = malloc(sizeof(char) * (opt->len + 1));

    if (lowcase(opt->files[h][j]) > lowcase(opt->files[i + 1][j])) {
        tmp = my_strcpy(tmp, opt->files[h]);
        opt->files[h] = my_strcpy(opt->files[h], opt->files[i + 1]);
        opt->files[i + 1] = my_strcpy(opt->files[i + 1], tmp);
        h--;
        return (opt->files);
    } else if (lowcase(opt->files[h][j]) == lowcase(opt->files[i + 1][j]))
        return (is_sorted(opt, h, i, j + 1));
    return (opt->files);
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

void create_files(struct options *opt)
{
    DIR *rep = opendir(opt->path);
    struct dirent *lecture;

    opt->files = malloc(sizeof(char *) * opt->nbr);
    for (int i = 0; i < opt->nbr; i++)
        opt->files[i] = malloc(sizeof(char) * (opt->len + 1));
    rep = opendir(opt->path);
    lecture = readdir(rep);
    for (int i = 0; i < opt->nbr; i++) {
        opt->files[i] = my_strcpy(opt->files[i], lecture->d_name);
        lecture = readdir(rep);
    }
    closedir(rep);
}