/* ************************************************************************** */
/*	                                                                   */
/*                                                        :::      ::::::::   */
/*   inter_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:12:51 by shamdani          #+#    #+#             */
/*   Updated: 2016/11/09 13:02:24 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				inter_sphere(void *sphere, t_vector *o, t_vector *dir, double *t)
{
	t_vector	dist_s;
	double		b;
	double		d;
	double		t0;
	double		t1;
	double		a;
	int			result;

	dist_s = vsub2(((t_sphere *)sphere)->pos, o);
	b = vpscal(dir, &dist_s);
	d = b * b - vpscal(&dist_s, &dist_s) + ((t_sphere *)sphere)->radius * (
		(t_sphere *)sphere)->radius;
	if (d < 0.01)
		return (0);
	a = sqrt(d);
	t0 = b - a;
	t1 = b + a;
	result = 1;
	if (t0 > 0.1 && t0 < *t)
		*t = t0;
	else if (t1 > 0.1 && t1 < *t)
		*t = t1;
	else
		result = 0;
	return (result);
}

int				inter_plane(void *plane, t_vector *o, t_vector *dir, double *t)
{
	t_plane		*p;
    double		d;
    double		nd;
    double		te;
    t_vector	qe;

    p = (t_plane *)plane;
    qe = vsub2(p->point, o);
    d = vpscal(p->dir, &qe);
	nd = vpscal(p->dir, dir);
	if(fabs(nd) > *t)
		return (0); 
	te = d / nd;
	if (te > 0.01 && te < *t)
	{
		*t = te;
		return (1); 
    } 
    return (0); 
}

int 			inter_cylinder(void *cylinder, t_vector *o, t_vector *dir, double *t)
{
	t_cyl		*cy;
	double		t0;
	double		t1;
    double		a;
    double		b;
    double		c;
    t_vector	dp;
    t_vector	tmp;
    t_vector	tmp2;

    cy = (t_cyl *)cylinder;
    dp = vsub2(o, cy->pos);
    t0 = vpscal(dir, cy->dir);
    a = dir->x - t0 * cy->dir->x;
    b = dir->y - t0 * cy->dir->y;
    c = dir->z - t0 * cy->dir->z;
    tmp = new_v2(a, b, c);
    t1 = vpscal(&dp, cy->dir);
    a = dp.x - t1 * cy->dir->x;
    b = dp.y - t1 * cy->dir->y;
    c = dp.z - t1 * cy->dir->z;
    tmp2 = new_v2(a, b, c);
	return (solve_quad(vpscal(&tmp, &tmp), vpscal(&tmp, &tmp2) * 2,
		vpscal(&tmp2, &tmp2) - cy->radius * cy->radius, t));
}

int				inter_cone(void *c, t_vector *o, t_vector *dir, double *t)
{
	double			alpha;
	t_vector		origin;	
	t_vector		tmp1;
	t_vector		tmp2;
	t_vector		dir_dir;
	t_vector		o_dir;
	t_cone 			*cone;
	double			arg1;
	double			arg2;
	double			arg3;

	cone = (t_cone *)c;
	alpha = cone->angle / 180 * M_PI;
	origin = vsub2(o, cone->pos);
	dir_dir = vmult_dbl2(cone->dir, vpscal(dir, cone->dir));
	o_dir = vmult_dbl2(cone->dir, vpscal(&origin, cone->dir));
	tmp1 = vsub2(dir, &dir_dir);
	tmp2 = vsub2(&origin, &o_dir);
	arg1 = pow(cos(alpha), 2) * vpscal(&tmp1, &tmp1) -
			pow(sin(alpha), 2) * pow(vpscal(dir, cone->dir), 2);
	arg2 = 2 * (pow(cos(alpha), 2) * vpscal(&tmp1, &tmp2)) -
	2 * (pow(sin(alpha), 2) * vpscal(dir, cone->dir) * vpscal(&origin, cone->dir));
	arg3 = pow(cos(alpha), 2) * vpscal(&tmp2, &tmp2) - 
			pow(sin(alpha), 2) * pow(vpscal(&origin, cone->dir), 2);
	return (solve_quad(arg1, arg2, arg3, t));
}
