/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 10:59:44 by jplevy            #+#    #+#             */
/*   Updated: 2016/04/30 03:34:04 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>
# include <float.h>
# include <math.h>

typedef struct	s_coord
{
	int			x;
	int			y;
	int			z;
}				t_coord;

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

void			ft_draw_line(void *mlx, void *win, t_point p1, t_point p2);
void			ft_get_coord(char *line, int y, t_list **map);
t_list			*ft_get_map(char *input);
t_point			ft_get_point(t_coord *data, t_coord max);
t_point			**ft_tab(t_list *map, t_coord max);
t_coord			ft_get_max(t_list *map);
void			ft_draw_line(void *mlx, void *win, t_point p1, t_point p2);
void			ft_draw(t_point **tab, t_coord max);
#endif
