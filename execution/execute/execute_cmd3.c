/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:41:15 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:10:03 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	exec_cmd3_helper(char **ptr, int i, char **interput, char **env)
{
	int		t;
	char	*str2;
	char	*str;

	t = 1;
	str2 = NULL;
	str = NULL;
	i = 0;
	while (ptr[i])
	{
		str2 = ft_strjoin(ptr[i], "/");
		free(ptr[i]);
		str = ft_strjoin(str2, interput[0]);
		free(str2);
		t = exec_cmd4(interput, str, env, ptr);
		free(str);
		i++;
	}
	return (t);
}

int	exec_cmd3(char **interput, char **env, int i)
{
	char	**ptr;
	char	*str;
	int		t;

	t = 0;
	if (env && interput[0])
	{
		t = exec_cmd3_v2(interput, env);
		if (t == 1)
		{
			str = get_path(env);
			ptr = ft_split(str, ':');
			free(str);
			t = exec_cmd3_helper(ptr, i, interput, env);
		}
		else
			return (t);
	}
	if (ch_in(interput) != 0 && interput[0] && access(interput[0], X_OK) == 0)
		execve(interput[0], interput, env);
	return (t);
}

void	exec_v2(int t)
{
	if (t == 3)
	{
		ft_putendl_fd(": permission denied", 2);
		g_exit_status = 126;
		exit(126);
	}
	if (t == 2)
	{
		ft_putendl_fd(": No such file or directory", 2);
		g_exit_status = 1;
		exit(127);
	}
}

void	exec_1(char **interput, int t)
{
	if ((t == 0 || t == 3 || t == 2) && interput)
	{
		if (interput[0])
		{
			if (!interput[0][1])
				ft_putchar_fd(interput[0][0], 1);
			else
				ft_putstr_fd(interput[0], 2);
			if (t == 0)
			{
				ft_putendl_fd(": command not found", 2);
				g_exit_status = 127;
				exit(127);
			}
			exec_v2(t);
		}
	}
}
