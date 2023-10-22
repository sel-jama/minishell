/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:41:40 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/20 10:12:39 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmds	*creat_cmds_list(t_cmds **all_commands)
{
	int		i;
	int		start;
	t_cmds	*lst;

	i = 0;
	start = 0;
	lst = NULL;
	(*all_commands)->cmd_info = NULL;
	if ((*all_commands)->ambig_file)
		return (ft_ambigous_handler(all_commands));
	count_commands(all_commands);
	while (i < (*all_commands)->cmds_num)
	{
		renetialize_content(all_commands);
		fill_redirection(&((*all_commands)->cmd_info), all_commands, start);
		fill_node(&((*all_commands)->cmd_info), all_commands, &start);
		ft_lstadd_back_cmds(&lst, ft_lstnew_cmds((*all_commands)->cmd_info));
		i++;
	}
	ft_clean_up((*all_commands)->tokens_arr);
	remove_skipping(&lst);
	return (lst);
}

t_cmds	*ft_ambigous_handler(t_cmds **all_cmds)
{
	(*all_cmds)->ambig_file = 0;
	ft_clean_up((*all_cmds)->tokens_arr);
	return (NULL);
}

void	remove_skipping(t_cmds **lst)
{
	t_cmds	*tmp;
	int		i;

	tmp = *lst;
	while (tmp)
	{
		i = 0;
		if (!tmp->cmd_info->cmds_arr)
			return ;
		while (tmp->cmd_info->cmds_arr[i] != NULL)
		{
			if (tmp->cmd_info->cmds_arr[i]
				&& ft_strchr(tmp->cmd_info->cmds_arr[i], '\\'))
				tmp->cmd_info->cmds_arr[i]
					= remove_skips(tmp->cmd_info->cmds_arr[i]);
			i++;
		}
		if (tmp->cmd_info->redi != 0)
			skips_in_redi(&tmp);
		tmp = tmp->next;
	}
}

char	*remove_one_skip(char *token, int index)
{
	int		i;
	int		a;
	int		skips;
	char	*new_token;

	i = ft_strlen(token);
	skips = 0;
	new_token = (char *)malloc(sizeof(char) * i);
	if (!new_token)
		return (token);
	i = -1;
	a = 0;
	while (token[++i])
	{
		if (!skips && i == index)
			skips = 1;
		else
		{
			new_token[a] = token[i];
			a++;
		}
	}
	new_token[a] = '\0';
	free(token);
	return (new_token);
}

int	new_len_counter(char *token)
{
	int	i;
	int	skips;
	int	len;

	i = 0;
	skips = 0;
	while (token[i])
	{
		if (token[i] == '\\')
			skips++;
		i++;
	}
	len = i - skips + 1;
	return (len);
}
