/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:29:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/05/16 18:36:16 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	ft_get_scale(float *scale, t_coord max, t_list *map)
{
	t_point	l;
	t_coord	*maxp;
	t_coord	*minp;

	*scale = 0;
	l.x = 0;
	l.y = 0;
	maxp = ft_max_point(max);
	minp = ft_min_point(max, map);
	while (ft_get_point(maxp, max, *scale + 1, l).x < 1500 && \
		ft_get_point(minp, max, *scale + 1, l).y - \
		ft_get_point(maxp, max, *scale + 1, l).y < 700)
		*scale = *scale + 1;
	l.x = (1600 - ft_get_point(maxp, max, *scale, l).x) / 2;
	l.y = 800 - (800 + ft_get_point(maxp, max, *scale, l).y) / 2\
	- (ft_get_point(minp, max, *scale, l).y) / 2;
	return (l);
}

int		main(int ac, char **av)
{
	t_list	*map;
	t_point	**tab;
	t_coord	max;
	t_point	l;
	float	scale;

	map = NULL;
	if (ac != 2)
		ft_putstr("usage : ./fdf input_file\n");
	else
	{
		map = ft_get_map(av[1]);
		if (map)
		{
			max = ft_get_max(map);
			l = ft_get_scale(&scale, max, map);
			tab = ft_tab(map, max, scale, l);
			ft_draw(tab, max);
		}
		else
			ft_putstr("error\n");
	}
	return (0);
}
