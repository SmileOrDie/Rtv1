/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:47:49 by shamdani          #+#    #+#             */
/*   Updated: 2016/11/22 14:36:59 by shamdani         ###   ########.fr       */
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
		// printf("%ftest\n", e->light->angle);
		*t = tr;
		return (1);
	}
	return (0);
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
	e->angle = 0.0;
	e->d_light = e->light;
	e->flag = 0;
	if (inter_obj(e, e->cam->eye, dir, &t))
	{

		e->c_hit = e->obj->color;
		phit = vhit(e->cam->eye, dir, t);
		e->flag = 1;
		while (e->light)
		{
			dir_l = vsub(e->light->pos, phit);
			t = sqrt(vpscal(dir_l, dir_l));
			vnorm(dir_l);

			if (!(inter_obj(e, phit, dir_l, &t)))
				e->obj->angle_func(e, phit, dir_l);
			else
				e->light->angle = 0;

			e->angle += e->light->angle;
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
