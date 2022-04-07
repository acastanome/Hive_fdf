/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_tochar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:30:37 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:44:01 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_tochar(const char *s, char c)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}
