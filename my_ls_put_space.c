/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_put_space
*/

#include "my.h"

void put_space_size(struct stat statbuff, int nbr, char **files, int a)
{
    int length_files[nbr];
    int lengthMax = 0;
    int number = 0;

    for (int i = 0; i < nbr; i++) {
        length_files[i] = 0;
        stat(files[i], &statbuff);
        number = statbuff.st_size;
        for (int j = 0; number != 0; j++) {
            length_files[i] += 1;
            number /= 10;
        }
        if (length_files[i] > lengthMax)
            lengthMax = length_files[i];
    }
    stat(files[a], &statbuff);
    number = statbuff.st_size;
    my_putchar(' ');
    for (int j = 0; j < lengthMax - length_files[a]; j++)
        my_putchar(' ');
}

void put_space_day_2(int length_file, struct tm *timer, int lengthMax, struct options *opt, int nbr)
{
    int number = 0;

    for (int i = 0; i < nbr; i++) {
        length_file = 0;
        number = timer->tm_mday;
        for (int j = 0; number != 0; j++) {
            length_file += 1;
            number /= 10;
        }
    }
    number = timer->tm_mday;
    for (int j = 0; j < lengthMax + length_file + opt->bool_a - opt->bool_f - length_file - 1; j++)
        my_putchar(' ');
}

void put_space_day(struct tm *timer, int nbr, struct options *opt)
{
    int length_file = 0;
    static int lengthMax = 0;
    int number = 0;

    if (lengthMax == 0) {
        for (int i = 0; i < nbr; i++) {
            length_file = 0;
            number = timer->tm_mday;
            for (int j = 0; number != 0; j++) {
                length_file += 1;
                number /= 10;
            }
            if (length_file > lengthMax)
                lengthMax = length_file;
        }
        lengthMax++;
    }
    put_space_day_2(length_file, timer, lengthMax, opt, nbr);
}