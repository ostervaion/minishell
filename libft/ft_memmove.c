/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:39:37 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/12 12:31:12 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*str_dest;
	const unsigned char	*str_src;

	if (!dest && !src)
		return (NULL);
	str_dest = (unsigned char *)dest;
	str_src = (const unsigned char *)src;
	while (n-- > 0)
	{
		if (str_src > str_dest)
			*str_dest++ = *str_src++;
		else
			*(str_dest + n) = *(str_src + n);
	}
	return (dest);
}
