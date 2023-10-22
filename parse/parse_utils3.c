/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 06:41:35 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/16 18:03:55 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	alloc_error(void)
{
	ft_putendl_fd("Error: Memory allocation failed. Unable to allocate", 2);
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*remove_skips(char *token)
{
	int		i;
	int		a;
	int		len;
	char	*new_token;

	len = new_len_counter(token);
	new_token = (char *)malloc(sizeof(char) * len);
	if (!new_token)
		return (token);
	i = 0;
	a = 0;
	while (token[i])
	{
		if (token[i] == '\\')
			i++;
		else
			new_token[a++] = token[i++];
		if (!token[i])
			break ;
	}
	new_token[a] = '\0';
	free(token);
	return (new_token);
}

int	no_out_append(t_content **cnt)
{
	if ((*cnt)->out != 1 && (*cnt)->append != 1)
		return (1);
	return (0);
}

void	check_args(int ac, char **av)
{
	if (ac != 1)
	{
		write(2, av[1], ft_strlen(av[1]));
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
}
