/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:36:57 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/16 09:56:36 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_successive_del(char *line, char *delimeters)
{
	int	successive_del;
	int	i;

	successive_del = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i])
			break ;
		if (ft_strchr(delimeters, line[i]) && !is_between_quote(line, i))
			successive_del += 1;
		else
			successive_del = 0;
		if (successive_del >= 3)
			return (display_error(line[i]));
		i++;
	}
	return (1);
}

void	skip_wspaces(char *line, int *index, int *err)
{
	int	i;

	i = *index;
	i += 1;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
	{
		*err = 2;
		i++;
	}
	*index = i;
}

int	check_d_del_errors(char *line, char *delimeters)
{
	int	i;
	int	save;
	int	err;

	i = 0;
	save = 0;
	while (line[i])
	{
		err = 0;
		if (ft_strchr(delimeters, line[i])
			&& !is_between_quote(line, i))
		{
			save = i;
			skip_wspaces(line, &i, &err);
			if (line[i] == '|' || (ft_strchr(delimeters, line[i])
					&& line[save] != line[i]))
				err = 2;
			if (err == 2 && (line[i] == '|'
					|| ft_strchr(delimeters, line[i])))
				return (display_error(line[i]));
		}
		i++;
	}
	return (1);
}

int	check_del_position(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '|' || (line[i] == '\\' && line[i + 1] == '\0'))
		return (display_error(line[i]));
	if (ft_strchr("<>", line[i]))
	{
		i += 1;
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		if (!line[i])
			return (display_error('\n'));
	}
	i = ft_strlen(line) - 1;
	while (i != 0 && (line[i] == ' ' || line[i] == '\t'))
		i--;
	if (ft_strchr("><", line[i]))
		return (display_error('\n'));
	if (ft_strchr("\\|", line[i]))
		return (display_error(line[i]));
	return (1);
}

int	display_error(char c)
{
	ft_putstr_fd(" syntax error near unexpected token `", 2);
	if (c == '\n' || c == '\0')
		ft_putstr_fd("newline", 2);
	else
		write(2, &c, 1);
	write(2, "'\n", 2);
	return (0);
}
