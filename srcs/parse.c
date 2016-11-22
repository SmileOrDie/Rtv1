/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2016/11/22 14:41:03 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void init_cam(t_env *e)
{
	double x;
	double y;
	double z;

	if (!(e->cam = (t_cam *)malloc(sizeof(t_cam))))
		ft_error (MALLOC , "static void init_cam(t_env *e) (=> e->cam)-(parse.c)");
	e->cam->eye = new_v(-400, 100, -50);
	e->cam->l_at = new_v(0, 0, 200);
	e->cam->up = new_v(0, -1, 0);
	vnorm(e->cam->up);
	e->cam->fov = 60;
	e->cam->dist = 150;
	e->cam->n = vsub(e->cam->eye, e->cam->l_at);
	vnorm(e->cam->n);
	x = e->cam->up->y * e->cam->n->z - e->cam->up->z * e->cam->n->y;
	y = e->cam->up->z * e->cam->n->x - e->cam->up->x * e->cam->n->z;
	z = e->cam->up->x * e->cam->n->y - e->cam->up->y * e->cam->n->x;
	e->cam->u = new_v(x, y, z);
	e->cam->h = tan(M_PI * (e->cam->fov / 2) / 180) * 2 * e->cam->dist;
	e->cam->w = e->cam->h * ((float)e->mlx->w / e->mlx->h);
	x = e->cam->eye->x - e->cam->n->x * e->cam->dist;
	y = e->cam->eye->y - e->cam->n->y * e->cam->dist;
	z = e->cam->eye->z - e->cam->n->z * e->cam->dist;
	e->cam->c = new_v(x, y, z);
	x = e->cam->c->x - e->cam->u->x * (e->cam->w / 2) - e->cam->up->x * (e->cam->h / 2);
	y = e->cam->c->y - e->cam->u->y * (e->cam->w / 2) - e->cam->up->y * (e->cam->h / 2);
	z = e->cam->c->z - e->cam->u->z * (e->cam->w / 2) - e->cam->up->z * (e->cam->h / 2);
	e->cam->l = new_v(x, y, z);
}

static t_light *init_light(t_vector *color, t_vector *pos, double i)
{
	t_light *light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		ft_error (MALLOC , "(=> e->light)-(parse.c)");
	light->pos = pos;
	light->color = color;
	light->intensity = i;
	light->angle = 1;
	light->next = NULL;
	return (light);
}

int		ft_parse(char *name, t_env *e)
{
	//gnl name
	(void)name;
	if (!(e->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		ft_error (MALLOC , "int	   ft_parse(char *name, t_env *e) (=> e->mlx)-(parse.c)");
	//gestion de la taille
	e->mlx->w = W;
	e->mlx->h = H;
	//gestion des object en dynamique

	e->l_obj = new_plane(get_color(0xDD, 0, 0), new_v(0, 1, 0), new_v(0, -50, 200));
	e->l_obj->next = new_sphere(get_color(0, 0, 235), new_v(0, 0, 200), 30);
	e->l_obj->next->next = new_sphere(get_color(0, 0, 255), new_v(-100, 100, 200), 20);
	e->l_obj->next->next->next = new_sphere(get_color(255, 255, 0), new_v(50, 0, 200), 20);
	e->l_obj->next->next->next->next = new_sphere(get_color(0, 255, 255), new_v(-150, 0, 200), 20);
	e->l_obj->next->next->next->next->next = new_cylinder(get_color(255, 0, 255), new_v(0, 1, 0), new_v(0, 0, 150), 20);
	e->l_obj->next->next->next->next->next->next = new_cone(get_color(0, 255, 0), new_v(1, 1, 0), new_v(0, 0, 100), 30, 0);
	e->l_obj->next->next->next->next->next->next->next = new_plane(get_color(255, 0, 0), new_v(0, 0, 1), new_v(0, 50, 300));
	e->light = init_light(new_v(1, 1, 1), new_v(150, 200, -250), 1);
	e->light->next = init_light(new_v(1, 1, 1), new_v(-150, 200, -250), 1);
	init_cam(e);
	return (1);
}