/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:59:53 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/18 13:06:00 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_makestr(int n, int digits)
{
	char	*str;
	int		check;

	check = 0;
	if (n < 0)
	{
		n = n * -1;
		check = 1;
	}
	str = (char *)malloc (digits + check + 1);
	if (!str)
		return (NULL);
	digits = digits + check;
	str[digits] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		digits--;
		str[digits] = (n % 10) + 48;
		n = n / 10;
	}
	if (check)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digits;
	int		aux;

	digits = 1;
	if (n == -2147483648)
	{
		str = ft_strdup("-2147483648");
		if (!str)
			return (NULL);
		return (str);
	}
	aux = n;
	while (aux / 10 != 0)
	{
		aux = aux / 10;
		digits++;
	}
	str = ft_makestr(n, digits);
	return (str);
}
