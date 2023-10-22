/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:25:44 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:16:48 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_content(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	display_env(t_env **lst)
{
	t_env	*env;
	int		i;

	i = 0;
	env = *lst;
	if (!*lst)
	{
		ft_putstr_fd("env: No such file or directory\n", 2);
		g_exit_status = 1;
		return ;
	}
	else
	{
		while (env && env->content)
		{
			i = check_content(env->content);
			if (i == 0)
			{
				ft_putstr_fd(env->content, 1);
				ft_putstr_fd("\n", 1);
			}
			env = env->next;
		}
	}
}
