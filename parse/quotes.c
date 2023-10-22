/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 02:57:48 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/21 00:42:26 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**remove_token(char **token_arr, int index, int num_of_tokens)
{
	int		i;
	int		j;
	int		index_to_remove;
	char	**new_arr;

	index_to_remove = index;
	i = 0;
	if (!token_arr || !token_arr[index_to_remove])
		return (token_arr);
	new_arr = (char **)malloc(sizeof(char *) * (num_of_tokens));
	if (!new_arr)
		alloc_error();
	j = 0;
	while (token_arr[i])
	{
		if (i == index_to_remove)
			i += 1;
		if (!token_arr[i])
			break ;
		new_arr[j++] = ft_strdup(token_arr[i]);
		i++;
	}
	new_arr[j] = NULL;
	ft_clean_up(token_arr);
	return (new_arr);
}

int	special_char_inbetween(char *line, int start, int end)
{
	int		ret;
	char	*special;

	ret = 0;
	special = extract_token(line, start + 1, end);
	if (!ft_strcmp(special, "|") || !ft_strcmp(special, ">")
		|| !ft_strcmp(special, ">>") || !ft_strcmp(special, "<")
		|| !ft_strcmp(special, "<<"))
		ret = 1;
	free(special);
	return (ret);
}

int	count_specials(const char *line, int start, int end)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (i < end)
	{
		if (line[i] && ft_strchr(TOKEN_DELIMETERS, line[i]))
			count++;
		i++;
	}
	return (count);
}

char	*copy_with_specials(const char *line, int start, int *end)
{
	char	*result;
	int		len;
	int		index;
	int		i;

	i = count_specials(line, start, *end);
	*end += i;
	len = ft_strlen(line);
	result = malloc(len + i + 1);
	if (!result)
		alloc_error();
	index = 0;
	i = -1;
	while (++i < start)
		result[index++] = line[i++];
	i = start;
	while (line[i])
	{
		if (line[i] && ft_strchr(TOKEN_DELIMETERS, line[i]) && i < *end)
			result[index++] = '\\';
		result[index++] = line[i];
		i++;
	}
	result[index] = '\0';
	return (result);
}

char	*skip_specials(char **str, int start, int *end)
{
	char	*line;
	char	*result;

	line = *str;
	result = copy_with_specials(line, start + 1, end);
	free(line);
	return (result);
}
