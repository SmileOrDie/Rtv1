/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdani <shamdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:50:51 by shamdani          #+#    #+#             */
/*   Updated: 2016/12/15 19:50:54 by shamdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int x;

	x = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	if (!s1[x] || !s2[x])
		return (1);
	return (0);
}
