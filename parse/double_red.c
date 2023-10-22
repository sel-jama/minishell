/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 07:34:44 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/16 09:36:46 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_double_right(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>')
		{
			i += 2;
			if (line[i] == '>')
			{
				line[i] = ' ';
				line[i - 1] = '>';
			}
		}
		i++;
	}
	return (line);
}

char	*check_double_left(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<')
		{
			i += 2;
			if (line[i] == '<')
			{
				line[i] = ' ';
				line[i - 1] = '<';
			}
		}
		i++;
	}
	return (line);
}

char	*check_double_redirection(char *line)
{
	line = check_double_right(line);
	line = check_double_left(line);
	return (line);
}
