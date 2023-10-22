/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:26:22 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 18:26:24 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_cd_exf(t_env **env, char **interput, int j, char *ptr)
{
	char	*str;
	int		t;

	str = NULL;
	t = 0;
	change_oldpwd(env);
	str = interput[1];
	t = chdir(str);
	if (t == -1)
	{
		ft_putstr_fd(interput[1], 2);
		ft_putstr_fd(": Not a directory\n", 2);
		if (j == 1)
			exit(1);
		g_exit_status = 1;
		return ;
	}
	ptr = getcwd(ptr, 0);
	change_pwd(env, ptr);
	g_exit_status = 0;
	free(ptr);
}

int	ft_cd_check(char **interput, int j, char *str)
{
	str = ft_strjoin("/", interput[1]);
	if (access(str, F_OK) == -1)
	{
		ft_putstr_fd(interput[1], 2);
		free(str);
		ft_putendl_fd(": No such file or directory", 2);
		if (j == 1)
			exit(1);
		g_exit_status = 1;
		return (0);
	}
	free(str);
	return (1);
}

void	ft_cd_access(t_env **env, int j, char *ptr, char *str)
{
	int	t;

	t = 0;
	change_oldpwd(env);
	g_exit_status = 0;
	ptr = NULL;
	if (access(str, F_OK) == 0)
	{
		t = chdir(str);
		if (t == -1)
		{
			ft_putstr_fd("No such file or directory\n", 2);
			if (j == 1)
				exit(1);
			g_exit_status = 1;
			return ;
		}
		ptr = getcwd(ptr, 0);
		change_pwd(env, ptr);
		g_exit_status = 0;
		free(ptr);
		free(str);
	}
}

int	ft_cd_mult(char **interput, int j)
{
	if (interput[2])
	{
		ft_putendl_fd("cd: To many arguments", 2);
		if (j == 1)
			exit(1);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}
