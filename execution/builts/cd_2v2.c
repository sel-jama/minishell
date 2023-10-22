/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2v2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:29:46 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:12:51 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_cd_own(char **interput, int j)
{
	char	*str;
	int		t;

	str = NULL;
	t = 0;
	str = getcwd(str, 0);
	ft_cd_back2(j, str);
	t = chdir(interput[1]);
	if (t == -1)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		free(str);
		if (j == 1)
			exit(1);
		g_exit_status = 1;
		return ;
	}
	free(str);
}

void	ft_cd_back(t_env **env, int j, char *ptr, char **interput)
{
	int	t;

	t = 0;
	change_oldpwd(env);
	t = chdir(interput[1]);
	if (t == -1)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd:", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putendl_fd("No such file or directory", 2);
		if (j == 1)
			exit(0);
		g_exit_status = 0;
		return ;
	}
	ptr = getcwd(ptr, 0);
	if (ft_cd_back2(j, ptr) == 1)
		return ;
	change_pwd(env, ptr);
	g_exit_status = 0;
	free(ptr);
}
