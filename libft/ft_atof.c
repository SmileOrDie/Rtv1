/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 16:55:20 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/12 12:21:03 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

static double		ft_atof_end(char **tab, double tmp, int neg)
{
	double tmp2;

	if (ft_tablen(&tab, 0) == 1)
	{
		while (tmp >= 1)
			tmp /= 10;
		ft_tablen(&tab, 1);
		return (tmp);
	}
	tmp2 = (double)ft_atoi(tab[1]);
	while (tmp2 >= 1)
		tmp2 /= 10;
	return ((tmp2 + tmp) * neg);
}

static int			state_str(char **str)
{
	int		neg;

	neg = 1;
	if (**str == '-' || **str == '+')
	{
		neg = (**str == '-') ? -1 : 1;
		(*str)++;
	}
	return (neg);
}

double				ft_atof(char *str)
{
	char	**tab;
	int		dbl;
	double	tmp;
	int 	neg;

	dbl = 0;
	tmp = 0;
	while (str[(int)tmp])
	{
		if (str[(int)tmp] == '.')
			++dbl;
		++tmp;
	}
	if (dbl == 0)
		return ((double)ft_atoi(str));
	else if (dbl > 1)
		return ((double)0);
	neg = state_str(&str);
	tab = ft_strsplit(str, '.');
	tmp = (double)ft_atoi(tab[0]);
	return (ft_atof_end(tab, tmp, neg));
}