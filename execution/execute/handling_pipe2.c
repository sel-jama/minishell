/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_pipe2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:43:02 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/18 03:15:47 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	ft_pipe1(t_cmds **input_1, t_env **lst, int next[2])
{
	int	l;

	l = 0;
	if ((*input_1) && (*input_1)->next == NULL)
	{
		l = (*input_1)->cmd_info->redi;
		if (l < 1 || l > 6)
			exec_cmd((*input_1)->cmd_info->cmds_arr, 0, 1, lst);
		else
			check_redi(&(*input_1), next, lst);
		return (1);
	}
	return (0);
}

void	ft_pids(void)
{
	int	i;
	int	t;
	int	status;

	t = 0;
	status = 0;
	i = 3;
	while (i <= 256)
	{
		close(i);
		i++;
	}
	while (t != -1)
	{
		t = waitpid(-1, &status, 0);
		if (t == -1)
			break ;
		if (WIFSIGNALED(status) != 0)
			g_exit_status = 128 + WTERMSIG(status);
		else if (WEXITSTATUS(status) != 0)
			g_exit_status = WEXITSTATUS(status);
		else
			g_exit_status = 0;
	}
}

void	ft_execution(t_cmds *input, t_env **lst, int next[2], int prev[2])
{
	int	l;

	l = 0;
	l = input->cmd_info->redi;
	if (input->next == NULL)
	{
		if (l < 1 || l > 6)
			exec_cmd(input->cmd_info->cmds_arr, next[0], 1, lst);
		else
			next[0] = check_redi(&input, next, lst);
	}
	else
	{
		if (l < 1 || l > 6)
			next[0] = exec_cmd(input->cmd_info->cmds_arr, next[0], prev[1],
					lst);
		else
			check_redi(&input, next, lst);
	}
}

void	ft_first_cmd(t_cmds *input, t_env **env, int next[2])
{
	int	l;

	l = input->cmd_info->redi;
	if (l < 1 || l > 6)
		exec_cmd(input->cmd_info->cmds_arr, 0, next[1], env);
	else
		check_redi(&input, next, env);
}

void	ft_multiple_pipe(t_cmds **input_1, t_env **lst)
{
	int		prev[2];
	int		next[2];
	int		l;
	int		i;
	t_cmds	*input;

	input = *input_1;
	i = 0;
	l = input->cmd_info->redi;
	if (ft_pipe1(input_1, lst, next) == 0)
	{
		pipe(prev);
		pipe(next);
		while (input)
		{
			l = input->cmd_info->redi;
			if (i == 0)
				ft_first_cmd(input, lst, next);
			else
				ft_execution(input, lst, next, prev);
			input = input->next;
			i++;
		}
	}
	ft_pids();
}
