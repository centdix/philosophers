#include "header.h"

int         write_err(char *str)
{
    write(1, str, ft_strlen(str));
    return (1);
}

void        free_all(char *ts, char *id, char *end, char *status)
{
    free(ts);
    free(id);
    free(status);
    free(end);
}

void        write_status(long timestamp, int id, int action)
{
    char    *status;
    char    *ts_str;
    char    *id_str;
    char    *end;
    char    *tmp;

    ts_str = ft_itoa((int)timestamp);
    id_str = ft_itoa(id);
    end = NULL;
    if (action == EAT)
        end = ft_strdup(" is eating\n");
    else if (action == SLEEP)
        end = ft_strdup(" is sleeping\n");
    else if (action == THINK)
        end = ft_strdup(" is thinking\n");
    else if (action == DIE)
        end = ft_strdup(" died\n");
    tmp = ft_strjoin(ts_str, " ");
    status = ft_strjoin(tmp, id_str);
    free(tmp);
    tmp = status;
    status = ft_strjoin(tmp, end);
    free(tmp);
    write(1, status, ft_strlen(status));
    free_all(ts_str, id_str, end, status);
}