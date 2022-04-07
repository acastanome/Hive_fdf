/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_3whitespace_b.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:31:11 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:20:36 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_3whitespace_b(const char *s)
{
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	while (ft_is_3whitespace(*s) == 1)
	{
		count++;
		s++;
	}
	return (count);
}
