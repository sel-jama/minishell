/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:46:25 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/20 10:17:26 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_ambig_red(t_cmds *input, t_cmds **list)
{
	if (!validate_redirections(list))
	{
		free(input->cmd_line);
		return (1);
	}
	return (0);
}

int	ft_syntax(t_cmds *input)
{
	if (!check_syntax(input->cmd_line))
	{
		free(input->cmd_line);
		return (1);
	}
	return (0);
}

int	ft_empty(t_cmds *input)
{	
	if (input->cmd_line && (input->cmd_line[0] == '\0'
			|| !ft_strcmp(input->cmd_line, "\n")))
	{
		free(input->cmd_line);
		return (1);
	}
	return (0);
}

void	skips_in_redi(t_cmds **tmp)
{
	t_cmds	*lst;

	lst = *tmp;
	if ((lst->cmd_info->redi == OUTPUT_RED
			|| lst->cmd_info->redi == APPEND_RED))
		backslash_deleter(lst->cmd_info->filenames);
	if (lst->cmd_info->redi == INPUT_RED)
		backslash_deleter(lst->cmd_info->infiles);
	if (lst->cmd_info->redi == IN_OUT
		|| lst->cmd_info->redi == IN_APPEND)
	{
		backslash_deleter(lst->cmd_info->filenames);
		backslash_deleter(lst->cmd_info->infiles);
	}
	if (lst->cmd_info->redi == HERE_DOC)
		backslash_deleter(lst->cmd_info->eof);
}

void	backslash_deleter(char **red)
{
	int	i;

	i = 0;
	while (red[i] != NULL)
	{
		if (ft_strchr(red[i], '\\'))
			red[i] = remove_skips(red[i]);
		i++;
	}
}
