/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:32:27 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/18 01:31:30 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

void	ft_init_param(t_cmds *input, t_content *content, t_env **lst)
{
	(void)lst;
	input->cmd_info = content;
	input->cmd_info->redi = 0;
	input->cmds_num = 0;
	input->cmd_info->in = 0;
	input->cmd_info->out = 0;
	input->cmd_info->append = 0;
	input->cmd_info->filenames = NULL;
	input->cmd_info->infiles = NULL;
	input->env = *lst;
	input->remove = 0;
	input->space_found = 0;
	input->expand_doc = 1;
	input->ambig_file = 0;
	input->modify_exitstatus = 1;
	g_exit_status = 0;
}

t_cmds	*start_minishell(t_cmds *input)
{
	t_cmds	*list;
	int		i;

	tokenize_input(&input);
	i = 0;
	while (input->tokens_arr[i])
		i++;
	input->num_of_tokens = i;
	input->expand_doc = 1;
	input->rank = 0;
	quote_handling(&input);
	list = creat_cmds_list(&input);
	return (list);
}

void	read_and_check_input(t_cmds *input, t_env **sega)
{
	input->env = *sega;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_action);
	input->cmd_line = readline(PROMPT);
	if (!input->cmd_line)
		signal_action(4);
	signal_notify();
}

void	free_all(t_cmds **list)
{
	t_cmds	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->cmd_info->redi == OUTPUT_RED
			|| tmp->cmd_info->redi == APPEND_RED)
			ft_clean_up(tmp->cmd_info->filenames);
		if (tmp->cmd_info->redi == INPUT_RED)
			ft_clean_up(tmp->cmd_info->infiles);
		if (tmp->cmd_info->redi == IN_OUT
			|| tmp->cmd_info->redi == IN_APPEND)
		{
			ft_clean_up(tmp->cmd_info->filenames);
			ft_clean_up(tmp->cmd_info->infiles);
		}
		if (tmp->cmd_info->redi == HERE_DOC)
			ft_clean_up(tmp->cmd_info->eof);
		if (tmp->cmd_info->cmds_arr)
			ft_clean_up(tmp->cmd_info->cmds_arr);
		tmp = tmp->next;
	}
	ft_lstclear_cmds(list, free);
}

int	main(int ac, char **av, char **env)
{
	t_content	all_cmds;
	t_cmds		input;
	t_cmds		*list;
	t_env		lst;
	t_env		*sega;

	check_args(ac, av);
	sega = load_environement(env, &lst);
	ft_init_param(&input, &all_cmds, &sega);
	while (1)
	{
		read_and_check_input(&input, &sega);
		if (ft_empty(&input))
			continue ;
		add_history(input.cmd_line);
		if (ft_syntax(&input))
			continue ;
		list = start_minishell(&input);
		if (ft_ambig_red(&input, &list))
			continue ;
		ft_multiple_pipe(&list, &sega);
		free(input.cmd_line);
		free_all(&list);
	}
	return (g_exit_status);
}
