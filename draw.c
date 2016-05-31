/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:29:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/05/16 18:36:16 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_draw_line(void *mlx, void *win, t_point p1, t_point p2)
{
	float	e;
	float	f;
	int		pm;

	e = 0;
	pm = (p2.y > p1.y) ? 1 : 0;
	f = (p2.y - p1.y) / (p2.x - p1.x);
	while (p1.x < p2.x)
	{
		mlx_pixel_put(mlx, win, p1.x, p1.y, 0xFFFFFF);
		e = e + f;
		while ((pm == 1 && e >= 0.5) || (pm == 0 && e <= -0.5))
		{
			p1.y = (pm == 1) ? p1.y + 1 : p1.y - 1;
			e = (pm == 1) ? e - 1 : e + 1;
			mlx_pixel_put(mlx, win, p1.x, p1.y, 0xFFFFFF);
		}
		p1.x = p1.x + 1;
	}
}

void	ft_draw(t_point **tab, t_coord max)
{
	void	*mlx;
	void	*win;
	int		y;
	int		x;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 600, 600, "fdf");
	y = -1;
	while (++y <= max.y)
	{
		x = -1;
		while (++x <= max.x)
		{
			if (x < max.x)
				ft_draw_line(mlx, win, tab[y][x], tab[y][x + 1]);
			if (y > 0)
				ft_draw_line(mlx, win, tab[y][x], tab[y - 1][x]);
		}
	}
	mlx_loop(mlx);
}
