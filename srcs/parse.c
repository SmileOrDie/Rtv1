/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 12:35:50 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/06 12:35:14 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void 	creat_lst(char **line, t_env *e)
{
	int len;

	len = ft_tablen(&line, 0);
	if(len == 3 && ft_strcmp(line[0], "img_size") == 0 && e->flag == 0)
	{
		e->flag = 1;
		e->mlx->w = ft_atoi(line[1]);
		e->mlx->h = ft_atoi(line[2]);
	}
	else if (len > 7 && e->obj && ft_strcmp(line[0], "light") != 0 
			&& ft_strcmp(line[0], "cam") != 0)
	{
		e->obj->next = add_obj(line, len);
		e->obj = e->obj->next;
	}
	else if (len > 7 && ft_strcmp(line[0], "light") 
			&& ft_strcmp(line[0], "cam"))
	{
		e->obj = add_obj(line, len);
		e->l_obj = e->obj;
	}
	else if (len > 7 && (ft_strcmp(line[0], "light") == 0
			|| ft_strcmp(line[0], "cam") == 0))
		add_env(line, e);
	ft_tablen(&line, 1);
}

void			ft_parse(char *name, t_env *e)
{
	int fd;
	int r;
	char *line;

	e->flag = 0;
	e->light = NULL;
	e->obj = NULL;
	if (!(e->mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		ft_error (MALLOC , "int	ft_parse(char *name, t_env *e)(e->mlx)");
	fd = open(name, O_RDONLY);
	while ((r = get_next_line(fd, &line)) >= 0)
	{
		if (r == -1)
			ft_error(FILES_E, name);
		if (*line && *line != '#')
			creat_lst(ft_strsplit(line, ' '), e);
		free(line);
		if(r == 0)
			break;
	}
	close(fd);
	e->obj = e->l_obj;
	e->light = e->d_light;
}