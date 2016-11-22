/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 14:02:07 by shamdani          #+#    #+#             */
/*   Updated: 2016/11/14 16:26:46 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_obj	*new_sphere(t_color *color, t_vector *pos, double r)
{
	t_obj		*obj;
	t_sphere	*s;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		ft_error (MALLOC , "(sphere=>obj)-(add_obj.c)");
	if (!(s = (t_sphere*)malloc(sizeof(t_sphere))))
		ft_error (MALLOC , "(sphere=>sphere)-(add_obj.c)");
	s->pos = pos;
	s->radius = r;
	obj->inter_func = inter_sphere;
	obj->angle_func = ft_angle_around;	
	obj->obj = s;
	obj->color = color;
	obj->next = NULL;
	return (obj);
}

t_obj	*new_plane(t_color *color, t_vector *dir, t_vector *point)
{
	t_obj		*obj;
	t_plane		*p;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		ft_error (MALLOC , "(plane=>obj)-(add_obj.c)");
	if (!(p = (t_plane *)malloc(sizeof(t_plane))))
		ft_error (MALLOC , "(plane=>plane)-(add_obj.c)");
	p->dir = dir;
	vnorm(p->dir);
	p->point = point;
	obj->inter_func = inter_plane;
	obj->angle_func = ft_angle_plane;
	obj->obj = p;
	obj->color = color;
	obj->next = NULL;
	return (obj);
}


t_obj	*new_cylinder(t_color *color, t_vector *dir, t_vector *point, double r)
{
	t_obj		*obj;
	t_cyl		*c;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		ft_error (MALLOC , "(plane=>obj)-(add_obj.c)");
	if (!(c = (t_cyl *)malloc(sizeof(t_cyl))))
		ft_error (MALLOC , "(cylindre=>cylindre)-(add_obj.c)");
	c->dir = dir;
	vnorm(c->dir);
	c->pos = point;
	c->radius = r;
	obj->inter_func = inter_cylinder;
	obj->angle_func = ft_angle_cylinder;
	obj->obj = c;
	obj->color = color;
	obj->next = NULL;
	return (obj);
}

t_obj	*new_cone(t_color *color, t_vector *dir, t_vector *pos, double angle, int m)
{
	t_obj		*obj;
	t_cone		*c;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		ft_error (MALLOC , "(plane=>obj)-(add_obj.c)");
	if (!(c = (t_cone *)malloc(sizeof(t_cone))))
		ft_error (MALLOC , "(cylinder=>cyl)-(add_obj.c)");
	c->dir = dir;
	vnorm(c->dir);
	c->pos = pos;
	c->angle = angle;
	c->m = m;
	obj->inter_func = inter_cone;
	obj->angle_func = ft_angle_cone;
	obj->obj = c;
	obj->color = color;
	obj->next = NULL;
	return (obj);
}