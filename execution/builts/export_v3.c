/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_v3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:32:36 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:17:16 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_export(char **interput, t_env **env, int j)
{
	if ((*env) && (*env)->content == NULL)
		ft_export3(interput[j], env);
	else if (interput && interput[j] && interput[j][0]
			&& ft_strncmp(interput[0], "export", 6) == 0)
		check_i(env, interput[j]);
}

void	ft_export_3(char *interput)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	if (!interput)
		return ;
	while (interput[i])
	{
		ft_putchar_fd(interput[i], 1);
		if (interput[i] == '=' && t == 0)
		{
			t = 1;
			ft_putchar_fd('"', 1);
		}
		if (interput[i] && !interput[i + 1] && t > 0)
		{
			ft_putchar_fd('"', 1);
			t = 0;
		}
		i++;
	}
}

void	ft_export_2(char **interput, t_env **env)
{
	t_env	*enve;

	if (!*env)
		return ;
	if ((*env)->content && interput && interput[0] && !interput[1])
	{
		enve = *env;
		while (enve)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_export_3(enve->content);
			ft_putchar_fd('\n', 1);
			enve = enve->next;
		}
	}
	g_exit_status = 0;
}

char	*ft_join_5(char *content, char *ptr)
{
	char	*str;

	str = NULL;
	str = content;
	content = ft_strjoin(str, ptr + 1);
	free(str);
	return (content);
}

char	*ft_join_4(char *content, char *ptr)
{
	char	*str;

	str = NULL;
	str = content;
	content = ft_strjoin(str, ptr);
	free(str);
	return (content);
}
