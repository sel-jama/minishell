/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:41:47 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 07:04:22 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_total_len(char **arr)
{
	int	total_length;
	int	i;

	total_length = 0;
	i = 0;
	while (arr[i])
	{
		total_length += ft_strlen(arr[i]);
		total_length += 1;
		i++;
	}
	return (total_length);
}

char	*concatenate_strings(char **arr)
{
	int		len;
	int		i;
	char	*result;
	int		j;
	int		a;

	if (!arr)
		return (NULL);
	len = count_total_len(arr);
	result = (char *)malloc((len) * sizeof(char));
	if (!result)
		alloc_error();
	i = 0;
	a = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
			result[a++] = arr[i][j++];
		if (arr[i] && arr[i + 1])
			result[a++] = ' ';
		i++;
	}
	result[a] = '\0';
	return (result);
}
