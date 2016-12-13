/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv_quad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:53:30 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/12 16:30:56 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			solve_quad(double a, double b, double c, double *t)
{
	// (void)a; (void)b; (void)c; (void)t;
	double delta;
	double sqrt_delta;
	double x0;
	double x1;
	double q;

	delta = b * b - 4 * a * c;
	if (delta > 0)
	{
		sqrt_delta = sqrt(delta);
		q = -.5 * (b + sqrt_delta);
		x0 = q / a;
		x1 = (q + sqrt_delta) / a;
		if (*t > x0 && x0 >= 0.1 && (x1 <= 0.1 || x1 >= x0))
		{
			*t = x0;
			return (1);
		}
		if (*t > x1 && x1 >= 0.1)
		{
			*t = x1;
			return (1);
		}
	}
	else if (delta == 0)
	{
		*t = 0;
		return (1);
	}
	return (0);
}
