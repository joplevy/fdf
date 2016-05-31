/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:29:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/05/16 18:36:16 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_get_coord(char *line, int y, t_list **map)
{
	t_coord	c;
	char	**tab;

	c.x = -1;
	c.y = y;
	tab = ft_strsplit(line, ' ');
	while (tab[++(c.x)])
	{
		c.z = ft_atoi(tab[c.x]);
		ft_lstadd(map, ft_lstnew(&c, sizeof(c)));
	}
	free(tab);
}

t_list	*ft_get_map(char *input)
{
	int		fd;
	t_list	*ret;
	char	*line;
	int		y;

	y = 0;
	ret = NULL;
	fd = open(input, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		ft_get_coord(line, y++, &ret);
	close(fd);
	return (ret);
}

t_point	ft_get_point(t_coord *data, t_coord max)
{
	t_point	ret;

	ret.x = ((double)data->x + cos(45) * (max.y - (double)data->y)) * 20;
	ret.y = 500 - (((double)data->z + sin(45) *\
		(max.y - (double)data->y)) * 20);
	return (ret);
}

t_point	**ft_tab(t_list *map, t_coord max)
{
	t_list	*tmp;
	t_coord	*data;
	t_point	**ret;
	int		y;

	y = -1;
	if (!(ret = (t_point**)malloc(sizeof(t_point*) * (max.y + 2))))
		return (NULL);
	while (++y <= max.y)
		if (!(ret[y] = (t_point*)malloc(sizeof(t_point) * (max.x + 2))))
			return (NULL);
	tmp = map;
	while (tmp)
	{
		data = tmp->content;
		ret[data->y][data->x] = ft_get_point(data, max);
		tmp = tmp->next;
	}
	return (ret);
}

t_coord	ft_get_max(t_list *map)
{
	t_coord	max;
	t_coord	*val;
	t_list	*tmp;

	tmp = map;
	max.x = 0;
	max.y = 0;
	max.z = 0;
	while (tmp)
	{
		val = tmp->content;
		max.x = (val->x > max.x) ? val->x : max.x;
		max.y = (val->y > max.y) ? val->y : max.y;
		max.z = (val->z > max.z) ? val->z : max.z;
		tmp = tmp->next;
	}
	return (max);
}
