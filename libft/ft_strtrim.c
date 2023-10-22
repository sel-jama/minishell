/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:52:07 by sel-jama          #+#    #+#             */
/*   Updated: 2022/11/01 00:27:21 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		j;
	int		temp;
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end != 0 && ft_strchr(set, s1[end]))
		end--;
	if (start > end)
		return (ft_strdup(""));
	trim = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!trim)
		return (NULL);
	j = 0;
	temp = start;
	while (j <= end - temp)
		trim[j++] = s1[start++];
	trim[j] = '\0';
	return (trim);
}
