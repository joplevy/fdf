/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jplevy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:29:19 by jplevy            #+#    #+#             */
/*   Updated: 2016/05/16 18:36:16 by jplevy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord	*ft_max_point(t_coord max)
{
	t_coord	*ret;

	ret = malloc(sizeof(t_coord));
	ret->x = max.x;
	ret->z = max.z;
	ret->y = 0;
	return (ret);
}

t_coord	*ft_min_point(t_coord max, t_list *map)
{
	t_coord	*ret;
	t_coord	*tmp1;
	t_list	*tmp;

	tmp = map;
	ret = malloc(sizeof(t_coord));
	ret->x = max.x;
	ret->z = 0;
	ret->y = max.y;
	while (tmp)
	{
		tmp1 = tmp->content;
		ret->z = (tmp1->z < ret->z) ? tmp1->z : ret->z;
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
