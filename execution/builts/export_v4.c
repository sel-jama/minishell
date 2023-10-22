/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_v4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:33:47 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/21 01:25:57 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	condition_fun(char *content, char *in, int j)
{
	if (ft_strncmp(in, content, j) == 0
		|| (ft_strncmp(in, content, j - 1) == 0
			&& in[j - 1] == '=' && !content[j - 1]))
		return (1);
	return (0);
}

int	condition_fun2(t_env **env, char *in, int j, char *ptr)
{
	if (j && (((*env)->content[j - 1] == '=' && (*env)->content)
			|| (!((*env)->content[j - 1] == '=') && in[j - 1] == '=')))
	{
		(*env)->content = check_env3((*env)->content, ptr, j, in);
		return (1);
	}
	return (0);
}

int	check_env2(t_env **envi, char *in, char *ptr, int j)
{
	t_env	*env;
	char	*tmp;

	env = *envi;
	tmp = NULL;
	while (env)
	{
		if (check_env2_2(in, env->content, ft_strlen(ptr), ptr) == 1)
			return (1);
		else if (condition_fun(env->content, in, j) == 1)
		{
			if (env->content && env->content[j - 1] == '=' && !env->content[j])
				tmp = check_env2_h(env->content, ptr, j);
			if (tmp != NULL)
			{
				env->content = tmp;
				return (1);
			}
			else if (condition_fun2(&env, in, j, ptr) == 1)
				return (1);
		}
		env = env->next;
	}
	return (0);
}

int	check_env(t_env **lst, char *interput)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (interput[i] && interput[i] != '=')
		i++;
	if (interput[i] == '=')
	{
		j = i;
		i = ft_strlen(interput + j);
	}
	j += 1;
	ptr = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(ptr, interput + j, i);
	i = check_env2(lst, interput, ptr, j);
	if (ptr)
		free(ptr);
	if (i == 1)
		return (1);
	return (0);
}

void	ft_export_h(t_env	**env, char **interput)
{
	int	j;

	j = 1;
	while (interput[j])
	{
		ft_export(interput, env, j);
		j++;
	}
	load_env_2(env);
}
