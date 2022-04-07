/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:15:17 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:46:33 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(needle);
	if (!needle || (*needle == '\0'))
		return ((char *)haystack);
	while (haystack[i])
	{
		if (ft_strncmp(haystack + i, needle, len) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
