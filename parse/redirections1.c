/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:42:00 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 07:28:14 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	output_redirection(t_content **content, t_cmds **all_cmds, int s)
{
	int	len;
	int	v;
	int	j;

	len = 0;
	v = 0;
	j = s;
	extract_filenames(all_cmds, s, &len);
	(*content)->filenames = (char **)malloc(sizeof(char *) * (len + 1));
	j = s;
	while ((*all_cmds)->tokens_arr[j]
		&& ft_strcmp((*all_cmds)->tokens_arr[j], "|"))
	{
		if (!ft_strcmp((*all_cmds)->tokens_arr[j], ">")
			|| !ft_strcmp((*all_cmds)->tokens_arr[j], ">>"))
			extract_output_red(content, all_cmds, &j, &v);
		else
			process_input_redir(content, all_cmds, j);
		if (!(*all_cmds)->tokens_arr[j])
			break ;
		j++;
	}
	(*content)->filenames[v] = NULL;
}

void	eof_len(int *len, t_cmds **cmds, int s)
{
	int	j;

	j = s;
	while ((*cmds)->tokens_arr[j] && ft_strcmp((*cmds)->tokens_arr[j], "|"))
	{
		if (!ft_strcmp((*cmds)->tokens_arr[j], "<<"))
			(*len)++;
		j++;
	}
}

void	heredoc_red(t_content **cntnt, t_cmds **all_cmds, int s)
{
	int	len;
	int	j;
	int	v;

	v = 0;
	len = 0;
	eof_len(&len, all_cmds, s);
	(*cntnt)->eof = (char **)malloc(sizeof(char *) * (len + 1));
	j = s;
	while ((*all_cmds)->tokens_arr[j]
		&& ft_strcmp((*all_cmds)->tokens_arr[j], "|"))
	{
		if (!ft_strcmp((*all_cmds)->tokens_arr[j], "<<"))
		{
			j++;
			if ((*all_cmds)->tokens_arr[j])
				(*cntnt)->eof[v++] = ft_strdup((*all_cmds)->tokens_arr[j]);
		}
		if (!(*all_cmds)->tokens_arr[j])
			break ;
		j++;
	}
	(*cntnt)->eof[v] = NULL;
	if ((*all_cmds)->expand_doc == 1)
		(*cntnt)->expand = 1;
}

int	error_redi(void)
{
	ft_putendl_fd("ambiguous redirect", 2);
	g_exit_status = 1;
	return (0);
}

int	validate_redirections(t_cmds **list)
{
	t_cmds	*all_cmds;

	all_cmds = *list;
	if (!all_cmds)
		return (error_redi());
	return (1);
}
