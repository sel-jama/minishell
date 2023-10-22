/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:27:17 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/20 18:00:43 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_unset_2(t_env *list, t_env *lst, t_env *str)
{
	if (list && str)
		list->next = str;
	else
		list->next = NULL;
	if (lst && lst->content)
	{
		free(lst->content);
		free(lst);
	}
	g_exit_status = 0;
	return (1);
}

void	ft_helper(int *t, char *interput)
{
	int	j;

	j = *t;
	j = 0;
	while (interput && interput[j] && interput[j] != '=')
		j++;
	*t = j;
	g_exit_status = 0;
}

int	ft_unset_3(t_env **env, t_env *lst, int j, t_env *str)
{
	if (j == 0 && lst->next == NULL)
	{
		if (lst && lst->content)
		{
			free(lst->envirenement);
			free(lst->content);
			free(lst);
		}
		*env = NULL;
		return (1);
	}
	else if (j == 0)
	{
		if (lst && lst->content)
		{
			free(lst->envirenement);
			free(lst->content);
			free(lst);
		}
		lst = str;
		*env = lst;
		g_exit_status = 0;
		return (1);
	}
	return (0);
}

void	ft_unset_helper(t_env **list, t_env **lst)
{
	*list = *lst;
	*lst = (*lst)->next;
}

void	ft_unset(char *interput, t_env **env)
{
	t_env	*lst;
	t_env	*str;
	t_env	*list;
	int		j;
	int		t;

	str = NULL;
	lst = *env;
	j = 0;
	while (lst)
	{
		ft_helper(&t, lst->content);
		if (interput && ft_strncmp(lst->content, interput, t) == 0
			&& (ft_strlen(interput) == (size_t)t))
		{
			if (lst && lst->next)
				str = lst->next;
			if (ft_unset_3(env, lst, j, str) == 1)
				break ;
			else if (ft_unset_2(list, lst, str) == 1)
				break ;
		}
		ft_unset_helper(&list, &lst);
		j++;
	}
}
