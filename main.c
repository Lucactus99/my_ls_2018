/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** main
*/

#include "my.h"

char **is_sorted(char **files, int h, int i, int len, int j)
{
    char *tmp = malloc(sizeof(char) * (len + 1));

    if (my_strlowcase(files[h][j]) > my_strlowcase(files[i + 1][j])) {
        tmp = my_strcpy(tmp, files[h]);
        files[h] = my_strcpy(files[h], files[i + 1]);
        files[i + 1] = my_strcpy(files[i + 1], tmp);
        h--;
        return (files);
    } else if (my_strlowcase(files[h][j]) == my_strlowcase(files[i + 1][j])) {
        return (is_sorted(files, h, i, len, j + 1));
    }
    return (files);
}

char **option_a(char **files, int nbr, int len)
{
    for (int h = 0; h < nbr; h++) {
        for (int i = h; i < nbr - 1; i++) {
            files = is_sorted(files, h, i, len, 0);
        }
    }
    return (files);
}

void analyse_arg(int ac, char const *const *av, struct options *opt)
{
    for (int i = 1; i < ac; i++) {
        if (my_strlen(av[i]) < 4 && av[i][0] != '.') {
            if (av[i][1] == '1') {
                opt->bool_1 = 1;
            }
            if (av[i][1] == 'a') {
                opt->bool_a = 1;
            }
            if (av[i][1] == 'A') {
                opt->bool_a_maj = 1;
            }
            if (av[i][1] == 'd') {
                opt->bool_d = 1;
            }
            if (av[i][1] == 'l') {
                opt->bool_l = 1;
            }
            if (my_strcmp(av[i], "-la") == 0) {
                opt->bool_l = 1;
                opt->bool_a = 1;
            }
        } else {
            opt->dir_bool = 1;
            opt->path = my_strcpy(opt->path, av[i]);
        }
    }
}

void put_space(struct stat statbuff, int nbr, char **files, int a)
{
    int length_files[nbr];
    int lengthMax = 0;
    int number = 0;

    for (int i = 0; i < nbr; i++)
        length_files[i] = 0;
    for (int i = 0; i < nbr; i++) {
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
    for (int j = 0; j < lengthMax - length_files[a]; j++) {
        my_putchar(' ');
    }
}

void put_space_day(struct tm *timer, int nbr)
{
    int length_file = 0;
    static int lengthMax = 0;
    int number = 0;

    if (lengthMax == 0) {
        for (int i = 0; i < nbr; i++) {
            number = timer->tm_mday;
            for (int j = 0; number != 0; j++) {
                length_file += 1;
                number /= 10;
            }
            if (length_file > lengthMax)
                lengthMax = length_file;
            length_file = 0;
        }
        lengthMax++;        
    }
    number = timer->tm_mday;
    for (int j = 0; j < lengthMax - length_file; j++) {
        my_putchar(' ');
    }
}

void print_modif_month(struct tm *timer)
{
    if (timer->tm_mon == 0)
        my_putstr("janv.");
    if (timer->tm_mon == 1)
        my_putstr("fév.");
    if (timer->tm_mon == 2)
        my_putstr("mar.");
    if (timer->tm_mon == 3)
        my_putstr("avr.");
    if (timer->tm_mon == 4)
        my_putstr("mai.");
    if (timer->tm_mon == 5)
        my_putstr("juin.");
    if (timer->tm_mon == 6)
        my_putstr("juil.");
    if (timer->tm_mon == 7)
        my_putstr("aout.");
    if (timer->tm_mon == 8)
        my_putstr("sep.");
    if (timer->tm_mon == 9)
        my_putstr("oct.");
    if (timer->tm_mon == 10)
        my_putstr("nov.");
    if (timer->tm_mon == 11)
        my_putstr("déc.");
}

int main(int ac, char const *const *av)
{
    struct options *opt = malloc(sizeof(struct options));
    DIR *rep;
    struct dirent *lecture;
    int nbr = 0;
    int len = 0;
    int total = 0;
    char **files;
    struct stat statbuff;
    struct tm *timer;
    struct passwd *pwd;
    struct group *gr;

    opt->path = malloc(sizeof(char) * 10);
    analyse_arg(ac, av, opt);
    if (opt->dir_bool == 0) {
        opt->path = my_strcpy(opt->path, ".");
    }
    rep = opendir(opt->path);
    if (rep == NULL) {
        my_putstr("my_ls: cannot access '");
        my_putstr(opt->path);
        my_putstr("': ");
        my_putstr(strerror(errno));
        my_putchar('\n');
        return (84);
    }
    lecture = readdir(rep);
    while (lecture) {
        if (my_strlen(lecture->d_name) > len)
            len = my_strlen(lecture->d_name);
        total += my_strlen(lecture->d_name) + 2;
        lecture = readdir(rep);
        nbr++;
    }
    closedir(rep);
    if (total >= 212)
        opt->lines_display /= 212;
    opt->lines_display += 1;
    files = malloc(sizeof(char *) * nbr);
    for (int i = 0; i < nbr; i++)
        files[i] = malloc(sizeof(char) * (len + 1));
    rep = opendir(opt->path);
    lecture = readdir(rep);
    for (int i = 0; i < nbr; i++) {
        files[i] = my_strcpy(files[i], lecture->d_name);
        lecture = readdir(rep);
    }
    closedir(rep);
    if (opt->bool_d == 1) {
        my_putstr(opt->path);
        my_putchar('\n');
        return (0);
    }
    if (ac == 1 || (ac == 2 && opt->dir_bool == 1)) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            if (files[i][0] != '.') {
                my_putstr(files[i]);
                if (i + 1 < nbr)
                    my_putstr("  ");
            }
        }
        my_putchar('\n');
        return (0);
    }
    if (opt->bool_l == 1) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            if (files[i][0] != '.') {
                stat(files[i], &statbuff);
                opt->total_size += statbuff.st_blocks / 2;
            }
        }
        my_putstr("total ");
        my_put_nbr(opt->total_size);
        my_putchar('\n');
        pwd = getpwuid(statbuff.st_uid);
        gr = getgrgid(statbuff.st_gid);
        for (int i = 0; i < nbr; i++) {
            if (files[i][0] != '.' || opt->bool_a == 1) {
                stat(files[i], &statbuff);
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
                my_put_nbr(statbuff.st_nlink);
                my_putchar(' ');
                my_putstr(pwd->pw_name);
                my_putchar(' ');
                my_putstr(gr->gr_name);
                put_space(statbuff, nbr, files, i);
                my_put_nbr(statbuff.st_size);
                my_putchar(' ');
                timer = localtime(&(statbuff.st_mtime));
                print_modif_month(timer);
                put_space_day(timer, nbr);
                my_put_nbr(timer->tm_mday);
                my_putchar(' ');
                my_put_nbr(timer->tm_hour);
                my_putchar(':');
                my_put_nbr(timer->tm_min);
                my_putchar(' ');
                my_putstr(files[i]);
                my_putchar('\n');
            }
        }
        return (0);
    }
    if (opt->bool_1 == 1 && opt->bool_a == 1) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            my_putstr(files[i]);
            my_putchar('\n');
        }
        return (0);
    }
    if (opt->bool_1 == 1) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            if (files[i][0] != '.') {
                my_putstr(files[i]);
                my_putchar('\n');
            }
        }
        return (0);
    }
    if (opt->bool_a == 1) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            my_putstr(files[i]);
            my_putstr("  ");
        }
        my_putchar('\n');
        return (0);
    }
    if (opt->bool_a_maj == 1) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            if (my_strcmp(files[i], ".") != 0 &&
                my_strcmp(files[i], "..") != 0) {
                my_putstr(files[i]);
                my_putstr("  ");
            }
        }
        my_putchar('\n');
        return (0);
    }
    if (ac == 2 && my_strcmp(av[1], "-1a") == 0) {
        files = option_a(files, nbr, len);
        for (int i = 0; i < nbr; i++) {
            my_putstr(files[i]);
            my_putchar('\n');
        }
    }
    return (0);
}
