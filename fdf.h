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
	float			x;
	float			y;
	float			z;
}				t_coord;

void	ft_draw_line(void *mlx, void *win, t_coord p1, t_coord p2);
#endif