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

    for (int i = 0; i < nbr; i++) {
        length_files[i] = 0;
        find_path(&statbuff, opt, i);
        number = statbuff.st_size;
        for (int j = 0; number != 0; j++) {
            length_files[i] += 1;
            number /= 10;
        }
        if (length_files[i] > lengthMax)
            lengthMax = length_files[i];
    }
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

    for (int i = 0; i < nbr; i++) {
        length_files[i] = 0;
        find_path(&statbuff, opt, i);
        timer = my_localtime(&(statbuff.st_mtime));
        number = timer->tm_mday;
        for (int j = 0; number != 0; j++) {
            length_files[i] += 1;
            number /= 10;
        }
        if (length_files[i] > lengthMax)
            lengthMax = length_files[i];
    }
    my_putchar(' ');
    for (int j = 0; j < lengthMax - length_files[a]; j++)
        my_putchar(' ');
}

void put_space_links(struct stat statbuff, int nbr, int a, struct options *opt)
{
    int length_files[nbr];
    int lengthMax = 0;
    int number = 0;

    for (int i = 0; i < nbr; i++) {
        length_files[i] = 0;
        find_path(&statbuff, opt, i);
        number = statbuff.st_nlink;
        for (int j = 0; number != 0; j++) {
            length_files[i] += 1;
            number /= 10;
        }
        if (length_files[i] > lengthMax)
            lengthMax = length_files[i];
    }
    for (int j = 0; j < lengthMax - length_files[a]; j++)
        my_putchar(' ');
}