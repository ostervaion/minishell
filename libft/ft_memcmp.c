/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:59:40 by juetxeba          #+#    #+#             */
/*   Updated: 2024/11/28 11:26:59 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*aux;
	const unsigned char	*aux2;

	aux = (const unsigned char *) s1;
	aux2 = (const unsigned char *) s2;
	while (n > 0)
	{
		if (*aux != *aux2)
			return (*aux - *aux2);
		n--;
		aux++;
		aux2++;
	}
	return (0);
}
