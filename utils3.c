/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:53:07 by martimar          #+#    #+#             */
/*   Updated: 2025/06/23 11:38:55 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*Gets the key par of a value=key pair from a string*/
char	*ft_unset_command_getkey(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	if (!key)
		return (NULL);
	return (key);
}

/*CHeck if a string is filled only by spaces*/
int	ft_check_empty_string(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

/*Check if the characters of a string are
valid for a enviroment Key*/
int	ft_isalnum_str(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (1);
	if (str[0] == '=')
		return (1);
	if (str[i] == '\'' || str[i] == '\"')
		i++;
	while (str[i] != '\0')
	{
		if (!(ft_isalpha(str[i])) && (str[i] != '\'' || str[i] != '\"')
			&& (str[i] != '_') && (str[i] != '='))
			return (1);
		i++;
	}
	return (0);
}

/*Check if the characters of a string are
valid for a enviroment Key*/
char	*ft_strjoin_custom(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

int	ft_check_env(char *str)
{
	int		i;

	i = 0;
	while (*str && str[i] != '\0')
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] != 'e')
			return (1);
		i++;
		if (str[i] != 'n')
			return (1);
		i++;
		if (str[i] != 'v')
			return (1);
		i++;
	}
	return (0);
}
