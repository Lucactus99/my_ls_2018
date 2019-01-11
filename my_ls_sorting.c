/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_sorting
*/

#include "my.h"

void swap_condition(struct options *opt, int nbr1, int nbr2, int j)
{
    if (nbr1 < nbr2)
        swap_str(&opt->files[j], &opt->files[j + 1]);
}

char **sort_by_time(struct options *opt)
{
    struct stat statbuff;
    int nbr1 = 0;
    int nbr2 = 0;

    for (int i = 0; i < opt->nbr - 1; i++) {
        for (int j = 0; j < opt->nbr - i - 1; j++) {
            find_path(&statbuff, opt, j);
            nbr1 = statbuff.st_mtime;
            find_path(&statbuff, opt, j + 1);
            nbr2 = statbuff.st_mtime;
            swap_condition(opt, nbr1, nbr2, j);
        }
    }
    return (opt->files);
}

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
    DIR *rep;
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