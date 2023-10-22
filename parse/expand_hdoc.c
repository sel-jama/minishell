/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:37:44 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 07:28:14 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_exitstatus_doc(void)
{
	char	*exit_sts;

	exit_sts = ft_itoa(g_exit_status);
	if (!exit_sts)
		return (NULL);
	return (exit_sts);
}

void	store_value_doc(t_cmds **input, char *str, int start, int end)
{
	int	j;
	int	a;

	a = 0;
	j = start + 1;
	(*input)->value = (char *)malloc(sizeof(char) * (end - start));
	while (j < end)
	{
		(*input)->value[a] = str[j];
		a++;
		j++;
	}
	(*input)->value[a] = '\0';
}

void	store_first_doc(t_cmds **input, char *str, int start)
{
	int	a;
	int	j;

	a = 0;
	j = 0;
	(*input)->first = malloc(sizeof(char) * (start + 1));
	while (j < start)
	{
		(*input)->first[a] = str[j];
		a++;
		j++;
	}
	(*input)->first[a] = '\0';
}

void	store_last_doc(t_cmds **input, char *str, int len, int end)
{
	int	a;
	int	j;

	a = 0;
	(*input)->last = malloc(len - end + 1);
	if (str[end])
	{
		j = end;
		while (str[j])
		{
			(*input)->last[a] = str[j];
			j++;
			a++;
		}
	}
	(*input)->last[a] = '\0';
}

void	ft_do_this_doc(t_cmds **input, char *str, char *get)
{
	char	*new;

	get = ft_strdup("");
	new = ft_strjoin((*input)->first, get);
	free((*input)->first);
	free(get);
	(*input)->str = ft_strjoin(new, (*input)->last);
	free((*input)->last);
	free(new);
	free(str);
}
