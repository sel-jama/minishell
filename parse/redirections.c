/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 06:14:52 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 07:24:52 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	infiles_len(int *len, t_cmds **cmds, t_content **ctnt, int s)
{
	int	l;
	int	i;

	l = 0;
	i = s;
	(*ctnt)->in = 1;
	while ((*cmds)->tokens_arr[i]
		&& ft_strcmp ((*cmds)->tokens_arr[i], "|"))
	{
		if (!ft_strcmp((*cmds)->tokens_arr[i], "<"))
			l++;
		i++;
	}
	*len = l;
}

void	input_redir(t_content **cnt, t_cmds **cmds, int start)
{
	int	len;
	int	v;
	int	i;

	infiles_len(&len, cmds, cnt, start);
	(*cnt)->infiles = (char **)malloc(sizeof(char *) * (len + 1));
	v = 0;
	i = start;
	while ((*cmds)->tokens_arr[i]
		&& ft_strcmp((*cmds)->tokens_arr[i], "|"))
	{
		if (!ft_strcmp((*cmds)->tokens_arr[i], "<"))
		{
			i++;
			if ((*cmds)->tokens_arr[i])
				(*cnt)->infiles[v++] = ft_strdup((*cmds)->tokens_arr[i]);
		}
		else if (no_out_append(cnt) && (*cmds)->tokens_arr[i]
			&& (!ft_strcmp((*cmds)->tokens_arr[i], ">")
				|| !ft_strcmp((*cmds)->tokens_arr[i], ">>" )))
			output_redirection(cnt, cmds, start);
		if ((*cmds)->tokens_arr[i])
			i++;
	}
	(*cnt)->infiles[v] = NULL;
}

void	extract_filenames(t_cmds **all_commands, int start, int *len)
{
	int	j;

	j = start;
	while ((*all_commands)->tokens_arr[j]
		&& ft_strcmp((*all_commands)->tokens_arr[j], "|"))
	{
		if (!ft_strcmp((*all_commands)->tokens_arr[j], ">")
			|| !ft_strcmp((*all_commands)->tokens_arr[j], ">>"))
			(*len)++;
		j++;
	}
}

void	extract_output_red(t_content **cnt, t_cmds **cmds, int *j, int *v)
{
	if (!ft_strcmp((*cmds)->tokens_arr[*j], ">"))
	{
		(*cnt)->out = 1;
		(*cnt)->append = 0;
	}
	if (!ft_strcmp((*cmds)->tokens_arr[*j], ">>"))
	{
		(*cnt)->append = 1;
		(*cnt)->out = 0;
	}
	(*j)++;
	if ((*cmds)->tokens_arr[*j])
		(*cnt)->filenames[*v] = ft_strdup((*cmds)->tokens_arr[*j]);
	(*v)++;
}

void	process_input_redir(t_content **content, t_cmds **cmds, int s)
{
	if ((*content)->in != 1 && (*cmds)->tokens_arr[s]
		&& (!ft_strcmp((*cmds)->tokens_arr[s], "<")))
		input_redir(content, cmds, s);
}
