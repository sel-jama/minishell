/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 06:15:51 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/14 07:19:44 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	count_commands(t_cmds **cmd)
{
	int	i;

	i = 0;
	(*cmd)->cmds_num = 0;
	while ((*cmd)->tokens_arr[i])
	{
		if (!ft_strcmp((*cmd)->tokens_arr[i], "|"))
			(*cmd)->cmds_num += 1;
		i++;
	}
	(*cmd)->cmds_num += 1;
}

int	ft_count_files(t_cmds **cmds, int start)
{
	int		v;
	int		redi_files;
	t_cmds	*all_commands;

	v = start;
	all_commands = *cmds;
	redi_files = 0;
	while (all_commands->tokens_arr[v]
		&& ft_strcmp(all_commands->tokens_arr[v], "|"))
	{
		if (is_redirection(all_commands->tokens_arr[v]))
			redi_files += 2;
		v++;
	}
	return (redi_files);
}

void	load_command(t_content **ctnt, t_cmds **cmds, int *s, int i)
{
	int			j;
	int			len;
	t_cmds		*c;
	t_content	*cmd_info;

	j = 0;
	c = *cmds;
	cmd_info = *ctnt;
	len = i - (*s) - c->red_num + 1;
	cmd_info->cmds_arr = (char **)malloc(sizeof(char *) * len);
	if (!cmd_info->cmds_arr)
		alloc_error();
	while (*s < i && c->tokens_arr[*s])
	{
		if (is_redirection(c->tokens_arr[*s]) && !c->ambig_file)
			*s += 2;
		else
		{
			if (ft_strlen(c->tokens_arr[*s]) > 0)
				cmd_info->cmds_arr[j++] = ft_strdup(c->tokens_arr[*s]);
			*s += 1;
		}
	}
	cmd_info->cmds_arr[j] = NULL;
}

void	fill_node(t_content **content, t_cmds **cmds, int *start)
{
	int		i;
	t_cmds	*all_commands;

	i = *start;
	all_commands = *cmds;
	all_commands->red_num = 0;
	if (!all_commands->tokens_arr[i])
		return ;
	all_commands->red_num = ft_count_files(cmds, *start);
	while (all_commands->tokens_arr[i])
	{
		if (!ft_strcmp(all_commands->tokens_arr[i], "|"))
		{
			load_command(content, cmds, start, i);
			break ;
		}
		i++;
	}
	if (!all_commands->tokens_arr[i])
		load_command(content, cmds, start, i);
	if (all_commands->tokens_arr[*start])
		*start += 1;
}

void	renetialize_content(t_cmds **all_commands)
{
	(*all_commands)->cmd_info = malloc(sizeof(t_content));
	(*all_commands)->cmd_info->redi = 0;
	(*all_commands)->cmd_info->in = 0;
	(*all_commands)->cmd_info->out = 0;
	(*all_commands)->cmd_info->append = 0;
}
