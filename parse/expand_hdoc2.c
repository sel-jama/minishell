/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:41:05 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 07:04:22 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_vars_doc(t_cmds **input, int *start, int *j)
{
	(*input)->rank += 1;
	*start = *j;
	*j += 1;
}

char	*expand_doc(t_cmds **input, char *str)
{
	int	j;

	(*input)->start = 0;
	(*input)->end = 0;
	(*input)->rank = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '$')
		{
			set_vars_doc(input, &(*input)->start, &j);
			expand_special_doc(input, str, j, &(*input)->end);
			expand_to_key_doc(input, str, &j);
			str = (*input)->str;
		}
		if (!str || !str[j])
			break ;
		if (str[j] != '$')
			j += 1;
	}
	return ((*input)->str);
}
