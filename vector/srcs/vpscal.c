/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vpscal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:25:55 by shamdani          #+#    #+#             */
/*   Updated: 2016/11/15 10:48:35 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/vector.h"

double	vpscal(t_vector *a, t_vector *b)
{

	if (!a || !b)
		ft_error (ARG_N , "double	vpscal(t_vector *a, t_vector *b)");
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}