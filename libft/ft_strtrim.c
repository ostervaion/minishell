/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:16:18 by juetxeba          #+#    #+#             */
/*   Updated: 2024/12/13 13:44:56 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	lens1;
	char			*str;

	if (!s1 || !set)
		return (NULL);
	lens1 = ft_strlen(s1);
	i = 0;
	while (i < lens1 && ft_strchr(set, s1[i]))
		i++;
	if (i == lens1)
		return (ft_strdup(""));
	j = lens1 - 1;
	while (j > i && ft_strrchr(set, s1[j]))
		j--;
	str = ft_substr(s1, i, j - i + 1);
	return (str);
}
