/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_put_space
*/

#include "my.h"

void put_space_size(struct stat statbuff, int nbr, int a, struct options *opt)
{
    int length_files[nbr];
    int lengthMax = 0;
    int number = 0;
    char *path_file = malloc(sizeof(char) *
    (my_strlen(opt->path) + opt->len + 1));

    for (int i = 0; i < nbr; i++) {
        length_files[i] = 0;
        path_file = my_strcpy(path_file, opt->path);
        path_file = my_strcat(path_file, opt->files[i]);
        stat(path_file, &statbuff);
        number = statbuff.st_size;
        for (int j = 0; number != 0; j++) {
            length_files[i] += 1;
            number /= 10;
        }
        if (length_files[i] > lengthMax)
            lengthMax = length_files[i];
    }
    stat(path_file, &statbuff);
    number = statbuff.st_size;
    if (length_files[a] == 0)
        length_files[a]++;
    for (int j = 0; j < lengthMax - length_files[a]; j++)
        my_putchar(' ');
}

void put_space_day(struct stat statbuff, int nbr, int a, struct options *opt)
{
    struct tm *timer;
    int length_files[nbr];
    int lengthMax = 0;
    int number = 0;
    char *path_file = malloc(sizeof(char) *
    (my_strlen(opt->path) + opt->len + 1));

    for (int i = 0; i < nbr; i++) {
        length_files[i] = 0;
        path_file = my_strcpy(path_file, opt->path);
        path_file = my_strcat(path_file, opt->files[i]);
        stat(path_file, &statbuff);
        timer = localtime(&(statbuff.st_mtime));
        number = timer->tm_mday;
        for (int j = 0; number != 0; j++) {
            length_files[i] += 1;
            number /= 10;
        }
        if (length_files[i] > lengthMax)
            lengthMax = length_files[i];
    }
    stat(path_file, &statbuff);
    timer = localtime(&(statbuff.st_mtime));
    number = timer->tm_mday;
    my_putchar(' ');
    for (int j = 0; j < lengthMax - length_files[a]; j++)
        my_putchar(' ');
}

void put_space_links(struct stat statbuff, int nbr, int a, struct options *opt)
{
    int length_files[nbr];
    int lengthMax = 0;
    int number = 0;
    char *path_file = malloc(sizeof(char) *
    (my_strlen(opt->path) + opt->len + 1));

    for (int i = 0; i < nbr; i++) {
        length_files[i] = 0;
        path_file = my_strcpy(path_file, opt->path);
        path_file = my_strcat(path_file, opt->files[i]);
        stat(path_file, &statbuff);
        number = statbuff.st_nlink;
        for (int j = 0; number != 0; j++) {
            length_files[i] += 1;
            number /= 10;
        }
        if (length_files[i] > lengthMax)
            lengthMax = length_files[i];
    }
    stat(path_file, &statbuff);
    number = statbuff.st_nlink;
    for (int j = 0; j < lengthMax - length_files[a]; j++)
        my_putchar(' ');
}