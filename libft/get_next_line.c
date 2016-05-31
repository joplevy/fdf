/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 15:41:04 by jplevy            #+#    #+#             */
/*   Updated: 2016/04/30 04:04:40 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int			ft_indexof(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == 26)
			return (i);
		i++;
	}
	return (-2);
}

int			get_chars(char *buff, char **str)
{
	char	*tmp;

	if (!(tmp = ft_strdup(*str)))
		return (-1);
	free(*str);
	if (!(*str = ft_strjoin(tmp, buff)))
		return (-1);
	free(tmp);
	free(buff);
	return (ft_indexof(*str));
}

int			ft_result(char **line, char **str, int n)
{
	char	*tmp;

	if (n == -2)
		n = ft_strlen(*str);
	if (!(tmp = ft_strdup(*str)))
		return (-1);
	free(*str);
	*line = ft_strsub(tmp, 0, n);
	*str = ((n == (int)ft_strlen(tmp)) ? ft_strnew(0) : \
		ft_strsub(tmp, n + 1, ft_strlen(tmp) - n));
	free(tmp);
	return (1);
}

t_list_fd	*ft_fd_finder(t_list_fd **mem, int fd)
{
	t_list_fd	*tmp1;

	tmp1 = *mem;
	if (tmp1 == NULL)
	{
		if (!(tmp1 = (t_list_fd *)malloc(sizeof(t_list_fd))) ||
			!(tmp1->line = ft_strnew(0)))
			return (NULL);
		tmp1->fd = fd;
		tmp1->next = NULL;
		*mem = tmp1;
	}
	while (tmp1->fd != fd)
	{
		if (tmp1->next == NULL)
		{
			if (!(tmp1->next = (t_list_fd *)malloc(sizeof(t_list_fd))) ||\
			!(tmp1->next->line = ft_strnew(0)))
				return (NULL);
			tmp1->next->fd = fd;
			tmp1->next->next = NULL;
		}
		tmp1 = tmp1->next;
	}
	return (tmp1);
}

int			get_next_line(int const fd, char **line)
{
	int					i;
	int					j;
	static t_list_fd	*mem = NULL;
	t_list_fd			*tmp;
	char				*buffer;

	if (fd < 0)
		return (-1);
	if (!(buffer = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (!(tmp = ft_fd_finder(&mem, fd)))
		return (-1);
	if ((j = ft_indexof(tmp->line)) != -2)
		return (ft_result(line, &(tmp->line), j));
	i = read(fd, buffer, BUFF_SIZE);
	if ((j = get_chars(buffer, &(tmp->line))) == -1 || i == -1)
		return (-1);
	if (i == 0 && ft_strlen(tmp->line) == 0)
		return (0);
	if (j == -2 && i != 0)
		return (get_next_line(fd, line));
	else
		return (ft_result(line, &(tmp->line), j));
}
