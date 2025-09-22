/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:25:03 by juetxeba          #+#    #+#             */
/*   Updated: 2025/05/27 13:30:30 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	const char	*aux2;
	const char	*aux;
	size_t		i;

	if (*to_find == '\0')
		return ((char *)str);
	while (n > 0 && *str != '\0')
	{
		i = n;
		aux = str;
		aux2 = to_find;
		while (*aux2 != '\0' && *str == *aux2 && i > 0)
		{
			i--;
			aux2++;
			str++;
		}
		if (*aux2 == '\0')
			return ((char *)aux);
		str = aux + 1;
		n--;
	}
	return (NULL);
}
