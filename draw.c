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

int		my_key_func(int keycode, void *param)
{
	if (keycode == 53 && param == 0)
		exit(0);
	return (0);
}

void	ft_swap_point(t_point *a, t_point *b)
{
	t_point	*tmp;

	tmp = malloc(sizeof(t_point));
	tmp->x = a->x;
	tmp->y = a->y;
	a->x = b->x;
	a->y = b->y;
	b->x = tmp->x;
	b->y = tmp->y;
	free(tmp);
}

void	ft_draw_high_line(void *mlx, void *win, t_point p1, t_point p2)
{
	float	e;
	float	f;
	int		pm;

	if (p1.y > p2.y)
		ft_swap_point(&p1, &p2);
	pm = (p2.x > p1.x) ? 1 : 0;
	f = (p2.x - p1.x) / (p2.y - p1.y);
	while (p1.y < p2.y)
	{
		mlx_pixel_put(mlx, win, p1.x, p1.y, 0xFFFFFF);
		e = e + f;
		if ((pm == 1 && e >= 0.5) || (pm == 0 && e <= -0.5))
		{
			p1.x = (pm == 1) ? p1.x + 1 : p1.x - 1;
			e = (pm == 1) ? e - 1 : e + 1;
		}
		p1.y = p1.y + 1;
	}
}

void	ft_draw_line(void *mlx, void *win, t_point p1, t_point p2)
{
	float	e;
	float	f;
	int		pm;

	e = 0;
	f = (p2.y - p1.y) / (p2.x - p1.x);
	if (f <= 0.5 && f >= -0.5)
	{
		pm = (p2.y > p1.y) ? 1 : 0;
		while (p1.x < p2.x)
		{
			mlx_pixel_put(mlx, win, p1.x, p1.y, 0xFFFFFF);
			e = e + f;
			if ((pm == 1 && e >= 0.5) || (pm == 0 && e <= -0.5))
			{
				p1.y = (pm == 1) ? p1.y + 1 : p1.y - 1;
				e = (pm == 1) ? e - 1 : e + 1;
			}
			p1.x = p1.x + 1;
		}
	}
	else
		ft_draw_high_line(mlx, win, p1, p2);
}

void	ft_draw(t_point **tab, t_coord max)
{
	void	*mlx;
	void	*win;
	int		y;
	int		x;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1600, 800, "fdf");
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
	mlx_key_hook(win, my_key_func, 0);
	mlx_loop(mlx);
}
