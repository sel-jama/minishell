/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:41:20 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/18 00:32:17 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_do_this(t_cmds **input, int *index)
{
	char	*result;
	int		i;

	i = *index;
	result = ft_strjoin((*input)->first, (*input)->last);
	free((*input)->first);
	free((*input)->last);
	if (!result || (result[0] == '\0' && (*input)->num_of_tokens > 1))
	{
		if (i > 0 && is_redirection((*input)->tokens_arr[i - 1]))
			(*input)->ambig_file = 1;
		(*input)->tokens_arr = remove_token((*input)->tokens_arr,
				i, (*input)->num_of_tokens);
		*index -= 1;
		(*input)->num_of_tokens -= 1;
		(*input)->rank = 0;
		free(result);
	}
	else
	{
		free((*input)->tokens_arr[i]);
		(*input)->tokens_arr[i] = result;
	}
}

void	ft_do_that(t_cmds **input, char *get, int i)
{
	char	*new;
	char	*result;
	int		inquote;

	inquote = 0;
	if ((ft_strchr((*input)->first, '"') || ft_strchr((*input)->first, '\''))
		&& (ft_strchr((*input)->last, '"') || ft_strchr((*input)->last, '\'')))
		inquote = 1;
	(*input)->value = ft_strdup(get);
	new = ft_strjoin((*input)->first, get);
	free(get);
	free((*input)->first);
	result = ft_strjoin(new, (*input)->last);
	free((*input)->last);
	free(new);
	free((*input)->tokens_arr[i]);
	(*input)->tokens_arr[i] = result;
	if (i != 0 && is_redirection((*input)->tokens_arr[i - 1])
		&& ft_strchr(result, ' ') && !inquote)
		(*input)->ambig_file = 1;
}

char	*replace_with_expansion(t_cmds **input, int *i, int start, int end)
{
	int		len;
	char	*get;

	if (!(*input)->tokens_arr[*i])
		return (NULL);
	len = ft_strlen((*input)->tokens_arr[*i]);
	store_value(input, start, end, *i);
	if (!(*input)->tokens_arr[*i][start + 1] ||
			ft_strchr(TOKEN_DELIMETERS, (*input)->tokens_arr[*i][start + 1])
			|| ft_strchr(SPECIALS, (*input)->tokens_arr[*i][start + 1]))
		get = ft_strdup("$");
	else if ((*input)->value[0] == '?')
		get = get_exitstatus();
	else
		get = ft_getvalue(input, (*input)->value);
	store_first(input, start, *i);
	store_last(input, *i, len, end);
	free((*input)->value);
	if (!get)
	{
		ft_do_this(input, i);
		return (NULL);
	}
	ft_do_that(input, get, *i);
	return ((*input)->value);
}

int	get_end(t_cmds **input, int i, int j)
{
	t_cmds	*in;

	in = *input;
	while (in->tokens_arr[i][j] && in->tokens_arr[i][j] != '\''
		&& in->tokens_arr[i][j] != '"' && in->tokens_arr[i][j] != ' '
		&& in->tokens_arr[i][j] != '\t' && in->tokens_arr[i][j] != '\\'
		&& in->tokens_arr[i][j] != '$'
		&& !ft_strchr(SPECIALS, in->tokens_arr[i][j])
		&& !ft_strchr(TOKEN_DELIMETERS, in->tokens_arr[i][j]))
		j++;
	return (j);
}

void	expand_special(t_cmds **input, int i, int *j)
{
	(*input)->rank += 1;
	(*input)->start = *j;
	*j += 1;
	if ((*input)->tokens_arr[i][*j] == '?')
		(*input)->end = *j + 1;
	else
	{
		if ((*input)->tokens_arr[i][*j] >= '0'
			&& (*input)->tokens_arr[i][*j] <= '9')
			*j += 1;
		else
			*j = get_end(input, i, *j);
		(*input)->end = *j;
	}
}
