/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_sorting
*/

#include "my.h"

void swap_str(char **str1, char **str2)
{
    char *tmp;

    if (my_strlen(*str1) > my_strlen(*str2))
        tmp = malloc(sizeof(char) * (my_strlen(*str1) + 1));
    else
        tmp = malloc(sizeof(char) * (my_strlen(*str2) + 1));
    tmp = *str1;
    *str1 = *str2;
    *str2 = tmp;
}

void find_path(struct stat *statbuff, struct options *opt, int i)
{
    char *path_file =
    malloc(sizeof(char) * (my_strlen(opt->path) + opt->len + 1));

    path_file = my_strcpy(path_file, opt->path);
    path_file = my_strcat(path_file, opt->files[i]);
    if (stat(path_file, statbuff) < 0)
        exit(84);
}

void set_time_2(struct tm *timer, struct dates *dt, int nb)
{
    if (nb > 5)
        dt->sec2 = timer->tm_sec;
    if (nb > 4)
        dt->min2 = timer->tm_min;
    if (nb > 3)
        dt->hour2 = timer->tm_hour;
    if (nb > 2)
        dt->day2 = timer->tm_mday;
    if (nb > 1)
        dt->month2 = timer->tm_mon;
    if (nb > 0)
        dt->year2 = timer->tm_year;
}

void set_time_1(struct tm *timer, struct dates *dt, int nb)
{
    if (nb > 5)
        dt->sec1 = timer->tm_sec;
    if (nb > 4)
        dt->min1 = timer->tm_min;
    if (nb > 3)
        dt->hour1 = timer->tm_hour;
    if (nb > 2)
        dt->day1 = timer->tm_mday;
    if (nb > 1)
        dt->month1 = timer->tm_mon;
    if (nb > 0)
        dt->year1 = timer->tm_year;
}

char **sort_sec(struct stat statbuff, struct tm *timer, struct options *opt)
{
    struct dates *dt = malloc(sizeof(struct dates));

    for (int i = 0; i < opt->nbr - 1; i++) {
        for (int j = 0; j < opt->nbr - i - 1; j++) {
            find_path(&statbuff, opt, j);
            timer = localtime(&(statbuff.st_mtime));
            set_time_1(timer, dt, 6);
            find_path(&statbuff, opt, j + 1);
            timer = localtime(&(statbuff.st_mtime));
            set_time_2(timer, dt, 6);
            if (dt->sec1 < dt->sec2 && dt->min1 == dt->min2 &&
            dt->hour1 == dt->hour2 && dt->day1 == dt->day2 &&
            dt->month1 == dt->month2 && dt->year1 == dt->year2)
                swap_str(&opt->files[j], &opt->files[j + 1]);
        }
    }
    return (opt->files);
}

char **sort_min(struct stat statbuff, struct tm *timer, struct options *opt)
{
    struct dates *dt = malloc(sizeof(struct dates));

    for (int i = 0; i < opt->nbr - 1; i++) {
        for (int j = 0; j < opt->nbr - i - 1; j++) {
            find_path(&statbuff, opt, j);
            timer = localtime(&(statbuff.st_mtime));
            set_time_1(timer, dt, 5);
            find_path(&statbuff, opt, j + 1);
            timer = localtime(&(statbuff.st_mtime));
            set_time_2(timer, dt, 5);
            if (dt->min1 < dt->min2 && dt->hour1 == dt->hour2 &&
            dt->day1 == dt->day2 && dt->month1 == dt->month2 &&
            dt->year1 == dt->year2)
                swap_str(&opt->files[j], &opt->files[j + 1]);
        }
    }
    return (sort_sec(statbuff, timer, opt));
}

char **sort_hour(struct stat statbuff, struct tm *timer, struct options *opt)
{
    struct dates *dt = malloc(sizeof(struct dates));

    for (int i = 0; i < opt->nbr - 1; i++) {
        for (int j = 0; j < opt->nbr - i - 1; j++) {
            find_path(&statbuff, opt, j);
            timer = localtime(&(statbuff.st_mtime));
            set_time_1(timer, dt, 4);
            find_path(&statbuff, opt, j + 1);
            timer = localtime(&(statbuff.st_mtime));
            set_time_2(timer, dt, 4);
            if (dt->hour1 < dt->hour2 && dt->day1 == dt->day2
            && dt->month1 == dt->month2 && dt->year1 == dt->year2)
                swap_str(&opt->files[j], &opt->files[j + 1]);
        }
    }
    return (sort_min(statbuff, timer, opt));
}

char **sort_day(struct stat statbuff, struct tm *timer, struct options *opt)
{
    struct dates *dt = malloc(sizeof(struct dates));

    for (int i = 0; i < opt->nbr - 1; i++) {
        for (int j = 0; j < opt->nbr - i - 1; j++) {
            find_path(&statbuff, opt, j);
            timer = localtime(&(statbuff.st_mtime));
            set_time_1(timer, dt, 3);
            find_path(&statbuff, opt, j + 1);
            timer = localtime(&(statbuff.st_mtime));
            set_time_2(timer, dt, 3);
            if (dt->day1 < dt->day2 && dt->month1 == dt->month2
            && dt->year1 == dt->year2)
                swap_str(&opt->files[j], &opt->files[j + 1]);
        }
    }
    return (sort_hour(statbuff, timer, opt));
}

char **sort_month(struct stat statbuff, struct tm *timer, struct options *opt)
{
    struct dates *dt = malloc(sizeof(struct dates));

    for (int i = 0; i < opt->nbr - 1; i++) {
        for (int j = 0; j < opt->nbr - i - 1; j++) {
            find_path(&statbuff, opt, j);
            timer = localtime(&(statbuff.st_mtime));
            set_time_1(timer, dt, 2);
            find_path(&statbuff, opt, j + 1);
            timer = localtime(&(statbuff.st_mtime));
            set_time_2(timer, dt, 2);
            if (dt->month1 < dt->month2 && dt->year1 == dt->year2)
                swap_str(&opt->files[j], &opt->files[j + 1]);
        }
    }
    return (sort_day(statbuff, timer, opt));
}

char **sort_year(struct stat statbuff, struct tm *timer, struct options *opt)
{
    struct dates *dt = malloc(sizeof(struct dates));

    for (int i = 0; i < opt->nbr - 1; i++) {
        for (int j = 0; j < opt->nbr - i - 1; j++) {
            find_path(&statbuff, opt, j);
            timer = localtime(&(statbuff.st_mtime));
            set_time_1(timer, dt, 1);
            find_path(&statbuff, opt, j + 1);
            timer = localtime(&(statbuff.st_mtime));
            set_time_2(timer, dt, 1);
            if (dt->year1 < dt->year2)
                swap_str(&opt->files[j], &opt->files[j + 1]);
        }
    }
    return (sort_month(statbuff, timer, opt));
}

char **sort_by_time(struct options *opt)
{
    struct stat statbuff;
    struct tm *timer = localtime(&(statbuff.st_mtime));

    opt->files = sort_year(statbuff, timer, opt);
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