/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:53:56 by juetxeba          #+#    #+#             */
/*   Updated: 2025/02/07 18:53:55 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

void	ft_hex(unsigned int num, int lucase, int *i);
void	ft_putunint(unsigned int num, int *i);
void	ft_putint(int num, int *i);
void	ft_putpointer(void *ptr, int *i);
void	ft_putstring(char *str, int *i);
void	ft_putchar(char const str, int *i);
int		ft_printf(char const *str, ...);
void	ft_hexptr(unsigned long num, int *i);
#endif
