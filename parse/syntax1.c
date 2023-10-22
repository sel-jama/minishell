/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:42:05 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/17 18:56:56 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_quotes(int *unclosed, char *line, int i)
{
	int	skipped;

	skipped = 0;
	if (i != 0 && is_quote_skipped(line, i))
		skipped = 1;
	if (*unclosed == 0 && line[i] == '"' && !skipped)
		*unclosed = 1;
	else if (*unclosed == 0 && line[i] == '\'' && !skipped)
		*unclosed = 2;
	else if (*unclosed == 1 && line[i] == '"' && !skipped)
		*unclosed = 0;
	else if (*unclosed == 2 && line[i] == '\'' && !skipped)
		*unclosed = 0;
}

int	unclosed_qoute(char *line)
{
	int	i;
	int	unclosed;

	i = 0;
	unclosed = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			process_quotes(&unclosed, line, i);
		i++;
	}
	if (unclosed == 1 || unclosed == 2)
	{
		ft_putendl_fd("syntax error: unclosed quotes", 2);
	}
	return (unclosed);
}

int	is_quote_skipped(char *line, int index)
{
	int	s;
	int	i;

	i = index - 1;
	s = 0;
	while (i != 0 && line[i] == '\\')
	{
		s += 1;
		i--;
	}
	if (s == 0 || s % 2 == 0)
		return (0);
	return (1);
}

int	check_wspaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
		i++;
	if (!line[i])
		return (0);
	return (1);
}

int	check_syntax(char *line)
{
	if (!check_wspaces(line) || unclosed_qoute(line)
		|| !check_successive_del(line, "><") || !check_d_del_errors(line, "<>")
		|| !check_successive_del(line, "|")
		|| !check_del_position(line) || !check_d_del_errors(line, "|"))
	{
		g_exit_status = 258;
		return (0);
	}
	return (1);
}
