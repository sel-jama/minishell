/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_pipe3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:43:57 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:08:59 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void	check_num_2(t_cmds *input, t_env **lst, int file, int fd[2])
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
			exec_cmd(input->cmd_info->cmds_arr, file, 1, lst);
		else if ((input->cmd_info->cmds_arr[0] && input) || input->next != NULL
			|| ft_strcmp(input->cmd_info->cmds_arr[0], "echo") == 0)
			fd[0] = exec_cmd(input->cmd_info->cmds_arr, file, fd[1], lst);
	}
}

void	execute_files(t_cmds *input, int t, int file, t_env **lst)
{
	if ((*lst) && input && input->cmd_info->cmds_arr[0])
	{
		if ((*lst)->cmds_num == 1 && input->cmd_info->cmds_arr[0]
			&& input->next == NULL && (ft_strcmp(input->cmd_info->cmds_arr[0],
					"export") == 0 || ft_strcmp(input->cmd_info->cmds_arr[0],
					"exit") == 0 || ft_strcmp(input->cmd_info->cmds_arr[0],
					"unset") == 0 || ft_strcmp(input->cmd_info->cmds_arr[0],
					"env") == 0 || ft_strcmp(input->cmd_info->cmds_arr[0],
					"pwd") == 0))
			exec_cmd(input->cmd_info->cmds_arr, 0, 1, lst);
		else if ((input->cmd_info->cmds_arr && input->cmd_info->cmds_arr[0]
				&& input) || ft_strcmp(input->cmd_info->cmds_arr[0],
				"echo") == 0)
			exec_cmd_redirection(input->cmd_info->cmds_arr, t, file, lst);
	}
}

int	open_files_4(char **filenames, int j, int i)
{
	int	file;

	while (filenames[j])
	{
		if (i == 0)
			file = open(filenames[j], O_CREAT | O_RDONLY | O_WRONLY | O_APPEND,
					0644);
		else
			file = open(filenames[j], O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC,
					0644);
		j++;
	}
	return (file);
}

int	open_files(t_cmds *input, t_env **lst, int i)
{
	int	j;
	int	t;
	int	file;

	j = 0;
	t = 0;
	while (input->cmd_info->infiles[j])
	{
		t = open(input->cmd_info->infiles[j], O_RDONLY);
		if (t == -1)
		{
			perror("open");
			g_exit_status = 1;
			return (0);
		}
		j++;
	}
	j = 0;
	file = open_files_4(input->cmd_info->filenames, j, i);
	if (input->cmd_info->cmds_arr[0])
		execute_files(input, t, file, lst);
	return (1);
}

void	execute_files_2(t_cmds *input, int fd[2], t_env **lst, int file)
{
	if ((*lst) && input && input->cmd_info->cmds_arr[0])
	{
		if ((*lst)->cmds_num == 1 && input->next == NULL
			&& (ft_strcmp(input->cmd_info->cmds_arr[0], "export") == 0
				|| ft_strcmp(input->cmd_info->cmds_arr[0], "exit") == 0
				|| ft_strcmp(input->cmd_info->cmds_arr[0], "unset") == 0
				|| ft_strcmp(input->cmd_info->cmds_arr[0], "env") == 0
				|| ft_strcmp(input->cmd_info->cmds_arr[0], "pwd") == 0))
			exec_cmd(input->cmd_info->cmds_arr, 0, 1, lst);
		else if ((*lst)->cmds_num == 1
			|| ft_strcmp(input->cmd_info->cmds_arr[0], "echo") == 0)
			fd[0] = exec_cmd(input->cmd_info->cmds_arr, 0, file, lst);
		else
			exec_cmd_redirection(input->cmd_info->cmds_arr, fd[0], file, lst);
	}
}
