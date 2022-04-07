/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:32:04 by acastano          #+#    #+#             */
/*   Updated: 2022/01/27 17:31:19 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_lstfree(t_list **lst)
{
	free((*lst)->content);
	free(*lst);
	*lst = NULL;
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlst;

	newlst = f(lst);
	if (!lst || !newlst)
		return (NULL);
	if (lst->next != NULL)
	{
		newlst->next = ft_lstmap(lst->next, f);
		if (newlst->next == NULL)
			ft_lstfree(&newlst);
	}
	return (newlst);
}
