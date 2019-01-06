/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_display_l
*/

#include "my.h"

void display_l_permissions(struct stat statbuff)
{
    my_putstr((S_ISDIR(statbuff.st_mode)) ? "d" : "-");
    my_putstr((statbuff.st_mode & S_IRUSR) ? "r" : "-");
    my_putstr((statbuff.st_mode & S_IWUSR) ? "w" : "-");
    my_putstr((statbuff.st_mode & S_IXUSR) ? "x" : "-");
    my_putstr((statbuff.st_mode & S_IRGRP) ? "r" : "-");
    my_putstr((statbuff.st_mode & S_IWGRP) ? "w" : "-");
    my_putstr((statbuff.st_mode & S_IXGRP) ? "x" : "-");
    my_putstr((statbuff.st_mode & S_IROTH) ? "r" : "-");
    my_putstr((statbuff.st_mode & S_IWOTH) ? "w" : "-");
    my_putstr((statbuff.st_mode & S_IXOTH) ? "x" : "-");
    my_putchar(' ');
}

void display_l_links(struct stat statbuff, struct options *opt, int i)
{
    put_space_links(statbuff, opt->nbr, i, opt);
    my_put_nbr(statbuff.st_nlink);
    my_putchar(' ');
}

void display_l_owner_user(struct stat statbuff, struct options *opt)
{
    struct passwd *pwd = getpwuid(statbuff.st_uid);
    struct group *gr = getgrgid(statbuff.st_gid);

    if (opt->bool_n == 1)
        my_put_nbr(statbuff.st_uid);
    else
        my_putstr(pwd->pw_name);
    my_putchar(' ');
    if (opt->bool_n == 1)
        my_put_nbr(statbuff.st_gid);
    else if (opt->bool_o == 0) {
        my_putstr(gr->gr_name);
        my_putchar(' ');
    }
}

void display_l_size(struct stat statbuff, struct options *opt, int i)
{
    put_space_size(statbuff, opt->nbr, i, opt);
    my_put_nbr(statbuff.st_size);
    my_putchar(' ');
}