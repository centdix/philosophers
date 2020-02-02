#include "header.h"

int         ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void        ft_putnbr(int nb)
{
    char c;

    if (nb >= 10)
        ft_putnbr(nb / 10);
    c = nb % 10 + '0';
    write(1, &c, 1);
}

int         write_err(char *str)
{
    write(1, str, ft_strlen(str));
    return (1);
}

void        write_status(long timestamp, int id, int action)
{
    char    *status;
    char    *ts_str;
    char    *id_str;

    if (action == EAT)
    {
        ts_str = ft_itoa((int)timestamp);
        status = ft_strcpy(ts_str);
        status += ft_strlen(ts_str);
    }
}