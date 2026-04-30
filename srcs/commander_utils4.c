/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juetxeba <juetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:34:20 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/10 17:34:52 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtrim_custom(char *s1, char const *set)
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
