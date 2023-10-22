/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:34:01 by sel-jama          #+#    #+#             */
/*   Updated: 2022/10/20 01:52:04 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	char	*str;
	int		i;

	str = (char *)s1;
	p = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (str[i])
	{
		*(p + i) = str[i];
		i++;
	}
	*(p + i) = '\0';
	return (p);
}
