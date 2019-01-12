/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_display_permissions
*/

#include "my.h"

int is_link(struct options *opt, int i)
{
    char buf[30];
    char *tmp = malloc(sizeof(char) * my_strlen(opt->path)
    + my_strlen(opt->files[i]));

    tmp = my_strcpy(tmp, opt->path);
    tmp = my_strcat(tmp, opt->files[i]);
    if (readlink(tmp, buf, sizeof(buf)) >= 0)
        return (1);
    return (0);
}

char display_perm(struct stat statbuff, struct options *opt, int i)
{
    char c = 'z';

    if ((statbuff.st_mode & __S_IFLNK) != 0) {
        if (is_link(opt, i) != 0)
            c = 'l';
    }
    if ((statbuff.st_mode & __S_IFIFO) != 0)
        c = 'p';
    if ((statbuff.st_mode & __S_IFBLK) != 0)
        c = 'b';
    if ((statbuff.st_mode & __S_IFCHR) != 0)
        c = 'c';
    if ((statbuff.st_mode & __S_IFDIR) != 0)
        c = 'd';
    if (c == 'z')
        c = '-';
    my_putchar(c);
    return (c);
}

void display_rwx(struct stat statbuff)
{
    ((statbuff.st_mode & S_IRUSR) != 0) ? my_putchar('r') : my_putchar('-');
    ((statbuff.st_mode & S_IWUSR) != 0) ? my_putchar('w') : my_putchar('-');
    ((statbuff.st_mode & S_IXUSR) != 0) ? my_putchar('x') : my_putchar('-');
    ((statbuff.st_mode & S_IRGRP) != 0) ? my_putchar('r') : my_putchar('-');
    ((statbuff.st_mode & S_IWGRP) != 0) ? my_putchar('w') : my_putchar('-');
    ((statbuff.st_mode & S_IXGRP) != 0) ? my_putchar('x') : my_putchar('-');
    ((statbuff.st_mode & S_IROTH) != 0) ? my_putchar('r') : my_putchar('-');
    ((statbuff.st_mode & S_IWOTH) != 0) ? my_putchar('w') : my_putchar('-');
}

void display_l_permissions(struct stat statbuff, struct options *opt, int i)
{
    if (display_perm(statbuff, opt, i) != 'l') {
        display_rwx(statbuff);
        if ((statbuff.st_mode & S_IXOTH) != 0 &&
        (statbuff.st_mode & __S_ISVTX) == 0)
            my_putchar('x');
        else if ((statbuff.st_mode & __S_ISVTX) != 0 &&
        (statbuff.st_mode & S_IXOTH) != 0)
            my_putchar('t');
        else if ((statbuff.st_mode & __S_ISVTX) != 0 &&
        (statbuff.st_mode & S_IXOTH) == 0)
            my_putchar('T');
        else
            my_putchar('-');
    } else {
        my_putstr("rwxrwxrwx");
    }
}