/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:45:45 by shamdani          #+#    #+#             */
/*   Updated: 2016/11/22 14:35:37 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "error.h"
# include "../vector/include/vector.h"
# include "../matrix/include/matrix.h"
# include <mlx.h>


#include <stdio.h>


# define ESC 53

# define W 640
# define H 480

# define T 20000


typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
	int				w;
	int				h;
}					t_mlx;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct		s_sphere
{
	t_vector		*pos;
	double			radius;
}					t_sphere;

typedef struct		s_cyl
{
	t_vector		*pos;
	t_vector		*dir;
	double			radius;
}					t_cyl;

typedef struct		s_cone
{
	t_vector		*pos;
	t_vector		*dir;
	double			angle;
	int				m;
}					t_cone;

typedef struct		s_plane
{
	t_vector		*dir;
	t_vector		*point;
}					t_plane;

typedef	struct		s_obj
{
	void			*obj;
	t_color			*color;
	int				(*inter_func)(void *s, t_vector *o, t_vector *dir, double *t);
	void			(*angle_func)(void *e, t_vector *o, t_vector *dir);	
	struct s_obj	*next;
}					t_obj;

// typedef struct		s_cam
// {
// 	t_vector		*pos;

// 	t_vector		*rot;
// 	unsigned int	f;
// }					t_cam;

typedef struct	s_cam
{
	t_vector	*eye;
	t_vector	*l_at;
	t_vector	*up;
	double		dist;
	double		fov;
	double		h;
	double		w;
	t_vector	*c;
	t_vector	*l;
	t_vector	*n;
	t_vector	*u;
}				t_cam;


typedef struct		s_light
{
	t_vector		*pos;
	t_vector		*color;
	double			intensity;
	double 			angle;
	t_vector		*norm;
	struct s_light	*next;
}					t_light;

typedef struct		s_env
{
	t_mlx			*mlx;
	t_cam			*cam;
	t_light			*light;
	t_light			*d_light;
	t_obj			*l_obj;
	t_obj			*obj;
	t_color			*c_hit;
	double			angle;
	int				flag;

}					t_env;

int		ft_parse(char *name_file, t_env *e);

int		solve_quad(double a, double b, double c, double *t);

int		keypress(int key, t_env *e);
int		redcross(t_env *e);

void	start_ray(t_env *e);

t_obj	*new_sphere(t_color *color, t_vector *pos, double r);
t_obj	*new_plane(t_color *color, t_vector *dir, t_vector *point);
t_obj	*new_cylinder(t_color *color, t_vector *dir, t_vector *pos, double r);
t_obj	*new_cone(t_color *color, t_vector *dir, t_vector *origine, double angle, int m);

int 	inter_sphere(void *s, t_vector *o, t_vector *dir, double *t);
int		inter_plane(void *s, t_vector *o, t_vector *dir, double *t);
int 	inter_cylinder(void *cylinder, t_vector *o, t_vector *dir, double *t);
int 	inter_cone(void *cone, t_vector *o, t_vector *dir, double *t);

void	ft_angle_around(void *e, t_vector *hit, t_vector *dir_l);
void	ft_angle_plane(void *e, t_vector *np, t_vector *dir_l);
void	ft_angle_cylinder(void *env, t_vector *hit, t_vector *dir_l);
void	ft_angle_cone(void *env, t_vector *hit, t_vector *dir_l);

t_color	*get_color(unsigned char r, unsigned char g, unsigned char b);
void	put_pixel(int x, int y, t_env *e);

#endif