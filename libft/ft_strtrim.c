/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:07:06 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:49:08 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	size_t	count_beginning;
	size_t	count_from_end;
	size_t	trimlen;

	if (!s)
		return (NULL);
	count_beginning = ft_count_3whitespace_b(s);
	count_from_end = ft_count_3whitespace_e(s);
	trimlen = ft_strlen(s) - count_beginning - count_from_end;
	if (count_beginning == ft_strlen(s))
		trimlen = ft_strlen(s) - count_beginning;
	return (ft_strsub(s, count_beginning, trimlen));
}
