/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:26:59 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 18:27:01 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_pwd_2(t_env *envi, char *str)
{
	free(str);
	while (envi)
	{
		if (envi->content[0] && ft_strncmp(envi->content, "PWD=", 4) == 0)
		{
			ft_putendl_fd(envi->content, 1);
			g_exit_status = 0;
			return ;
		}
		envi = envi->next;
	}
}

void	ft_pwd(t_env **env)
{
	t_env	*envi;
	char	*str;

	envi = *env;
	str = getcwd(NULL, 0);
	if (str)
	{
		ft_putendl_fd(str, 1);
		free(str);
		g_exit_status = 0;
		return ;
	}
	else
		ft_pwd_2(envi, str);
	return ;
}
