/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:41:55 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/18 00:38:36 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*produce_unquoted_line(char *line, int start, int end, int red_befor)
{
	int		len;
	char	*new_line;
	int		a;
	int		b;

	len = ft_strlen(line);
	if (start == end - 1 && len <= 3 && !red_befor)
		len++;
	new_line = (char *)malloc(sizeof(char) * (len - 1));
	if (!new_line)
		alloc_error();
	b = 0;
	a = 0;
	while (line[a])
	{
		if (a == start && start == end - 1 && len <= 3 && !red_befor)
			new_line[b++] = ' ';
		if (a != start && a != end)
			new_line[b++] = line[a];
		a++;
	}
	new_line[b] = '\0';
	free (line);
	return (new_line);
}

void	init_vars(int *s, int *e, int *i, int *index)
{
	*s = -1;
	*e = 0;
	*i = *index;
}

char	*quote_removal(t_cmds **input, int n, int *index)
{
	int		start;
	int		end;
	int		i;
	char	*line;
	int		red;

	get_red(&red, input, n, &line);
	init_vars(&start, &end, &i, index);
	while (line[i])
	{
		get_start_and_end(&start, &end, line, i);
		if (start >= 0 && end != 0)
		{
			if (special_char_inbetween(line, start, end) == 1)
				line = skip_specials(&line, start, &end);
			else
				line = skip_char_inbetween(line, start, &end);
			line = produce_unquoted_line(line, start, end, red);
			*index = end - 1;
			return (line);
		}
		i++;
	}
	*index = -2;
	return (line);
}

void	quote_handling(t_cmds **input)
{
	int	i;
	int	start;

	start = 0;
	expand_token(input);
	if ((*input)->space_found == 1)
		manage_space_presence(input);
	i = -1;
	while (++i < (*input)->num_of_tokens)
	{
		if (!(*input)->tokens_arr[i])
			break ;
		if (!ft_strcmp((*input)->tokens_arr[i], "<<")
			&& (*input)->tokens_arr[i + 1]
			&& (ft_strchr((*input)->tokens_arr[i + 1], '"')
				|| ft_strchr((*input)->tokens_arr[i + 1], '\'')))
			(*input)->expand_doc = 0;
		start = 0;
		if (ft_strchr((*input)->tokens_arr[i], '\'')
			|| ft_strchr((*input)->tokens_arr[i], '"'))
		{
			while (start != -2)
				(*input)->tokens_arr[i] = quote_removal(input, i, &start);
		}
	}
}

void	manage_space_presence(t_cmds **input)
{
	int	i;

	free((*input)->cmd_line);
	(*input)->cmd_line = concatenate_strings((*input)->tokens_arr);
	if ((*input)->cmd_line[0] == ' ')
		return ;
	ft_clean_up((*input)->tokens_arr);
	tokenize_input(input);
	i = 0;
	while ((*input)->tokens_arr[i])
		i++;
	(*input)->num_of_tokens = i;
	(*input)->space_found = 0;
}
