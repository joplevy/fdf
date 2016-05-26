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

void	ft_draw_line(void *mlx, void *win, t_point p1, t_point p2)
{
	float	e;
	float	f;
	int		pm;

	e = 0;
	pm = (p2.y > p1.y)? 1 : 0;
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
	close (fd);
	return (ret);

}

t_point	ft_get_point(t_coord *data, t_coord max)
{
	t_point	ret;

	ret.x = ((double)data->x + cos(45) * (max.y - (double)data->y)) * 20;
	ret.y = 500 - (((double)data->z + sin(45) * (max.y - (double)data->y)) * 20);
	if (data->z > 0)
		printf("> 0");
	printf("x = %.1f, y = %.1f\n", ret.x, ret.y);
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
		printf("maxy = %d maxx = %d\nitery = %d iterx = %d\n", max.y, max.x, data->y, data->x);
		ret[data->y][data->x] = ft_get_point(data, max);
		tmp = tmp->next;
	}
	return(ret);
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
	return(max);
}

int		main(int ac, char **av)
{
	t_list	*map;
	t_point	**tab;
	t_coord	max;
	/*void	*mlx;
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
	mlx_loop(mlx);*/
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
			/*while (map)
			{
				data = map->content;
				printf("x = %d y = %d z = %d\n", data->x, data->y, data->z);
				map = map->next;
			}*/
		}
		else
			printf("pipi\n");
	}
	return (0);
}
