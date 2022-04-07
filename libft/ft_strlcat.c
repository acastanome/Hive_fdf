/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:14:32 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:43:36 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	max;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	max = dstsize - dstlen - 1;
	if (srclen < max)
		max = srclen;
	if (dstsize != 0 && (dstsize > dstlen))
	{
		ft_memcpy(dst + dstlen, src, max);
		dst[dstlen + max] = '\0';
	}
	else
		return (dstsize + srclen);
	return (dstlen + srclen);
}
