/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 20:22:30 by sel-jama          #+#    #+#             */
/*   Updated: 2022/11/01 05:41:12 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_substrs(char const *s, char c)
{
	int	i;
	int	words;

	if (s == 0 || s[0] == 0)
		return (0);
	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || !s[i + 1]))
			words++;
		i++;
	}
	return (words);
}

static int	lenght_strs(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**free_arr(char **arr, int j)
{
	int	i;

	i = j - 1;
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (NULL);
}

static char	**malloc_fill_strs(char const *s, char c, char **arr)
{
	int	i;
	int	j;
	int	len;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = lenght_strs(s + i, c);
			arr[j] = (char *)malloc(sizeof(char) * (len + 1));
			if (!arr[j])
				return (free_arr(arr, j));
			k = 0;
			while (k < len)
				arr[j][k++] = s[i++];
			arr[j][k] = '\0';
			j++;
		}
		else
			i++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**arr;

	if (!s)
		return (NULL);
	words = count_substrs(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr = malloc_fill_strs(s, c, arr);
	arr[words] = NULL;
	return (arr);
}
