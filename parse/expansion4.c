/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:41:25 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/18 01:36:42 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_to_key(t_cmds **input, int *i, int *j)
{
	char	*value;
	int		v;

	(*input)->space_found = 0;
	value = replace_with_expansion(input, i,
			(*input)->start, (*input)->end);
	if (!value)
		*j = (*input)->start;
	if (value != NULL)
	{
		if (ft_strchr(value, ' '))
		{
			(*input)->space_found = 1;
			value = insert_limits(input, *i);
		}
		v = 0;
		while (value[v++])
		{
			if (value[v] == '$')
				(*input)->rank += 1;
		}
		*j = (*input)->start + ft_strlen(value);
		(*input)->rank -= 1;
		free((*input)->value);
	}
}

void	expand_token(t_cmds **input)
{
	int	i;
	int	j;

	i = -1;
	(*input)->start = 0;
	(*input)->end = 0;
	(*input)->indexes = NULL;
	while ((*input)->tokens_arr && (*input)->tokens_arr[++i])
	{
		if (i != 0 && !ft_strcmp((*input)->tokens_arr[i - 1], "<<"))
			continue ;
		j = 0;
		while ((*input)->tokens_arr[i][j])
		{
			if ((*input)->tokens_arr[i][j] && (*input)->tokens_arr[i][j] == '$')
			{
				expand_special(input, i, &j);
				if (is_expandble(input, (*input)->rank))
					expand_to_key(input, &i, &j);
			}
			if (manage_result(input, i, &j))
				break ;
		}
	}
}

int	manage_result(t_cmds **input, int i, int *j)
{
	if (i < 0 || !(*input)->tokens_arr || !(*input)->tokens_arr[i]
		|| !(*input)->tokens_arr[i][*j])
		return (1);
	if ((size_t)(*j) > ft_strlen((*input)->tokens_arr[i])
		&& !(*input)->tokens_arr[i][*j])
		return (1);
	if ((*input)->tokens_arr[i][*j] != '$')
		*j += 1;
	return (0);
}

char	*ft_getvalue(t_cmds **input, char *value)
{
	t_env	*env;
	char	*result;

	if (!value)
		return (NULL);
	env = NULL;
	if ((*input) && (*input)->env)
		env = (*input)->env;
	result = NULL;
	while (env)
	{
		if (env->content && ft_strncmp(env->content,
				value, ft_strlen(value)) == 0)
		{
			if (ft_strncmp(env->content + ft_strlen(value), "=", 1) == 0)
				result = ft_strdup(env->content + ft_strlen(value) + 1);
		}
		env = env->next;
	}
	if (result && (ft_strchr(result, '\'') || ft_strchr(result, '"')))
	{
		result = skip_quotes(result);
	}
	return (result);
}

char	*skip_quotes(char *value)
{
	int		i;
	int		j;
	int		quotes;
	char	*new;

	i = -1;
	quotes = 0;
	while (value[++i])
	{
		if (value[i] == '\'' || value[i] == '"')
			quotes++;
	}
	new = (char *)malloc(sizeof(char) * (i + quotes + 1));
	i = -1;
	j = 0;
	while (value[++i])
	{
		if (value[i] == '\'' || value[i] == '"')
			new[j++] = '\\';
		new[j++] = value[i];
	}
	new[j] = '\0';
	free(value);
	return (new);
}
