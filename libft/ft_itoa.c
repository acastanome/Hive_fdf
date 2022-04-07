/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:44:00 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:23:43 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_elements(long int n)
{
	int	el;

	el = 0;
	if (n < 0)
	{
		n = -n;
		el++;
	}
	while (n > 9)
	{
		n = n / 10;
		el++;
	}
	el++;
	return (el);
}

char	*ft_itoa(int n)
{
	char		*s;
	int			el;
	int			i;
	long int	nl;

	nl = n;
	el = ft_elements(nl);
	s = ft_strnew(el);
	i = 0;
	if (!s)
		return (NULL);
	if (nl < 0)
	{
		s[0] = '-';
		nl = -nl;
	}
	while (1 < el)
	{
		s[el - 1] = '0' + (nl % 10);
		nl = nl / 10;
		el--;
	}
	if (s[0] != '-')
		s[0] = '0' + nl;
	return (s);
}
