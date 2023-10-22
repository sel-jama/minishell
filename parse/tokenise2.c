/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:42:11 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 14:43:20 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_between_quote(char *cmd_line, int index)
{
	char	*line;
	int		start;
	int		end;

	start = -1;
	end = 0;
	if (!cmd_line)
		return (0);
	line = ft_strdup(cmd_line);
	if (!line)
		return (0);
	while (ft_strchr(line, '\'') || ft_strchr(line, '"'))
	{
		extract_interval(line, &start, &end, index);
		if (start >= 0 && end == 0)
			end = start + 1;
		if (start <= 0 || (index > start && index < end))
			break ;
		else
			fill_portion_with_spaces(&line, start, end);
	}
	free(line);
	if (index > start && index < end)
		return (1);
	return (0);
}

char	*extract_token(char *line, int start, int end)
{
	int		i;
	int		a;
	char	*new;

	i = start;
	new = NULL;
	if (end - start >= 0)
		new = malloc(end - start + 1);
	if (!new)
		return (NULL);
	a = 0;
	while (i < end)
	{
		new[a] = line[i];
		a++;
		i++;
	}
	new[a] = '\0';
	return (new);
}

char	*trim_input(char *line, int end)
{
	char	*new;
	int		l;
	int		i;
	int		a;

	l = ft_strlen(line);
	new = malloc(sizeof(char) * (l + 1 - end));
	i = end;
	a = 0;
	while (line[i])
	{
		new[a] = line[i];
		a++;
		i++;
	}
	new[a] = '\0';
	free(line);
	return (new);
}

char	**get_array(t_list **tokens_lst)
{
	int		len;
	int		i;
	t_list	*tmp;
	char	**tokens_arr;

	tmp = *tokens_lst;
	len = ft_lstsize((*tokens_lst));
	tokens_arr = (char **)malloc((len + 1) * sizeof(char *));
	i = 0;
	while (tmp)
	{
		tokens_arr[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	tokens_arr[i] = NULL;
	return (tokens_arr);
}
