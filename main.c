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

int		main(int ac, char **av)
{
	t_list	*map;
	t_point	**tab;
	t_coord	max;

	map = NULL;
	if (ac != 2)
		ft_putstr("usage : ./fdf input_file\n");
	else
	{
		map = ft_get_map(av[1]);
		if (map)
		{
			max = ft_get_max(map);
			tab = ft_tab(map, max);
			ft_draw(tab, max);
		}
	}
	return (0);
}
