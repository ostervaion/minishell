/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:22:42 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/12 12:30:18 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*str;
	unsigned char	*str2;

	if (!dest && !src)
		return (NULL);
	str = (unsigned char *)dest;
	str2 = (unsigned char *)src;
	while (n-- > 0)
	{
		*str = *str2;
		str++;
		str2++;
	}
	return (dest);
}
