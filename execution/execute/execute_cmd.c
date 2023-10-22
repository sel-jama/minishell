/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:10:40 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:10:44 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	fork_fun(int input, int output, int fd[2])
{
	int	i;

	i = 0;
	if (output != 1 && input != 0)
		output = fd[1];
	if (input != 0)
		dup2(input, STDIN_FILENO);
	if (output != 1)
		dup2(output, STDOUT_FILENO);
	i = 3;
	while (i <= 256)
	{
		close(i);
		i++;
	}
}

int	exec_cmd_helper(t_env **lst, int input, int output, char **interput)
{
	int	i;

	i = 1;
	if (input == 0 && output == 1)
		i = handling_b_v2(lst, interput);
	return (i);
}

int	exec_cmd(char **interput, int input, int output, t_env **lst)
{
	int		i;
	pid_t	pid;
	int		t;
	int		fd[2];

	t = 0;
	i = 0;
	pipe(fd);
	if (exec_cmd_helper(lst, input, output, interput) == 0)
		return (0);
	if (interput && interput[0])
	{
		signal_proccess();
		pid = fork();
		if (pid == 0)
		{
			fork_fun(input, output, fd);
			handling_b(lst, interput);
			if (*lst && interput)
				t = exec_cmd3(interput, (*lst)->envirenement, i);
			exec_1(interput, t);
		}
	}
	return (fd[0]);
}

void	exec_cmd_redirection(char **interput, int input, int output,
		t_env **lst)
{
	int		i;
	pid_t	pid;
	int		t;

	t = 0;
	signal_proccess();
	pid = fork();
	if (pid == 0)
	{
		if (input != 0)
			dup2(input, STDIN_FILENO);
		if (output != 1)
			dup2(output, STDOUT_FILENO);
		i = 3;
		while (i <= 256)
		{
			close(i);
			i++;
		}
		handling_b(lst, interput);
		if (*lst && interput)
			t = exec_cmd3(interput, (*lst)->envirenement, i);
		exec_1(interput, t);
	}
}
