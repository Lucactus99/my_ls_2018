/*
** EPITECH PROJECT, 2019
** PSU_my_ls_2018
** File description:
** my_ls_print_month
*/

#include "my.h"

void print_month_2(struct tm *timer)
{
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

void print_month(struct tm *timer)
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
    print_month_2(timer);
}