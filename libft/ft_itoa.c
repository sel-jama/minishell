/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:05:53 by sel-jama          #+#    #+#             */
/*   Updated: 2022/10/30 15:55:42 by sel-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_length(int n)
{
	int	count;
	int	sign;

	sign = 0;
	if (n == 0)
		count = 1;
	else
	{
		if (n < 0)
		{
			sign = 1;
			n *= -1;
		}
		count = 0;
		while (n != 0)
		{
			n = n / 10;
			count++;
		}
	}
	return (count + sign);
}

static int	check_nbr(int n, char *res)
{
	if (n == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		n = 147483648;
	}
	else if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	else if (n == 0)
	{
		res[0] = 0 + '0';
		n = 0;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	int		nb;

	len = count_length(n);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	n = check_nbr(n, res);
	res[len] = '\0';
	while (n != 0 && len)
	{
		nb = n % 10;
		res[--len] = nb + '0';
		n = n / 10;
	}
	return (res);
}
