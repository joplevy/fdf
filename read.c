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

int		ft_get_coord(char *line, int y, t_list **map, int x)
{
	t_coord		c;
	char		**tab;

	c.x = -1;
	c.y = y;
	tab = ft_strsplit(line, ' ');
	while (tab[++(c.x)] && (x == 0 || c.x < x))
	{
		c.z = ft_atoi(tab[c.x]);
		ft_lstadd(map, ft_lstnew(&c, sizeof(c)));
	}
	free(tab);
	return (c.x);
}

t_list	*ft_get_map(char *input)
{
	int		fd;
	t_list	*ret;
	char	*line;
	t_coord	c;

	c.y = 0;
	c.x = 0;
	ret = NULL;
	fd = open(input, O_RDONLY);
	get_next_line(fd, &line);
	c.x = ft_get_coord(line, c.y++, &ret, c.x);
	while (get_next_line(fd, &line) > 0)
		if (ft_get_coord(line, c.y++, &ret, c.x) < c.x)
			return (NULL);
	close(fd);
	return (ret);
}

t_point	ft_get_point(t_coord *data, t_coord max, double scale, t_point l)
{
	t_point	ret;

	ret.x = l.x + ((double)data->x + cos(45) * \
		(max.y - (double)data->y)) * scale;
	ret.y = l.y - (((double)data->z + sin(45) *\
		(max.y - (double)data->y)) * scale);
	return (ret);
}

t_point	**ft_tab(t_list *map, t_coord max, double scale, t_point l)
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
		ret[data->y][data->x] = ft_get_point(data, max, scale, l);
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
