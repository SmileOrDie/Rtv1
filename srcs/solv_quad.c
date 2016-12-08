/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv_quad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:53:30 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/05 17:29:58 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static int	solve_quad_ext(double delta, double b, double *t)
{
	if (delta <= 0)
		return (0);
	else if (*t < b && b > 0.1)
	{
		*t = b;
		return (1);
	}
	return (0);
}

int			solve_quad(double a, double b, double c, double *t)
{
	double delta;
	double x0;
	double x1;
	double q;

	delta = b * b - 4 * a * c;
	if (delta >= 0)
	{
		q = -.5 * (b + sqrt(delta));
		x0 = q / a;
		x1 = c / q;
		if (x0 > x1 && x1 >= 0.1)
			x0 = x1;
		if (*t > x0 && x0 >= 0.1)
		{
			*t = x0;
			return (1);
		}
	}
	else
		return (solve_quad_ext(delta, b, t));
	return (0);
}