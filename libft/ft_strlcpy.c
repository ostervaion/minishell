/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:57:27 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/13 12:13:52 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	char		*aux2;
	const char	*aux;
	size_t		i;

	i = 0;
	aux2 = dest;
	aux = src;
	if (size == 0)
		return (ft_strlen((char *)src));
	while (aux[i] != '\0' && size - 1 > i)
	{
		aux2[i] = aux[i];
		i++;
	}
	aux2[i] = '\0';
	return (ft_strlen((char *)src));
}
