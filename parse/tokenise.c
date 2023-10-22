/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 08:49:39 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 14:42:58 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	get_end_of_quote(char *line, int *index)
{
	int		i;
	int		flag;

	flag = 0;
	i = *index;
	while (line[++i] && line[i] != line[*index])
	{
		if (line[i] == '\\' && line[i + 1])
			i += 2;
	}
	if (line[i])
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
	{
		if (ft_strchr(TOKEN_DELIMETERS, line[i]) && !is_between_quote(line, i))
			break ;
		flag = 1;
		if (line[i] == '"' || line[i] == '\'')
			break ;
		i++;
	}
	if (flag && (line[i] == '"' || line[i] == '\''))
		get_end_of_quote(line, &i);
	*index = i;
	return (i);
}

void	spaces_skiping(t_cmds **input, int *index)
{
	int	i;

	i = *index;
	while ((*input)->cmd_line[i] && ((*input)->cmd_line[i] == ' '
			|| (*input)->cmd_line[i] == '\t'))
		i++;
	*index = i;
}

void	check_and_getend(t_cmds **input, int i, int *end)
{
	if ((*input)->cmd_line[i] == '|')
		*end = i + 1;
	else if ((*input)->cmd_line[i] == '>'
		&& (*input)->cmd_line[i + 1] == '>')
		*end = i + 2;
	else if ((*input)->cmd_line[i] == '<'
		&& (*input)->cmd_line[i + 1] == '<')
		*end = i + 2;
	else if ((*input)->cmd_line[i] == '>')
		*end = i + 1;
	else if ((*input)->cmd_line[i] == '<')
		*end = i + 1;
}

int	process_delimiter(t_cmds **input, int i, int *end)
{
	if (!is_between_quote((*input)->cmd_line, i))
	{
		check_and_getend(input, i, end);
	}
	else
		(*end)++;
	return (*end);
}
