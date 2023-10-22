/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_b_v2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:35:40 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/20 18:02:00 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	handling_cd(t_env **env, char **interput, int d)
{
	char	*ptr;

	ptr = NULL;
	if (d == 0)
	{
		ft_cd(interput, env, 0, ptr);
		return (0);
	}
	else
	{
		ft_cd(interput, env, 1, ptr);
		exit(g_exit_status);
	}
	return (1);
}

int	handling_env(t_env **env, int d)
{
	if (d == 0)
	{
		display_env(env);
		return (0);
	}
	else
	{
		display_env(env);
		exit(0);
	}
	return (1);
}

int	handling_pwd(t_env **env, int d)
{
	if (d == 0)
	{
		ft_pwd(env);
		return (0);
	}
	else
	{
		ft_pwd(env);
		g_exit_status = 0;
		exit(0);
	}
	return (1);
}

int	handling_echo(char **interput, int d)
{
	if (d == 0)
	{
		ft_echo(interput);
		return (0);
	}
	else
	{
		ft_echo(interput);
		exit(g_exit_status);
	}
	return (1);
}

int	handling_export(char **interput, t_env **env, int d)
{
	int	j;

	j = 1;
	if (interput[0] && !interput[1])
	{
		ft_export_2(interput, env);
		return (0);
	}
	if (d == 0 && interput[1])
	{
		ft_export_h(env, interput);
		return (0);
	}
	if (d == 1 && interput[1])
	{
		while (interput[j])
		{
			ft_export(interput, env, j);
			j++;
		}
		load_env_2(env);
		exit(g_exit_status);
	}
	return (1);
}
