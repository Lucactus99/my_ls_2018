/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_display_R
*/

#include "my.h"

int count_slash(char *str)
{
    int nbr = 0;

    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '/')
            nbr++;
    }
    return (nbr);
}

char *get_actual_path(char *str)
{
    int count = 0;
    int i = 0;
    int a = 0;
    char *s = malloc(sizeof(char) * my_strlen(str));

    while (count < count_slash(str) - 1) {
        if (str[i] == '/')
            count++;
        i++;
    }
    for (; str[i] != '/'; a++) {
        s[a] = str[i];
        i++;
    }
    s[a] = '/';
    return (s);
}

void display_list_r_2(struct options *opt, int i, struct stat statbuff, char *path_file)
{
    struct stat underbuff;
    int is_dir = 0;
    char *tmp = malloc(sizeof(char) * 100);
    char *s = malloc(sizeof(char) * 100);

    tmp = my_strcpy(tmp, path_file);
    tmp = my_strcat(tmp, "/");
    tmp = my_strcat(tmp, opt->files[i]);
    //printf("=>%s\n", tmp);
    if (stat(tmp, &underbuff) >= 0)
        is_dir = S_ISDIR(underbuff.st_mode);
    display_i(opt, statbuff);
    print_file(opt->files[i]);
    //printf("%d\n", S_ISDIR(underbuff.st_mode));
    if (is_dir == 1 && count_slash(tmp) >= 3) {
        s = get_actual_path(tmp);
        my_putchar('\n');
        my_putchar('\n');
        my_putstr(tmp);
        my_putchar(':');
        my_putchar('\n');
        get_elements(opt, i, s);
        create_files(opt, i, s);
        //display_list_r(opt, tmp);
        // get_elements(opt, -1, NULL);
        // create_files(opt, -1, NULL);
    }
    if (i + 1 < opt->nbr) {
        if (opt->bool_m == 1) {
            my_putchar(44);
            my_putchar(' ');
        } else if (opt->bool_1 == 1)
            my_putchar('\n');
        else {
            my_putchar(' ');
            my_putchar(' ');
        }
    }
}

void display_list_r(struct options *opt, char *path_file)
{
    struct stat statbuff;

    for (int i = 0; i < opt->nbr; i++) {
        stat(path_file, &statbuff);
        if (opt->files[i][0] != '.' || opt->bool_a == 1)
            display_list_r_2(opt, i, statbuff, path_file);
    }
    my_putchar('\n');
}

void putstr_slash(char *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] != '/' || str[i + 1] != '\0')
            my_putchar(str[i]);
    }
}

void display_r(struct options *opt, int i)
{
    struct stat statbuff;
    char *path_file = malloc(sizeof(char) *
    (my_strlen(opt->path) + opt->len + 1));

    if (i == -1) {
        my_putstr(opt->path);
        my_putchar(':');
        my_putchar('\n');
        display_list_r(opt, path_file);
        display_r(opt, i + 1);
    }
    for (; i < opt->nbr - 1; i++) {
        path_file = my_strcpy(path_file, opt->path);
        path_file = my_strcat(path_file, opt->files[i]);
        stat(path_file, &statbuff);
        if (opt->files[i][0] != '.' || opt->bool_a == 1) {
            if (S_ISDIR(statbuff.st_mode)) {
                my_putchar('\n');
                my_putstr(path_file);
                my_putchar(':');
                my_putchar('\n');
                get_elements(opt, i, NULL);
                create_files(opt, i, NULL);
                display_list_r(opt, path_file);
                get_elements(opt, -1, NULL);
                create_files(opt, -1, NULL);
                display_r(opt, i + 1);
            }
        }
    }
    exit(0);
}