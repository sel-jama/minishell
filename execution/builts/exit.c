/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:25:58 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/19 13:30:44 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	ft_exit2_p(char *interput)
{
	ft_putstr_fd(interput, 2);
	ft_putendl_fd(": too many arguments", 2);
}

int	ft_exit2(char **interput, int d, int j)
{
	while (interput[j])
	{
		if (j == 2)
		{
			ft_exit2_p(interput[j]);
			g_exit_status = 1;
			return (1);
		}
		while (interput[j][++d])
		{
			if (interput[j][0] == '-')
				d++;
			if (interput[j][d] < '0' || interput[j][d] > '9')
			{
				ft_putstr_fd(interput[j], 2);
				ft_putendl_fd(": numeric argument required", 2);
				g_exit_status = ft_atoi(interput[j]);
				exit(255);
			}
		}
		j++;
	}
	if (j == 1)
		exit(g_exit_status);
	return (0);
}

void	ft_exit3(char **interput, int j, int i)
{
	if (interput && i == 1)
	{
		g_exit_status = ft_atoi(interput[j]);
		exit(ft_atoi(interput[j]));
	}
	if (interput && i == 0)
	{
		g_exit_status = ft_atoi(interput[j]);
		ft_putendl_fd("exit", 2);
		exit(ft_atoi(interput[j]));
	}
}

void	ft_exit_(char **interput, int i, t_env **lst)
{
	int	j;
	int	d;

	(void)i;
	(void)lst;
	j = 1;
	d = -1;
	if (ft_exit2(interput, d, j) == 0)
	{
		if (((unsigned long long )ft_atoi(interput[j]) > 9223372036854775807
				&& interput[j][0] != '-' ) || ft_strlen(interput[j]) > 19)
		{
			ft_putstr_fd(interput[j], 2);
			ft_putendl_fd(": numeric argument required", 2);
			g_exit_status = 255;
			exit(255);
		}
		if ((unsigned long long)ft_atoi(interput[j]) < 0)
			exit(ft_atoi(interput[j]));
		ft_exit3(interput, j, i);
	}
}
