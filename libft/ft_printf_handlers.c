/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:55:06 by juetxeba          #+#    #+#             */
/*   Updated: 2025/02/07 18:55:07 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_putpointer(void *ptr, int *i)
{
	if (ptr == 0)
		ft_putstring("(nil)", i);
	else
	{
		ft_putstring("0x", i);
		ft_hexptr((unsigned long)ptr, i);
	}
}

static void	ft_luhex(unsigned int num, int lucase, int *i)
{
	if (lucase == 0)
		ft_putchar('A' - 10 + num, i);
	else if (lucase == 1)
		ft_putchar('a' - 10 + num, i);
}

void	ft_hex(unsigned int num, int lucase, int *i)
{
	if (num > 15)
		ft_hex(num / 16, lucase, i);
	num = num % 16;
	if (num >= 10 && num < 16)
		ft_luhex(num, lucase, i);
	else
		ft_putchar('0' + num, i);
}

void	ft_hexptr(unsigned long num, int *i)
{
	if (num > 15)
		ft_hexptr(num / 16, i);
	num = num % 16;
	if (num >= 10 && num < 16)
		ft_putchar('a' - 10 + num, i);
	else
		ft_putchar('0' + num, i);
}
