/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:26:36 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/19 10:49:24 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	handling_unset2(t_env **env, char **interput)
{
	int	j;

	j = 1;
	while (interput[j])
	{
		ft_unset(interput[j], env);
		j++;
	}
	load_env_2(env);
}

int	handling_unset(t_env **env, char **interput, int d)
{
	int	j;

	j = 1;
	if (d == 0)
	{
		handling_unset2(env, interput);
		if (j == 1)
			g_exit_status = 0;
		return (0);
	}
	else
	{
		while (interput[j])
		{
			ft_unset(interput[j], env);
			j++;
		}
		load_env_2(env);
		exit(g_exit_status);
	}
	return (1);
}

int	handling_exit(char **interput, t_env **env, int d)
{
	int	j;

	j = 1;
	if (interput[0] && !interput[1])
		exit(g_exit_status);
	if (interput[j])
	{
		if (d == 1)
			ft_exit_(interput, 1, env);
		else
			ft_exit_(interput, 0, env);
	}
	if ((interput[j][0] == '>' || interput[j][0] == '<'))
	{
		g_exit_status = 0;
		exit(0);
	}
	return (0);
}

void	handling_b(t_env **env, char **interput)
{
	if (interput[0] && ft_strcmp(interput[0], "cd") == 0)
		handling_cd(env, interput, 1);
	if (interput[0] && ft_strcmp("env", interput[0]) == 0)
		handling_env(env, 1);
	if (interput[0] && ft_strcmp(interput[0], "pwd") == 0)
		handling_pwd(env, 1);
	if (interput[0] && ft_strcmp(interput[0], "echo") == 0)
		handling_echo(interput, 1);
	if (interput[0] && ft_strcmp(interput[0], "export") == 0)
		handling_export(interput, env, 1);
	if (interput[0] && ft_strcmp(interput[0], "unset") == 0)
		handling_unset(env, interput, 1);
	if (interput[0] && ft_strcmp(interput[0], "exit") == 0)
		handling_exit(interput, env, 1);
}

int	handling_b_v2(t_env **env, char **interput)
{
	int	j;

	j = 1;
	if (interput[0] && ft_strcmp(interput[0], "cd") == 0)
		j = handling_cd(env, interput, 0);
	if (interput[0] && ft_strcmp("env", interput[0]) == 0)
		j = handling_env(env, 0);
	if (interput[0] && ft_strcmp(interput[0], "pwd") == 0)
		j = handling_pwd(env, 0);
	if (interput[0] && ft_strcmp(interput[0], "echo") == 0)
		j = handling_echo(interput, 0);
	if (interput[0] && ft_strcmp(interput[0], "export") == 0)
		j = handling_export(interput, env, 0);
	if (interput[0] && ft_strcmp(interput[0], "unset") == 0)
		j = handling_unset(env, interput, 0);
	if (interput[0] && ft_strcmp(interput[0], "exit") == 0)
		j = handling_exit(interput, env, 0);
	if (j == 0)
		return (0);
	return (1);
}
