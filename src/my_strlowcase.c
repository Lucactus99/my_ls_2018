/*
** EPITECH PROJECT, 2018
** d
** File description:
** d
*/

char lowcase(char str)
{

    if (str > 64 && str < 91)
        str = (str + 32);
    return (str);
}