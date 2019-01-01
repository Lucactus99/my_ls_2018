/*
** EPITECH PROJECT, 2018
** d
** File description:
** d
*/

char my_strlowcase(char str)
{

    if (str > 64 && str < 91)
        str = (str + 32);
    return (str);
}