/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:52:59 by fgoulama          #+#    #+#             */
/*   Updated: 2020/02/11 21:53:45 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			write_err(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

void		free_all(char *ts, char *id, char *end, char *status)
{
	free(ts);
	free(id);
	free(status);
	free(end);
}

char		*get_end(int action)
{
	char	*end;

	end = NULL;
	if (action == EAT)
		end = ft_strdup(" is eating\n");
	else if (action == SLEEP)
		end = ft_strdup(" is sleeping\n");
	else if (action == THINK)
		end = ft_strdup(" is thinking\n");
	else if (action == DIE)
		end = ft_strdup(" died\n");
	return (end);
}

void		write_status(long timestamp, int id, int action)
{
	char	*status;
	char	*ts_str;
	char	*id_str;
	char	*end;
	char	*tmp;

	ts_str = ft_itoa((int)timestamp);
	id_str = ft_itoa(id);
	end = get_end(action);
	tmp = ft_strjoin(ts_str, " ");
	status = ft_strjoin(tmp, id_str);
	free(tmp);
	tmp = status;
	status = ft_strjoin(tmp, end);
	free(tmp);
	sem_wait(g_write_sem);
	write(1, status, ft_strlen(status));
	sem_post(g_write_sem);
	free_all(ts_str, id_str, end, status);
}
