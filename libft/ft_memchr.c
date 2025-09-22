/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:52:55 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/12 12:38:49 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char		*aux;

	aux = (unsigned char *) str;
	c = c % 256;
	while (n != 0)
	{
		if (*aux == c)
			return ((unsigned char *)aux);
		aux++;
		n--;
	}
	return (NULL);
}
