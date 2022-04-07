/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_3whitespace_e.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 18:09:53 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:20:45 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_3whitespace_e(const char *s)
{
	size_t	count;
	int		i;

	count = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	i--;
	while (ft_is_3whitespace(s[i]) == 1 && i >= 0)
	{
		count++;
		i--;
	}
	return (count);
}
