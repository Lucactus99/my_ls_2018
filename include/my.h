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

void my_putchar(char);
int my_putstr(char const *);
int my_strlen(char const *);
char *my_strcpy(char *dest, char const *src);
char my_strlowcase(char str);

#endif //MY_H_
