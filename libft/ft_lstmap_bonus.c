/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:36:10 by sel-jama          #+#    #+#             */
/*   Updated: 2022/11/01 04:24:05 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;
	t_list	*new;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (new)
	{
		elem = NULL;
		lst = lst->next;
		while (lst)
		{
			elem = ft_lstnew(f(lst->content));
			if (!elem)
			{
				ft_lstclear(&new, del);
				return (NULL);
			}
			ft_lstadd_back(&new, elem);
			lst = lst->next;
		}
	}
	return (new);
}
