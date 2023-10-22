/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboucha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:26:10 by yboucha           #+#    #+#             */
/*   Updated: 2023/10/21 01:22:56 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_join_3(t_env **env, int i, char *ptr, char *interput)
{
	t_env	*envi;
	int		t;

	t = 0;
	envi = *env;
	while (envi)
	{
		while (envi->content[t] && envi->content[t] != '=')
			t++;
		t -= 1;
		if (ft_strncmp(envi->content, interput, i) == 0 && (t == i - 1))
		{
			if (ft_strrchr(envi->content, '=') == NULL)
				envi->content = ft_join_4(envi->content, ptr);
			else
				envi->content = ft_join_5(envi->content, ptr);
			return (1);
		}
		t = 0;
		envi = envi->next;
	}
	return (0);
}

int	ft_join(t_env **env, char *interput, int a)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	int		l;

	i = 0;
	l = 0;
	j = 1;
	(void)a;
	while (interput[i] && interput[i] != '+')
		i++;
	j = i;
	while (interput[j])
		j++;
	j -= 1;
	ptr = ft_strrchr(interput, '=');
	l = ft_join_3(env, i, ptr, interput);
	if (l == 0)
		return (3);
	g_exit_status = 0;
	return (0);
}

int	check_env2_2(char *interput, char *content, int i, char *ptr)
{
	int	j;

	(void)ptr;
	(void)i;
	j = 0;
	while (interput[j] && interput[j] != '=')
		j++;
	if (interput[j] && (((interput[j] != '=' && content[j] == '=')
				&& ft_strncmp(interput, content, j) == 0
				&& ft_strlen(interput) != ft_strlen(content))
			|| ft_strcmp(interput, content) == 0))
		return (1);
	return (0);
}

char	*check_env3(char *content, char *ptr, int j, char *interput)
{
	int		t;
	char	*str;
	char	*tmp;

	t = 0;
	tmp = NULL;
	str = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (interput[j] && interput[j] != '=')
	{
		str[t] = interput[j];
		t++;
		j++;
	}
	str[t] = interput[j];
	str[t + 1] = '\0';
	tmp = ft_strjoin(str, ptr);
	free(str);
	free(content);
	return (tmp);
}

char	*check_env2_h(char *content, char *ptr, int j)
{
	char	*tmp;

	if (content && content[j - 1] == '=' && !content[j])
	{
		tmp = content;
		content = ft_strjoin(tmp, ptr);
		free(tmp);
	}
	if (content)
		return (content);
	return (NULL);
}
