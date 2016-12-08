/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:47:49 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/08 19:27:10 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int		inter_obj(t_env *e, t_vector *pos, t_vector *dir, double *t)
{
	t_obj 		*lst;
	double		tr;


	lst = e->l_obj;
	tr = *t;
	while (lst)
	{
		if (lst->inter_func(lst->obj, pos, dir, &tr) && !e->flag)
			e->obj = lst;
		lst = lst->next;
	}
	if (tr < *t)
	{
		*t = tr;
		return (1);
	}
	return (0);
}

static void	l_color(t_env *e, double inte)
{
	int tmp;

	if (e->r > 255)
	{
		tmp = (e->r - 255) * inte;
		e->g += tmp;
		e->b += tmp;
	}
	if (e->g > 255)
	{
		tmp = (e->g - 255) * inte;
		e->r += tmp;
		e->b += tmp;
	}
	if (e->b > 255)
	{
		tmp = (e->b - 255) * inte;
		e->r += tmp;
		e->g += tmp;
	}
	(e->r > 255) ? e->r = 255 : 0;
	(e->g > 255) ? e->g = 255 : 0;
	(e->b > 255) ? e->b = 255 : 0;
}

void		ft_raytracer(int x, int y, t_env *e)
{
	//creer une structure contenant toute les variable
	t_vector	*ray;
	t_vector	*phit;
	t_vector	*dir;
	t_vector	*dir_l;
	double		t;
	double 		a;
	double		b;
	double		c;

	a = e->cam->l->x + e->cam->u->x * x * (e->cam->w / e->mlx->w) + e->cam->up->x * y * (e->cam->h / e->mlx->h);
	b = e->cam->l->y + e->cam->u->y * x * (e->cam->w / e->mlx->w) + e->cam->up->y * y * (e->cam->h / e->mlx->h);
	c = e->cam->l->z + e->cam->u->z * x * (e->cam->w / e->mlx->w) + e->cam->up->z * y * (e->cam->h / e->mlx->h);
	ray = new_v(a, b, c);
	dir = vsub(ray, e->cam->eye);
	vnorm(dir);
	t = T;
	e->d_light = e->light;
	e->flag = 0;
	if (inter_obj(e, e->cam->eye, dir, &t))
	{
		e->c_hit = e->obj->color;
		e->r = e->c_hit->r * e->amb;
		e->g = e->c_hit->g * e->amb;
		e->b = e->c_hit->b * e->amb;
		phit = vhit(e->cam->eye, dir, t);
		e->flag = 1;
		while (e->light)
		{
			dir_l = vsub(e->light->pos, phit);
			t = sqrt(vpscal(dir_l, dir_l));
			vnorm(dir_l);
			if (!(inter_obj(e, phit, dir_l, &t)))
			{
				e->obj->angle_func(e, phit, dir_l);
				e->r += e->c_hit->r * e->light->color->x * e->light->angle;
				e->g += e->c_hit->g * e->light->color->y * e->light->angle;
				e->b += e->c_hit->b * e->light->color->z * e->light->angle;
				l_color(e, 0.5);
			}
			else
				e->light->angle = 0;
			e->light = e->light->next;
			free(dir_l);
		}
		e->light = e->d_light;
		put_pixel(x, y, e);
	}
}

void			start_ray(t_env *e)
{
	int	x;
	int	y;

	x = -1;
	while (++x < e->mlx->w)
	{
		y = -1;
		while (++y < e->mlx->h)
			ft_raytracer(x, y, e);
	}
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img, 0 , 0);
}