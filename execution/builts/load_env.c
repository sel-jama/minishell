/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:26:48 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/20 18:02:25 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*before_the_last_list_(t_env *node)
{
	t_env	*last;
	t_env	*new;

	last = node;
	while (last->next != NULL)
	{
		new = last;
		last = last->next;
	}
	return (new->content);
}

void	ft_lstadd_back_(t_env **lst, t_env *new)
{
	t_env	*last;

	if (*lst != NULL)
	{
		last = ft_lstlast_(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_env	*ft_lstlast_(t_env *lst)
{
	t_env	*last;

	last = lst;
	if (last)
	{
		while (last->next)
		{
			last = last->next;
			if (last->next == NULL)
				break ;
		}
		return (last);
	}
	return (last);
}

void	load_env_3(t_env **lst, char **ptr)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = *lst;
	while (tmp)
	{
		ptr[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	if (ptr)
	{
		ptr[i] = NULL;
		if ((*lst)->envirenement)
			free((*lst)->envirenement);
		(*lst)->envirenement = ptr;
	}
}

void	load_env_2(t_env **lst)
{
	int		i;
	t_env	*envi;
	char	**ptr;

	envi = *lst;
	i = 0;
	while (envi && envi->content)
	{
		i++;
		envi = envi->next;
	}
	envi = *lst;
	if (*lst)
	{
		ptr = malloc(sizeof (char *) * (i + 1));
		load_env_3(lst, ptr);
	}
}
