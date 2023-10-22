/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:25:07 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/17 23:12:21 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_cd(char **interput, t_env **env, int j, char *ptr)
{
	char	*str;
	t_env	*enve;

	str = NULL;
	enve = *env;
	if (!interput[1] || ft_strncmp(interput[1], "~", 2) == 0)
		ft_cd_home(env, ptr, enve, j);
	else if (ft_cd_mult(interput, j) == 1)
		g_exit_status = 1;
	else if (ft_strncmp(interput[1], "-", 1) == 0)
		ft_cd_oldpwd(env, ptr, enve, j);
	else if (ft_strlen(interput[1]) == 1 && ft_strncmp(interput[1], ".",
			1) == 0)
		ft_cd_own(interput, j);
	else if (ft_strncmp(interput[1], "..", 2) == 0)
		ft_cd_back(env, j, ptr, interput);
	else if (access(interput[1], F_OK) == 0)
		ft_cd_exf(env, interput, j, ptr);
	else if (interput[1])
	{
		if (ft_cd_check(interput, j, str) == 0)
			return ;
		ft_cd_access(env, j, ptr, str);
	}
}

void	change_oldpwd_h(int test, t_env **envi, char *len)
{
	char	*ptr;
	char	*tmp;

	ptr = NULL;
	tmp = NULL;
	if (test == 0)
	{
		ptr = malloc(sizeof(char) * 8);
		ft_strlcpy(ptr, "OLDPWD=", 8);
		len = getcwd(NULL, 0);
		if (len)
		{
			tmp = ft_strjoin(ptr, len);
			ft_lstadd_back_(envi, new_list(tmp));
			free(ptr);
			free(len);
		}
		else
		{
			free(ptr);
			free(len);
		}
	}
}

char	*change_oldpwd_h2(int *test, char *content, char *ptr, char *tmp)
{
	char	*len;

	len = malloc(sizeof(char) * 8);
	ft_strlcpy(len, content, 7);
	tmp = ft_strjoin(len, "=");
	free(len);
	free(content);
	content = ft_strjoin(tmp, ptr);
	free(tmp);
	free(ptr);
	*test = 1;
	return (content);
}

void	change_oldpwd(t_env **envi)
{
	t_env	*env;
	char	*ptr;
	char	*len;
	char	*tmp;
	int		test;

	ptr = NULL;
	len = NULL;
	tmp = NULL;
	env = *envi;
	test = 0;
	while (env)
	{
		if (env->content && ft_strncmp(env->content, "OLDPWD=", 7) == 0)
		{
			ptr = getcwd(NULL, 0);
			if (ptr)
				env->content = change_oldpwd_h2(&test, env->content, ptr, tmp);
		}
		env = env->next;
	}
	change_oldpwd_h(test, envi, len);
}

void	change_pwd(t_env **envi, char *ptr)
{
	t_env	*env;
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	env = *envi;
	while (env)
	{
		if (env->content && ft_strncmp(env->content, "PWD=", 4) == 0)
		{
			str = malloc(sizeof(char) * 5);
			ft_strlcpy(str, env->content, 4);
			tmp = ft_strjoin(str, "=");
			free(env->content);
			env->content = ft_strjoin(tmp, ptr);
			free(str);
			free(tmp);
		}
		env = env->next;
	}
}
