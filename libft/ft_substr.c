/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:34:12 by sel-jama          #+#    #+#             */
/*   Updated: 2022/11/01 00:15:34 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*subs;

	if (!s)
		return (NULL);
	j = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
			len = ft_strlen(s) - start;
	else if (start + len > ft_strlen(s))
			len = len - 1;
	subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (NULL);
	while (j < len && s[start + j] != '\0' && (start + j) < ft_strlen(s))
	{
		subs[j] = s[start + j];
		j++;
	}
	subs[j] = '\0';
	return (subs);
}
