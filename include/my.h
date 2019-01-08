/*
** EPITECH PROJECT, 2018
** h
** File description:
** h
*/

#ifndef MY_H_
#define MY_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>

struct dates
{
    int year1;
    int month1;
    int day1;
    int hour1;
    int min1;
    int sec1;
    int year2;
    int month2;
    int day2;
    int hour2;
    int min2;
    int sec2;
};

struct options
{
    int nbr;
    int len;
    int dir_bool;
    int bool_a;
    int bool_a_maj;
    int bool_d;
    int bool_f;
    int bool_i;
    int bool_1;
    int bool_l;
    int bool_m;
    int bool_n;
    int bool_o;
    int bool_p;
    int bool_r;
    int bool_tt;
    long total_size;
    char *path;
    char **files;
    int lines_display;
};

void my_putchar(char);
int my_putstr(char const *);
int my_strlen(char const *);
char *my_strcpy(char *dest, char const *src);
char lowcase(char str);
int my_strcmp(char const *s1, char const *s2);
char *my_strcat(char *dest, char const *src);
int my_getnbr(char *str);
int my_put_nbr(int nb);
void analyse_arg(int, char const * const *, struct options *);
void option_a(struct options *);
void put_space_size(struct stat, int, int, struct options *);
void put_space_links(struct stat, int, int, struct options *);
void print_month(struct tm *);
void display_ls(struct options *);
void display_l(struct options *);
void display_a(char **, int, struct options *);
void display_a_maj(char **, int);
void display_d(struct options *);
void display_l_permissions(struct stat);
void display_l_links(struct stat, struct options *, int);
void display_l_owner_user(struct stat, struct options *);
void display_l_size(struct stat, struct options *, int);
void display_l_time(struct stat);
void display_l_total_size(int, struct options *, struct stat);
void create_files(struct options *);
void condition_display(int, struct options *, char const *const *);
void check_invalid_option(int, char const *const *);
void display_i(struct options *, struct stat);
void find_path(struct stat *statbuff, struct options *opt, int i);
char **sort_by_time(struct options *opt);
char **is_sorted(struct options *, int, int, int);
char **reverse_str(char **, int, int);
void print_file(char *file);
void swap_str(char **str1, char **str2);

#endif //MY_H_