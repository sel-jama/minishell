/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:36:39 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/20 13:20:46 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	**load_environement2(char **env)
{
	int		i;
	char	**str;

	i = 0;
	while (env[i])
		i++;
	str = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		str[i] = ft_strdup(env[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}

t_env	*load_environement3(t_env *lst)
{
	char	*ptr;
	char	*tmp;

	lst = NULL;
	ptr = getcwd(NULL, 0);
	tmp = ft_strdup(ptr);
	free(ptr);
	ptr = ft_strjoin("PWD=", tmp);
	ft_lstadd_back_(&lst, new_list(ptr));
	ptr = ft_strdup("OLDPWD=");
	ft_lstadd_back_(&lst, new_list(ptr));
	free(tmp);
	return (lst);
}

void	load_environemen4(t_env *lst2, t_env **lst)
{
	int	i;

	i = 0;
	while (lst2)
	{
		(*lst)->envirenement[i] = lst2->content;
		i++;
		lst2 = lst2->next;
	}
	(*lst)->envirenement[i] = NULL;
}

t_env	*load_environement(char **env, t_env *lst)
{
	int		i;
	t_env	*lst2;

	i = 0;
	if (*env == NULL)
		lst = load_environement3(lst);
	else
	{
		if (env)
		{
			lst = NULL;
			while (env[i])
			{
				ft_lstadd_back_(&lst, new_list(ft_strdup(env[i])));
				i++;
			}
			lst2 = lst;
			lst->envirenement = malloc(sizeof(char *) * (i + 1));
			load_environemen4(lst2, &lst);
		}
	}
	return (lst);
}

t_env	*new_list(char *content)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->envirenement = NULL;
	new->content = content;
	new->next = NULL;
	return (new);
}
