/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:41:15 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 07:28:14 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_expandble(t_cmds **input, int rank)
{
	char	*line;
	int		start;
	int		end;
	int		index;

	start = 0;
	end = 0;
	index = 0;
	line = concatenate_strings((*input)->tokens_arr);
	if (!line || !check_if_skipped(line, rank))
		return (0);
	index = get_dollar_index(line, rank);
	if (ft_strchr(SPECIALS, line[index + 1]) || dollar_only(line, index))
	{
		free(line);
		return (0);
	}
	retrieve_start_and_end(line, &start, &end, index);
	if (start >= 0 && index > start && index < end && line[start] == '\'')
	{
		free (line);
		return (0);
	}
	free (line);
	return (1);
}

char	*get_exitstatus(void)
{
	char	*exit_sts;

	exit_sts = ft_itoa(g_exit_status);
	if (!exit_sts)
		return (NULL);
	return (exit_sts);
}

void	store_value(t_cmds **input, int start, int end, int i)
{
	int	j;
	int	a;

	a = 0;
	j = start + 1;
	(*input)->value = (char *)malloc(sizeof(char) * (end - start));
	while (j < end)
	{
		(*input)->value[a] = (*input)->tokens_arr[i][j];
		a++;
		j++;
	}
	(*input)->value[a] = '\0';
}

void	store_first(t_cmds **input, int start, int i)
{
	int	a;
	int	j;

	a = 0;
	j = 0;
	(*input)->first = malloc(sizeof(char) * (start + 1));
	while (j < start)
	{
		(*input)->first[a] = (*input)->tokens_arr[i][j];
		a++;
		j++;
	}
	(*input)->first[a] = '\0';
}

void	store_last(t_cmds **input, int i, int len, int end)
{
	int	a;
	int	j;

	a = 0;
	(*input)->last = malloc(len - end + 1);
	if ((*input)->tokens_arr[i][end])
	{
		j = end;
		while ((*input)->tokens_arr[i][j])
		{
			(*input)->last[a] = (*input)->tokens_arr[i][j];
			j++;
			a++;
		}
	}
	(*input)->last[a] = '\0';
}
