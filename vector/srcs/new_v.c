/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_v.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:05:18 by shamdani          #+#    #+#             */
/*   Updated: 2016/11/08 10:19:13 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/vector.h"

t_vector *new_v(double x, double y, double z)
{
	t_vector *new;

	new = NULL;
	if (!(new = (t_vector *)malloc(sizeof(t_vector))))
		ft_error (MALLOC , "t_vector *new_v(double a, double b, double c);");
	else
	{
		new->x = x;
		new->y = y;
		new->z = z;
		new->p = 1;
	}
	return (new);
}