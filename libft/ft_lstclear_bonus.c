/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:31:50 by sel-jama          #+#    #+#             */
/*   Updated: 2022/11/01 04:34:18 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*p;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		p = temp;
		temp = temp->next;
		del(p->content);
		free(p);
	}
	*lst = NULL;
}
