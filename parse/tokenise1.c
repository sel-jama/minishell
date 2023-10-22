/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:42:09 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/17 20:02:24 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_regular_token(t_cmds **input, int i, int *end)
{
	while ((*input)->cmd_line[i] && (*input)->cmd_line[i] != ' '
		&& (*input)->cmd_line[i] != '\t')
	{
		if ((*input)->cmd_line[i] == '"' || (*input)->cmd_line[i] == '\'')
		{
			if (i != 0 && (*input)->cmd_line[i] == '\\')
			{
				i++;
				continue ;
			}
			*end = get_end_of_quote((*input)->cmd_line, &i);
			break ;
		}
		if ((ft_strchr(TOKEN_DELIMETERS, (*input)->cmd_line[i])
				&& !is_between_quote((*input)->cmd_line, i)))
			break ;
		i++;
		*end = i;
	}
	return (*end);
}

int	process_token(t_cmds **input, t_list **lst_token, int i)
{
	int		start;
	int		end;
	char	*token;

	spaces_skiping(input, &i);
	if (!(*input)->cmd_line[i])
		return (i);
	start = i;
	if ((*input)->cmd_line[i] == '"' || (*input)->cmd_line[i] == '\'')
		end = get_end_of_quote((*input)->cmd_line, &i);
	else if (ft_strchr(TOKEN_DELIMETERS, (*input)->cmd_line[i]))
		end = process_delimiter(input, i, &i);
	else
		end = process_regular_token(input, i, &i);
	token = extract_token((*input)->cmd_line, start, end);
	if (!(*lst_token))
		*lst_token = ft_lstnew(token);
	else
		ft_lstadd_back(lst_token, ft_lstnew(token));
	return (end);
}

void	tokenize_input(t_cmds **input)
{
	int		i;
	t_list	*lst_token;

	lst_token = NULL;
	i = 0;
	while ((*input)->cmd_line[i])
		i = process_token(input, &lst_token, i);
	(*input)->tokens_arr = get_array(&lst_token);
	ft_lstclear(&lst_token, &free);
}

void	extract_interval(char *line, int *start, int *end, int i)
{
	*start = -1;
	*end = 0;
	while (i >= 0)
	{
		if (line[i] == '\\' && line[i + 1])
			i -= 2;
		if (line[i] == '"' || line[i] == '\'')
			*start = i;
		i--;
	}
	i = *start + 1;
	while (line[i])
	{
		if (line[i] == '\\' && line[i + 1])
			i += 2;
		if (*start >= 0 && line[i] == line[*start])
		{
			*end = i;
			break ;
		}
		i++;
	}
}

void	fill_portion_with_spaces(char **str, int start, int end)
{
	int		a;
	char	*line;

	line = *str;
	a = start;
	while (a <= end)
	{
		line[a] = ' ';
		a++;
	}
}
