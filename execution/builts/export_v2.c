/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:31:36 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:13:39 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_export3(char *interput, t_env **env)
{
	t_env	*str;
	char	*str2;

	str = NULL;
	str2 = malloc(sizeof(char) * (ft_strlen(interput) + 1));
	ft_strlcpy(str2, interput, ft_strlen(interput) + 1);
	ft_lstadd_back_(&str, new_list(str2));
	free(str2);
	*env = str;
}

void	ft_export4_helper(t_env **env, t_env *ptr2, t_env *str, t_env *lst)
{
	lst = str;
	lst->next = ft_lstlast_(*env);
	lst->next->next = ptr2;
	lst->next->next->next = NULL;
}

void	ft_export4(t_env **env, t_env *ptr2, char *str2, char *ptr)
{
	t_env	*lst;
	t_env	*str;

	lst = *env;
	str = NULL;
	if (lst && lst->next)
		ptr = before_the_last_list_(lst);
	else
	{
		ft_lstadd_back_(&lst, new_list(str2));
		*env = lst;
	}
	while (lst && ptr)
	{
		if (ft_strcmp(lst->content, ptr) == 0)
		{
			str = lst;
			ft_lstadd_back_(&str, new_list(str2));
		}
		lst = lst->next;
	}
	if (!lst)
		ft_export4_helper(env, ptr2, str, lst);
	g_exit_status = 0;
}

int	check_i2(t_env **env, t_env *ptr2, char *interput, int i)
{
	char	*ptf;
	char	*str2;
	char	*tmp;

	ptf = NULL;
	str2 = NULL;
	if (i == 3)
	{
		i = 0;
		while (interput[i] && (interput[i] != '+'))
			i++;
		str2 = ft_strdup(interput + (i + 1));
		ptf = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(ptf, interput, (i + 1));
		tmp = ft_strjoin(ptf, str2);
		free(str2);
		free(ptf);
		i = 3;
	}
	if (i != 3)
		tmp = ft_strdup(interput);
	ft_export4(env, ptr2, tmp, ptf);
	return (0);
}

int	check_i(t_env **env, char *interput)
{
	t_env	*lst;
	t_env	*ptr2;
	int		i;

	i = 0;
	lst = *env;
	if (lst != NULL && check_env(env, interput) == 1)
		return (1);
	if (lst != NULL)
		ptr2 = ft_lstlast_(lst);
	i = check_interput(interput);
	if (i == 0)
		return (1);
	if (lst && i == 2)
	{
		i = ft_join(env, interput, i);
		if (i != 3)
			return (1);
	}
	check_i2(env, ptr2, interput, i);
	return (0);
}
