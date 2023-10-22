/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:27:01 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 21:27:03 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

void	print_fun(char **interput, int t)
{
	int	i;

	i = 0;
	if (t == 1 && interput[1] && ft_strncmp(interput[0], "echo", 4) == 0
		&& ft_strncmp(interput[1], "-n", 2) == 0)
	{
		i = 1;
		while (interput[i])
		{
			if (t == 1)
				t = check_parametre(interput[i]);
			if (t == 0)
			{
				ft_putstr_fd(interput[i], 1);
				if (interput[i + 1])
					ft_putstr_fd(" ", 1);
			}
			i++;
		}
	}
}

void	print_fun2(char **interput, int t)
{
	int	i;

	i = 0;
	if (t == 0 && interput[0] && ft_strncmp(interput[0], "echo", 4) == 0)
	{
		i = 1;
		if (interput[i])
		{
			while (interput[i])
			{
				ft_putstr_fd(interput[i], 1);
				if (interput[i + 1])
					ft_putstr_fd(" ", 1);
				i++;
			}
		}
		ft_putstr_fd("\n", 1);
	}
}

void	ft_echo(char **interput)
{
	int	t;

	t = 0;
	if (interput[1] == NULL)
	{
		ft_putendl_fd("", 1);
		return ;
	}
	t = check_parametre(interput[1]);
	print_fun(interput, t);
	print_fun2(interput, t);
	g_exit_status = 0;
}

int	check_parametre(char *interput)
{
	int	i;

	i = 1;
	while (interput && interput[0] == '-' && interput[i])
	{
		if (interput[i] != 'n')
			return (0);
		i++;
	}
	i = 1;
	if (interput[0] && interput[0] != '-')
		return (0);
	return (1);
}
