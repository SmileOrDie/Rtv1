/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 09:28:02 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/08 18:54:57 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


void			ft_angle_sphere(void *env, t_vector *hit, t_vector *dir_l)
{
	t_vector	*pho;
	double		tmp;
	t_env		*e;
	t_sphere	*s;

	e = (t_env *)env;
	s = (t_sphere *)e->obj->obj;
	pho = vsub(hit, s->pos);
	vnorm(pho);
	tmp = vpscal(pho, dir_l);
	e->light->angle = (tmp < .0) ? 0 : tmp;
	free(pho);
}

void			ft_angle_plane(void *env, t_vector *hit, t_vector *dir_l)
{
	t_env		*e;
	t_plane		*p;
	// t_vector	*n;
	double		tmp;

	(void)hit;
	e = (t_env *)env;
	p = (t_plane *)e->obj->obj;
	tmp = vpscal(p->dir, dir_l);
	// if ( tmp < 0)
	// {
	// 	n = vmult_dbl(p->dir, -1);
	// 	tmp = vpscal(n, dir_l);
	// }
	if (tmp < 0)
		tmp *=-1;
	e->light->angle = tmp;
}

void			ft_angle_cylinder(void *env, t_vector *p_hit, t_vector *l_vector)
{
	double tmp;
	t_env *e;
	t_cyl *obj;
	t_vector *b;
	t_vector *c;
	t_vector *r;
	double n;
	double n2;
	float dist;

	e = (t_env *)env;
	obj = (t_cyl *)e->obj->obj;
	b = vsub(p_hit, obj->pos);
	n = vpscal(b, b);
	if ((float)n == obj->radius * obj->radius)
		dist = 0;
	else
		dist = sqrt(n - obj->radius * obj->radius);
	b->x = obj->dir->x * dist + obj->pos->x;
	b->y = obj->dir->y * dist + obj->pos->y;
	b->z = obj->dir->z * dist + obj->pos->z;
	c = vsub(p_hit, b);
	n2 = vpscal(c, c);
	if (n2 > n)
	{
		b->x = -(obj->dir->x * dist) + obj->pos->x;
		b->y = -(obj->dir->y * dist) + obj->pos->y;
		b->z = -(obj->dir->z * dist) + obj->pos->z;
	}
	r = vsub(p_hit, b);
	vnorm(r);
	vnorm(l_vector);
	tmp = vpscal(r, l_vector);
	e->light->angle = (tmp < .0) ? tmp * -1 : tmp;
}

void			ft_angle_cone(void *env, t_vector *p_hit, t_vector *l_vector)
{
	t_env 		*e;
	t_cone *obj;
	double hypo;
	double opp;
	double adj;
	t_vector *b;
	t_vector *c;
	double alpha;
	double dist;
	double tmp;

	e = (t_env *)env;
	obj = (t_cone *)e->obj->obj;
	alpha = M_PI * obj->angle / 180;
	c = vsub(p_hit, obj->pos);
	hypo = sqrt(vpscal(c, c));
	adj = hypo * cos(alpha);
	opp = adj * tan(alpha);
	c->x = obj->dir->x * adj + obj->pos->x;
	c->y = obj->dir->y * adj + obj->pos->y;
	c->z = obj->dir->z * adj + obj->pos->z;
	b = vsub(p_hit, c);
	dist = sqrt(vpscal(b, b));
	if ((float)dist > (float)opp)
	{
		c->x = obj->dir->x * -adj + obj->pos->x;
		c->y = obj->dir->y * -adj + obj->pos->y;
		c->z = obj->dir->z * -adj + obj->pos->z;
	}
	b = vsub(p_hit, c);
	vnorm(b);
	vnorm(l_vector);
	tmp = vpscal(b, l_vector);
	e->light->angle = (tmp < .0) ? 0 : tmp;
}