/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:52:21 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 17:52:26 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	home_check(char *ptr, int j)
{
	if (!ptr)
	{
		ft_putstr_fd("cd: HOME not set\n", 1);
		if (j == 1)
			exit(1);
		g_exit_status = 1;
		return (0);
	}
	return (1);
}

void	ft_cd_home(t_env **env, char *ptr, t_env *enve, int j)
{
	(void)env;
	while (enve)
	{
		if (ft_strncmp(enve->content, "HOME=", 5) == 0)
		{
			change_oldpwd(env);
			ptr = malloc((sizeof(char)) * ft_strlen(enve->content) - 3);
			ft_strlcpy(ptr, enve->content + 5, (ft_strlen(enve->content) - 3));
			chdir(ptr);
			free(ptr);
			ptr = getcwd(NULL, 0);
			change_pwd(env, ptr);
			g_exit_status = 0;
			free(ptr);
		}
		enve = enve->next;
	}
	if (home_check(ptr, j) == 0)
		return ;
}

int	check_oldpwd(char *ptr, int j)
{
	if (!ptr)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 1);
		if (j == 1)
			exit(1);
		g_exit_status = 1;
		return (0);
	}
	return (1);
}

int	ft_cd_oldpwd(t_env **env, char *ptr, t_env *enve, int j)
{
	while (enve)
	{
		if (ft_strncmp(enve->content, "OLDPWD=", 7) == 0)
		{
			ptr = malloc((sizeof(char)) * ft_strlen(enve->content) - 6);
			ft_strlcpy(ptr, enve->content + 7, (ft_strlen(enve->content) - 5));
			change_oldpwd(env);
			chdir(ptr);
			free(ptr);
			ptr = NULL;
			ptr = getcwd(ptr, 0);
			change_pwd(env, ptr);
			free(ptr);
			g_exit_status = 0;
		}
		enve = enve->next;
	}
	if (check_oldpwd(ptr, j) == 0)
		return (0);
	return (1);
}

int	ft_cd_back2(int j, char *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		free(ptr);
		if (j == 1)
			exit(0);
		g_exit_status = 0;
		return (1);
	}
	return (0);
}
