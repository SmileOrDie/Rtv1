/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:39:22 by shamdani          #+#    #+#             */
/*   Updated: 2016/11/22 14:42:58 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_color					*get_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color				*color;

	if (!(color = (t_color *)malloc(sizeof(t_color))))
		ft_error (MALLOC , " => (put_pixel.c)");
	color->r = r;
	color->g = g;
	color->b = b;
	return (color);
}

static unsigned char	l_color(unsigned char o, double l, double angle, double amb)
{
	int ret;

	if (angle > 0.1)
		amb = 0;
	else
		angle = 0;
	ret = (o * amb) + (angle * l * o);
	if(ret > 255)
		return (255);
	return ((unsigned char)ret);
}

void					put_pixel(int x, int y, t_env *e)
{
	char 				*pos;

	pos = e->mlx->data + y * e->mlx->sizeline + e->mlx->bpp / 8 * x;
	// if( (float)e->light->angle == 0)
	// 	e->light->angle = 1;
	// *pos = e->obj->color->r * (float)e->light->angle;
	// *(pos + 1) = e->obj->color->g * (float)e->light->angle;
	// *(pos + 2) = e->obj->color->b * (float)e->light->angle;
	if (e->angle > 1)
		e->angle = 1;
	*pos = l_color(e->c_hit->r, e->light->color->x, e->angle, .1);
	*(pos + 1) = l_color(e->c_hit->g, e->light->color->y, e->angle, .1);
	*(pos + 2) = l_color(e->c_hit->b, e->light->color->z, e->angle, .1);
	// printf("%f\n", e->light->angle);
	// *pos = (e->obj->color->r * .1) + e->light->angle * e->light->color->x * e->obj->color->r;
	// *(pos + 1) = (e->obj->color->g * .1) + e->light->angle * e->light->color->y * e->obj->color->g;
	// *(pos + 2) = (e->obj->color->b * .1) + e->light->angle * e->light->color->z * e->obj->color->b;
}