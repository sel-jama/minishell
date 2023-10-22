/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_pipe4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:44:20 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:07:32 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	open_files_2(t_cmds *input, int fd[2], t_env **env)
{
	int	j;
	int	file;

	j = 0;
	while (input->cmd_info->filenames[j])
	{
		if (input->cmd_info->redi == 1)
			file = open(input->cmd_info->filenames[j],
					O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0644);
		if (input->cmd_info->redi == 3)
			file = open(input->cmd_info->filenames[j],
					O_CREAT | O_RDONLY | O_WRONLY | O_APPEND, 0644);
		j++;
	}
	if (file == -1)
	{
		perror("open");
		g_exit_status = 1;
		return (0);
	}
	if (input->cmd_info->cmds_arr[0])
		execute_files_2(input, fd, env, file);
	g_exit_status = 0;
	return (1);
}

char	*herdoc_file(t_cmds *input, t_env **lst, int *t)
{
	int		d;
	char	*str;

	d = *t;
	if (input->cmd_info->eof[d] && input->cmd_info->eof[d + 1])
	{
		while (input->cmd_info->eof[d] && input->cmd_info->eof[d + 1])
		{
			str = readline(">");
			if (!str || (ft_strncmp(input->cmd_info->eof[d], str,
						ft_strlen(input->cmd_info->eof[d])) == 0
					&& ft_strlen(str) == ft_strlen(input->cmd_info->eof[d])))
				d++;
		}
	}
	str = readline(">");
	if (str && input->cmd_info->eof[0] && ft_strcmp(input->cmd_info->eof[0],
			str) && ft_strchr(str, '$') && input->cmd_info->expand == 1)
	{
		input->env = *lst;
		str = expand_doc(&input, str);
	}
	*t = d;
	return (str);
}

void	execute_herdoc(t_cmds *input, t_env **lst, int fd[2], int herdoc[2])
{
	if ((*lst) && input && input->cmd_info->cmds_arr[0])
	{
		if ((*lst)->cmds_num == 1 && (ft_strcmp(input->cmd_info->cmds_arr[0],
					"export") == 0 || ft_strcmp(input->cmd_info->cmds_arr[0],
					"exit") == 0 || ft_strcmp(input->cmd_info->cmds_arr[0],
					"unset") == 0 || ft_strcmp(input->cmd_info->cmds_arr[0],
					"env") == 0 || ft_strcmp(input->cmd_info->cmds_arr[0],
					"pwd") == 0))
			exec_cmd(input->cmd_info->cmds_arr, 0, 1, lst);
		else if (input->cmd_info->cmds_arr[0] && input->next == NULL)
			exec_cmd(input->cmd_info->cmds_arr, herdoc[0], 1, lst);
		else if ((input->cmd_info->cmds_arr[0])
			|| ft_strcmp(input->cmd_info->cmds_arr[0], "echo") == 0)
			fd[0] = exec_cmd(input->cmd_info->cmds_arr, herdoc[0], fd[1], lst);
	}
}

void	infile_redi3(t_cmds *input, t_env **lst, int fd[2])
{
	int	file;
	int	j;

	j = 0;
	j = redi_file_2(input);
	if (access(input->cmd_info->infiles[j], R_OK) == 0)
	{
		file = open(input->cmd_info->infiles[j], O_RDONLY);
		if (input->cmd_info->cmds_arr[0])
			check_num_2(input, lst, file, fd);
	}
	else
		g_exit_status = 1;
}
