/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:38:08 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/13 18:56:44 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void ft_test(t_env *e)
{
	e->cam->n = vsub(e->cam->eye, e->cam->l_at);
	vnorm(e->cam->n);
	e->cam->u = new_v(e->cam->up->y * e->cam->n->z - e->cam->up->z *
		e->cam->n->y, e->cam->up->z * e->cam->n->x - e->cam->up->x *
		e->cam->n->z, e->cam->up->x * e->cam->n->y - e->cam->up->y *
		e->cam->n->x);
	e->cam->h = tan(M_PI * (e->cam->fov / 2) / 180) * 2 * e->cam->dist;
	e->cam->w = e->cam->h * ((float)e->mlx->w / e->mlx->h);
	e->cam->c = new_v(e->cam->eye->x - e->cam->n->x * e->cam->dist,
		e->cam->eye->y - e->cam->n->y * e->cam->dist,
		e->cam->eye->z - e->cam->n->z * e->cam->dist);
	e->cam->l = new_v(e->cam->c->x - e->cam->u->x * (e->cam->w / 2) -
		e->cam->up->x * (e->cam->h / 2), e->cam->c->y - e->cam->u->y *
		(e->cam->w / 2) - e->cam->up->y * (e->cam->h / 2),
		e->cam->c->z - e->cam->u->z * (e->cam->w / 2) - e->cam->up->z *
		(e->cam->h / 2));
}

int		keypress(int key, t_env *e)
{
	(void) e;
	if (key == ESC)
		exit(1);
	else if (key == 37)
		e->cam->eye->y += 10;
	else if (key == 38)
		e->cam->eye->x += 10;
	else if (key == 40)
	{
		e->cam->eye->z += 10;
		printf("%f\n", e->cam->eye->z);
	}
	else
		return (1);
	ft_test(e);
	start_ray(e);
	return (1);
}

int		redcross(t_env *e)
{
	(void) e;
	exit(1);
	return (1);
}