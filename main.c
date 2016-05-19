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

void	ft_draw_line(void *mlx, void *win, t_coord p1, t_coord p2)
{
	float	e;
	float	f;

	e = 0;
	f = (p2.y - p1.y) / (p2.x - p1.x);
	while (p1.x < p2.x)
	{
		mlx_pixel_put(mlx, win, p1.x, p1.y, 0xFFFFFF);
		e = e + f;
		if (e >= 0.5)
		{
			p1.y = p1.y + 1;
			e = e - 1;
		}
		p1.x = p1.x + 1;
	}
}

int		main(void)
{
	void	*mlx;
	void	*win;
	t_coord	p1;
	t_coord	p2;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 400, "fdf");
	p1.y = 50;
	p1.x = 50;
	p2.y = 100;
	p2.x = 150;
	ft_draw_line(mlx, win, p1, p2);
	mlx_loop(mlx);
	return (0);
}
