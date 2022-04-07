/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:50:54 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:45:49 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	nlen;

	i = 0;
	nlen = ft_strlen(needle);
	if (!needle || (*needle == '\0'))
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if ((ft_strncmp(haystack + i, needle, nlen) == 0) && (nlen <= len - i))
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
