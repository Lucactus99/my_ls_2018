/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_display_l
*/

#include "my.h"

void display_l_permissions(struct stat statbuff)
{
    if (S_ISCHR(statbuff.st_mode))
        my_putchar('c');
    else if (S_ISDIR(statbuff.st_mode))
        my_putchar('d');
    else
        my_putstr(S_ISBLK(statbuff.st_mode) ? "b" : "-");
    my_putstr((statbuff.st_mode & S_IRUSR) ? "r" : "-");
    my_putstr((statbuff.st_mode & S_IWUSR) ? "w" : "-");
    my_putstr((statbuff.st_mode & S_IXUSR) ? "x" : "-");
    my_putstr((statbuff.st_mode & S_IRGRP) ? "r" : "-");
    my_putstr((statbuff.st_mode & S_IWGRP) ? "w" : "-");
    my_putstr((statbuff.st_mode & S_IXGRP) ? "x" : "-");
    my_putstr((statbuff.st_mode & S_IROTH) ? "r" : "-");
    my_putstr((statbuff.st_mode & S_IWOTH) ? "w" : "-");
    if (statbuff.st_mode & __S_ISVTX)
        my_putchar('t');
    else if (statbuff.st_mode & S_IXOTH)
        my_putchar('x');
    else
        my_putchar('-');
}

void display_l_links(struct stat statbuff, struct options *opt, int i)
{
    my_putchar(' ');
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

void display_l_size_2(struct stat statbuff, struct options *opt, int i)
{
    if (S_ISBLK(statbuff.st_mode)) {
        put_space_size(statbuff, opt->nbr, i, opt);
        my_put_nbr(major(statbuff.st_rdev));
        my_putchar(44);
        put_space_size(statbuff, opt->nbr, i, opt);
        my_put_nbr(minor(statbuff.st_rdev));
        my_putchar(' ');
        return;
    }
    put_space_size(statbuff, opt->nbr, i, opt);
    my_put_nbr(statbuff.st_size);
    my_putchar(' ');
}

void display_l_size(struct stat statbuff, struct options *opt, int i)
{
    if (S_ISCHR(statbuff.st_mode)) {
        put_space_size(statbuff, opt->nbr, i, opt);
        my_put_nbr(major(statbuff.st_rdev));
        my_putchar(44);
        put_space_size(statbuff, opt->nbr, i, opt);
        my_put_nbr(minor(statbuff.st_rdev));
        my_putchar(' ');
        return;
    }
    if (S_ISDIR(statbuff.st_mode)) {
        put_space_size(statbuff, opt->nbr, i, opt);
        my_put_nbr(statbuff.st_size);
        my_putchar(' ');
        return;
    }
    display_l_size_2(statbuff, opt, i);
}