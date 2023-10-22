/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:40:57 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 14:40:28 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_do_that_doc(t_cmds **input, char *str, char *get)
{
	char	*new;

	(*input)->value = ft_strdup(get);
	new = ft_strjoin((*input)->first, get);
	free(get);
	free((*input)->first);
	(*input)->str = ft_strjoin(new, (*input)->last);
	free((*input)->last);
	free(new);
	free(str);
}

char	*replace_doc(t_cmds **input, char *str, int start, int end)
{
	int		len;
	char	*get;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	store_value_doc(input, str, start, end);
	if (!str[start + 1]
		|| ft_strchr(TOKEN_DELIMETERS, str[start + 1]))
		get = ft_strdup("$");
	else if ((*input)->value[0] == '?')
		get = get_exitstatus_doc();
	else
		get = ft_getvalue(input, (*input)->value);
	store_first_doc(input, str, start);
	store_last_doc(input, str, len, end);
	free ((*input)->value);
	if (!get)
	{
		ft_do_this_doc(input, str, get);
		return (NULL);
	}
	ft_do_that_doc(input, str, get);
	return ((*input)->value);
}

int	get_end_doc(t_cmds **input, char *str, int j)
{
	(void)input;
	while (str[j] && str[j] != '\''
		&& str[j] != '"' && str[j] != ' '
		&& str[j] != '\t' && str[j] != '\\'
		&& str[j] != '$' && !ft_strchr(SPECIALS, str[j])
		&& !ft_strchr(TOKEN_DELIMETERS, str[j]))
		j++;
	return (j);
}

void	expand_special_doc(t_cmds **input, char *str, int j, int *end)
{
	if (str[j] == '?')
		*end = j + 1;
	else
	{
		if (str[j] >= '0' && str[j] <= '9')
			j++;
		else
			j = get_end_doc(input, str, j);
		*end = j;
	}
}

void	expand_to_key_doc(t_cmds **input, char *str, int *j)
{
	char	*value;
	int		v;

	value = replace_doc(input, str,
			(*input)->start, (*input)->end);
	if (!value)
		*j = 0;
	if (value != NULL)
	{
		if (ft_strchr(value, ' '))
			(*input)->space_found = 1;
		v = -1;
		while (value[++v])
		{
			if (value[v] == '$')
				(*input)->rank += 1;
		}
		*j = (*input)->start + ft_strlen(value);
		(*input)->rank -= 1;
		free((*input)->value);
	}
}
