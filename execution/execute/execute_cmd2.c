/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:40:43 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:10:25 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*get_path2(char *ptr, char *str, char **env, int i)
{
	int	j;
	int	t;

	j = 0;
	t = 0;
	while (env[++i])
		if (!ft_strncmp("PATH=", env[i], 5))
			break ;
	ptr = env[i];
	if (ptr)
	{
		t = ft_strlen(ptr) - 5;
		str = malloc(sizeof(char *) * t);
		i = 5;
		while (ptr[i])
		{
			str[j] = ptr[i];
			j++;
			i++;
		}
		str[j] = '\0';
	}
	return (str);
}

char	*get_path(char **env)
{
	int		i;
	char	*ptr;
	char	*str;

	i = 0;
	ptr = NULL;
	str = NULL;
	if (!env)
	{
		ft_putendl_fd("No such file or directory", 2);
		g_exit_status = 127;
		exit(127);
	}
	i = -1;
	str = get_path2(ptr, str, env, i);
	if (!str)
	{
		ft_putendl_fd("No such file or directory", 2);
		g_exit_status = 127;
		exit(127);
	}
	return (str);
}

int	exec_cmd4(char **interput, char *str, char **env, char **ptr)
{
	int	t;

	t = 0;
	if (!access(str, X_OK))
	{
		t = 1;
		if (execve(str, interput, env) == 1)
		{
			free(str);
			free(ptr);
			g_exit_status = 127;
			exit(127);
		}
	}
	return (t);
}

int	ch_in(char **interput)
{
	int	t;
	int	d;

	t = 0;
	d = 0;
	if (interput && interput[0] && interput[0][0])
	{
		if (interput[0][0] == '.' && interput[0][1] == '.')
			return (0);
		if (interput[0][0] == '.' && interput[0][1] == '\0')
			return (0);
		while (interput[0][t])
		{
			if (interput[0][t] != '/' && interput[0][t] != '.')
				return (1);
			t++;
		}
	}
	return (0);
}

int	exec_cmd3_v2(char **interput, char **env)
{
	int	acc;

	if (interput[0][0] == '.' || interput[0][0] == '/')
	{
		acc = access(interput[0], F_OK);
		if (!acc)
		{
			acc = access(interput[0], X_OK);
			if (!acc)
				execve(interput[0], interput, env);
			else
				return (3);
		}
		return (2);
	}
	return (1);
}
