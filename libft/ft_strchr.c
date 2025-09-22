/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:34:06 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/13 14:06:12 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	c = c % 256;
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		else
			str++;
	}
	if (c == *str)
		return ((char *)str);
	else
		return (NULL);
}
