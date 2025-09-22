/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:08:23 by juetxeba          #+#    #+#             */
/*   Updated: 2025/02/07 18:50:42 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_putchar(char c, int *i)
{
	write(1, &c, 1);
	(*i)++;
}

void	ft_putstring(char *str, int *i)
{
	if (!str)
		return (ft_putstring("(null)", i));
	while (*str != '\0')
	{
		ft_putchar(*str, i);
		str++;
	}
}

void	ft_putunint(unsigned int num, int *i)
{
	if (num == 0)
		return (ft_putchar('0', i));
	if (num < 10)
		ft_putchar(('0' + num), i);
	else
	{
		ft_putunint((num / 10), i);
		ft_putchar((num % 10) + '0', i);
	}
}

void	ft_putint(int num, int *i)
{
	char	*str;

	str = ft_itoa(num);
	ft_putstring(str, i);
	free(str);
}
