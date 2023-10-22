/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:41:32 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/20 10:14:36 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	which_redi(char *redirection)
{
	if (!ft_strcmp(redirection, ">"))
		return (OUTPUT_RED);
	if (!ft_strcmp(redirection, "<"))
		return (INPUT_RED);
	if (!ft_strcmp(redirection, ">>"))
		return (APPEND_RED);
	if (!ft_strcmp(redirection, "<<"))
		return (HERE_DOC);
	return (0);
}

void	set_redi_value(t_content **content)
{
	if ((*content)->in == 1 && (*content)->out == 1)
		(*content)->redi = IN_OUT;
	else if ((*content)->in == 1 && (*content)->append == 1)
		(*content)->redi = IN_APPEND;
	else if ((*content)->append == 1)
		(*content)->redi = APPEND_RED;
	else if ((*content)->out == 1)
		(*content)->redi = OUTPUT_RED;
}

void	fill_redirection(t_content **cntnt, t_cmds **all_cmds, int s)
{
	int	i;

	i = s;
	while ((*all_cmds)->tokens_arr[i]
		&& ft_strcmp((*all_cmds)->tokens_arr[i], "|"))
	{
		(*cntnt)->redi = which_redi((*all_cmds)->tokens_arr[i]);
		if ((*cntnt)->redi)
		{
			if ((*cntnt)->redi == INPUT_RED)
				input_redir(cntnt, all_cmds, s);
			else if ((*cntnt)->redi == OUTPUT_RED
				|| (*cntnt)->redi == APPEND_RED)
				output_redirection(cntnt, all_cmds, s);
			else if ((*cntnt)->redi == HERE_DOC)
			{
				(*cntnt)->expand = 0;
				heredoc_red(cntnt, all_cmds, s);
			}
			break ;
		}
		i++;
	}
	set_redi_value(cntnt);
}

void	ft_clean_up(char **token_arr)
{
	int	i;

	i = 0;
	while (token_arr[i])
	{
		free(token_arr[i]);
		i++;
	}
	free(token_arr);
}

void	get_red(int *red, t_cmds **input, int n, char **line)
{
	*red = 0;
	if (n != 0 && is_redirection((*input)->tokens_arr[n - 1]))
		*red = 1;
	*line = (*input)->tokens_arr[n];
}
