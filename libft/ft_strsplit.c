/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:09:32 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:46:22 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**ft_fail_free(char **main_s, size_t j)
{
	size_t	i;

	i = 0;
	if (!main_s)
		return (NULL);
	while (i < j)
	{
		free(main_s[i]);
		i++;
	}
	return (main_s);
}

static char	**ft_alloc_free(char **main_s, size_t words, char const *s, char c)
{
	size_t			j;
	unsigned int	i;

	j = 0;
	i = 0;
	while (j < words)
	{
		while (s[i] == c)
			i++;
		main_s[j] = ft_strsub(s, i, ft_strlen_tochar(s + i, c));
		if (!main_s[j])
		{
			ft_fail_free(main_s, j);
			free(main_s);
			return (NULL);
		}
		j++;
		i = i + ft_strlen_tochar(s + i, c);
	}
	main_s[j] = NULL;
	return (main_s);
}

char	**ft_strsplit(char const *s, char c)
{
	size_t	words;
	char	**main_s;

	if (!s)
		return (NULL);
	words = ft_word_count(s, c);
	main_s = (char **)malloc(sizeof(char *) * (words + 1));
	if (!main_s)
		return (NULL);
	main_s = ft_alloc_free(main_s, words, s, c);
	return (main_s);
}
