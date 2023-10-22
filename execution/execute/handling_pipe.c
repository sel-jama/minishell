/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:09:25 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:09:29 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	redi_file_2(t_cmds *input)
{
	int	j;
	int	t;

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
	j -= 1;
	return (j);
}

int	herdoc_exp(t_cmds *input, int t, int herdoc[2], char *str)
{
	if (!str || (ft_strncmp(input->cmd_info->eof[t], str,
				ft_strlen(input->cmd_info->eof[t])) == 0
			&& ft_strlen(str) == ft_strlen(input->cmd_info->eof[t])))
	{
		free(str);
		return (0);
	}
	if (str)
	{
		write(herdoc[1], str, ft_strlen(str));
		free(str);
	}
	write(herdoc[1], "\n", 1);
	return (1);
}

void	f_checck_redi(t_cmds *input, t_env **lst, int fd[2])
{
	if (input->cmd_info->redi == 2)
		infile_redi3(input, lst, fd);
	else if (input->cmd_info->redi == 5)
		open_files(input, lst, 1);
	else if (input->cmd_info->redi == 1 || input->cmd_info->redi == 3)
		open_files_2(input, fd, lst);
}

int	check_redi(t_cmds **input_2, int fd[2], t_env **lst)
{
	t_cmds	*input;
	char	*str;
	int		t;
	int		herdoc[2];

	str = NULL;
	input = *input_2;
	f_checck_redi(input, lst, fd);
	if (input->cmd_info->redi == 4)
	{
		t = 0;
		pipe(herdoc);
		while (1)
		{
			str = herdoc_file(input, lst, &t);
			if (herdoc_exp(input, t, herdoc, str) == 0)
				break ;
		}
		execute_herdoc(input, lst, fd, herdoc);
	}
	else if (input->cmd_info->redi == 6)
		open_files(input, lst, 0);
	return (fd[0]);
}
