/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:53:02 by juetxeba          #+#    #+#             */
/*   Updated: 2025/02/07 18:39:43 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_put_variable(char const **str, int *i, va_list arg)
{
	if (**str == 'c')
		ft_putchar(va_arg(arg, int), i);
	else if (**str == 's')
		ft_putstring(va_arg(arg, char *), i);
	else if (**str == 'p')
		ft_putpointer(va_arg(arg, void *), i);
	else if (**str == 'd')
		ft_putint(va_arg(arg, int), i);
	else if (**str == 'i')
		ft_putint(va_arg(arg, int), i);
	else if (**str == 'u')
		ft_putunint(va_arg(arg, unsigned int), i);
	else if (**str == 'x')
		ft_hex(va_arg(arg, long long), 1, i);
	else if (**str == 'X')
		ft_hex(va_arg(arg, long long), 0, i);
	else if (**str == '%')
		ft_putchar(**str, i);
}

int	ft_printf(char const *str, ...)
{
	va_list	arg;
	int		i;

	va_start(arg, str);
	i = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			ft_put_variable(&str, &i, arg);
		}
		else
			ft_putchar(*str, &i);
		str++;
	}
	va_end(arg);
	return (i);
}
