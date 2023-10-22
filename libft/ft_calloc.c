/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:43:46 by sel-jama          #+#    #+#             */
/*   Updated: 2022/11/01 03:26:35 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	i;

	if (size && count >= SIZE_MAX / size)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}
