/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdelarray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 23:10:28 by acastano          #+#    #+#             */
/*   Updated: 2022/04/15 18:15:15 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_memdelarray(void **array)
{
	void	**temp;

	temp = *array;
	while (*temp)
		ft_memdel(temp++);
	free(*array);
	*array = NULL;
}
