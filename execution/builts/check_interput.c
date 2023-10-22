/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_interput.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:25:25 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:16:25 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	check_interput2(char *interput, int i)
{
	if (interput[i] == '+' && interput[i + 1] != '=')
	{
		ft_putstr_fd(interput, 2);
		ft_putendl_fd(" : not a valid indentifier", 2);
		g_exit_status = 1;
		return (0);
	}
	if (interput[i] == '+' && interput[i + 1] == '=')
		return (2);
	if (i != 0 && (interput[i] == '=' && ((interput[i - 1] == '_')
				|| (interput[i - 1] >= '0' && interput[i - 1] <= '9')
				|| (interput[i - 1] >= 'a' && interput[i - 1] <= 'z')
				|| (interput[i - 1] >= 'A' && interput[i - 1] <= 'Z'))))
		return (3);
	if (i >= 1 && (interput[i] < 'a' || interput[i] > 'z')
		&& (interput[i] < 'A' || interput[i] > 'Z') && (interput[i] != '_')
		&& (interput[i] < '0' || interput[i] > '9'))
	{
		ft_putstr_fd(interput, 2);
		ft_putendl_fd(": not a valid identifier", 2);
		g_exit_status = 1;
		return (0);
	}
	return (4);
}

int	check_interput(char *interput)
{
	int	i;
	int	t;

	t = 0;
	i = 0;
	while (interput[i])
	{
		if ((interput[0] < 'A' || interput[0] > 'Z')
			&& (interput[0] < 'a' || interput[0] > 'z') && (interput[0] != '_'))
		{
			ft_putstr_fd(interput, 2);
			ft_putendl_fd(": not a valid identifier", 2);
			g_exit_status = 1;
			return (0);
		}
		t = check_interput2(interput, i);
		if (t != 4)
			return (t);
		i++;
	}
	g_exit_status = 0;
	return (1);
}
