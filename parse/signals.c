/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 04:45:24 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/17 19:09:50 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_notify(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_action);
}

void	signal_action(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (sig == SIGQUIT)
		ft_putstr_fd("Ctrl+\\ (SIGQUIT) ignored\n", 1);
	if (sig == 4)
	{
		g_exit_status = 0;
		ft_putstr_fd("exit\n", 2);
		exit (0);
	}
}

void	signal_proccess(void)
{
	signal(SIGINT, c_process);
	signal(SIGQUIT, backslash_process);
}

void	c_process(int sig)
{
	(void)sig;
	g_exit_status = 130;
	ft_putstr_fd("\n", 1);
}

void	backslash_process(int sig)
{
	(void)sig;
	g_exit_status = 131;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}
