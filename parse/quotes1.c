/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:41:52 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 14:42:38 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_and_alloc(int *index, int *i, const char *line, char *result)
{
	if (!line)
		return (0);
	*index = 0;
	*i = 0;
	if (!result)
		alloc_error();
	return (1);
}

char	*copy_with_skips(const char *line, int start, int end, int skips)
{
	char	*result;
	int		index;
	int		i;
	int		len;

	len = ft_strlen(line) + skips + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (!check_and_alloc(&index, &i, line, result))
		return (NULL);
	while (line[i])
	{
		if (i >= start && line[i] == '\\' && i < end)
		{
			if (i + 1 != end && (line[i + 1] == '\'' || line[i + 1] == '"'))
			{
				result[index++] = line[i++];
				continue ;
			}
			result[index++] = '\\';
		}
		result[index++] = line[i];
		i++;
	}
	result[index] = '\0';
	return (result);
}

char	*add_one_skip(char **str, int start, int *end, int skips)
{
	char	*line;
	char	*result;

	line = *str;
	result = copy_with_skips(line, start + 1, *end, skips);
	if (!result)
		return (NULL);
	*end += skips;
	free(line);
	return (result);
}

char	*skip_char_inbetween(char *line, int s, int *e)
{
	int		skips;
	char	*new;
	int		i;

	skips = 0;
	i = s;
	new = NULL;
	while (i <= *e)
	{
		if (line[i] == '\\')
		{
			if (i + 1 != *e && (line[i + 1] == '\'' || line[i + 1] == '"'))
			{
				i++;
				continue ;
			}
			skips++;
		}
		i++;
	}
	if (skips >= 1)
		new = add_one_skip(&line, s, e, skips);
	if (new)
		return (new);
	return (line);
}

void	get_start_and_end(int *s, int *e, char *line, int i)
{
	if (line[i] == '\'' || line[i] == '"')
	{
		if (*s < 0)
			*s = i;
		else if (!*e && line[*s] == line[i] && line[i - 1] != '\\')
			*e = i;
	}
}
