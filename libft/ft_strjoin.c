/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 20:14:53 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:43:21 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*joined;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (size + 1));
	if (!joined)
		return (NULL);
	ft_bzero(joined, size + 1);
	joined = ft_strcat(joined, s1);
	joined = ft_strcat(joined, s2);
	return (joined);
}
