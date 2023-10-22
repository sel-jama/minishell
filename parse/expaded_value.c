/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expaded_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:40:45 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/18 02:13:51 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words(const char *line)
{
	int	i;
	int	word;
	int	in_word;

	word = 0;
	in_word = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\t'
			|| line[i] == '\n' || line[i] == '\r')
			in_word = 0;
		else
		{
			if (!in_word)
			{
				in_word = 1;
				word++;
			}
		}
		i++;
	}
	return (word);
}

void	skip_spaces(t_cmds **in, int i, int *g, int *q)
{
	int	j;
	int	k;

	j = *g;
	k = *q;
	while ((*in)->tokens_arr[i][j] && ((*in)->tokens_arr[i][j] == ' '
		|| (*in)->tokens_arr[i][j] == '\t'))
		j++ ;
	if (k != 1)
		(*in)->quoted[k++] = ' ';
	*g = j;
	*q = k;
}

void	insert_quotes(t_cmds **in, int i, int *g, int *q)
{
	int	j;
	int	k;

	j = *g;
	while ((*in)->tokens_arr[i][j] && ((*in)->tokens_arr[i][j] == ' '
		|| (*in)->tokens_arr[i][j] == '\t'))
		j++ ;
	if (!(*in)->tokens_arr[i][j])
	{
		*g = j;
		return ;
	}
	k = *q;
	(*in)->quoted[k++] = '"';
	skip_spaces(in, i, g, &k);
	if (!(*in)->tokens_arr[i][*g])
		return ;
	(*in)->quoted[k++] = '"';
	*q = k;
}

void	count_len_and_init(t_cmds **input, int i, int *len, int *var)
{
	int	size;
	int	j;
	int	words;

	j = 0;
	*var = 0;
	words = count_words((*input)->tokens_arr[i]);
	size = ft_strlen((*input)->tokens_arr[i]);
	while ((*input)->tokens_arr[i][j])
	{
		if ((*input)->tokens_arr[i][j] == ' '
			|| (*input)->tokens_arr[i][j] == '\t')
			size--;
		j++;
	}
	*len = words * 2;
	*len += words - 1;
	*len += size + 1;
}

char	*insert_limits(t_cmds **input, int i)
{
	int	j;
	int	k;
	int	len;

	count_len_and_init(input, i, &len, &j);
	(*input)->quoted = (char *)malloc(sizeof(char) * len);
	if (!(*input)->quoted)
		alloc_error();
	k = 0;
	(*input)->quoted[k++] = '"';
	skip_spaces(input, i, &j, &k);
	while ((*input)->tokens_arr[i][j])
	{
		if ((*input)->tokens_arr[i][j] == ' '
				|| (*input)->tokens_arr[i][j] == '\t')
			insert_quotes(input, i, &j, &k);
		if (!(*input)->tokens_arr[i][j])
			break ;
		(*input)->quoted[k++] = (*input)->tokens_arr[i][j++];
	}
	(*input)->quoted[k] = '"';
	(*input)->quoted[k + 1] = '\0';
	free((*input)->tokens_arr[i]);
	(*input)->tokens_arr[i] = (*input)->quoted;
	return ((*input)->quoted);
}
