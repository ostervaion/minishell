/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:42:26 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/13 14:34:54 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t		len;

	c = c % 256;
	len = ft_strlen(str);
	if (str[len] == c)
		return ((char *)str + len);
	while (len > 0)
	{
		len--;
		if (str[len] == c)
			return ((char *)str + len);
	}
	return (NULL);
}
