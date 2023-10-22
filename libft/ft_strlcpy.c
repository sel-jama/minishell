/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:10:57 by sel-jama          #+#    #+#             */
/*   Updated: 2022/10/21 04:40:34 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	j;

	j = 0;
	if (dstsize != 0)
	{
		while (src[j] && j < (dstsize - 1))
		{
			dst[j] = src[j];
			j++;
		}
		dst[j] = '\0';
	}
	return (ft_strlen(src));
}
