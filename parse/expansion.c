/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:10:28 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 14:40:40 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dollar_only(char *line, int index)
{
	if (is_between_quote(line, index) && (!line[index + 1]
			|| (line[index + 1] == ' ' || line[index + 1] == '\t'
				|| line[index + 1] == '"' || line[index + 1] == '\'')))
		return (1);
	return (0);
}

int	check_if_skipped(char *line, int rank)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (line[i])
	{
		if (line[i] == '$' && i != 0 && line[i - 1] == '\\')
		{
			r += 1;
			if (r == rank)
			{
				free (line);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	get_dollar_index(char *line, int rank)
{
	int	index;
	int	r;
	int	i;

	index = 0;
	r = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			index = i;
			r += 1;
		}
		if (index && r == rank)
			break ;
		i++;
	}
	return (index);
}

void	retrieve_start_and_end(char *line, int *start, int *end, int index)
{
	int	i;

	while (ft_strchr(line, '\'') || ft_strchr(line, '"'))
	{
		*start = -1;
		*end = 0;
		i = index + 1;
		while (--i >= 0)
		{
			if (line[i] == '"' || line[i] == '\'')
				*start = i;
		}
		i = *start;
		while (line[++i] && !(*end))
		{
			if (*start >= 0 && line[i] == line[*start])
				*end = i;
		}
		if (*start >= 0 && !(*end))
			*end = i;
		if (*start <= 0 || (index > *start && index < *end))
			break ;
		else
			insert_spaces_between(&line, *start, *end);
	}
}

void	insert_spaces_between(char **str, int start, int end)
{
	char	*line;
	int		a;

	line = *str;
	a = start;
	while (a <= end)
	{
		line[a] = ' ';
		a++;
	}
}
