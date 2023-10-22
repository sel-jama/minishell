/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 08:28:30 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 07:21:27 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstclear_cmds(t_cmds **lst, void (*del)(void*))
{
	t_cmds	*temp;
	t_cmds	*p;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		p = temp;
		temp = temp->next;
		del(p->cmd_info);
		free(p);
	}
	*lst = NULL;
}

void	ft_lstadd_back_cmds(t_cmds **lst, t_cmds *new)
{
	t_cmds	*last;

	if (*lst)
	{
		last = ft_lstlast_cmds(*lst);
		last -> next = new;
	}
	else
		*lst = new;
}

t_cmds	*ft_lstnew_cmds(void *content)
{
	t_cmds	*new_node;

	new_node = (t_cmds *)malloc(sizeof(t_cmds));
	if (!new_node)
		return (NULL);
	new_node->cmd_info = content;
	new_node->next = NULL;
	return (new_node);
}

t_cmds	*ft_lstlast_cmds(t_cmds *lst)
{
	t_cmds	*last;

	last = lst;
	if (last)
		while (last->next != NULL)
			last = last->next;
	return (last);
}

int	is_redirection(char *token)
{
	if (!ft_strcmp(token, ">") || !ft_strcmp(token, "<")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
		return (1);
	return (0);
}
