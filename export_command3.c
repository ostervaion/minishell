/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:50:18 by martimar          #+#    #+#             */
/*   Updated: 2025/06/19 16:55:13 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export_command_search(t_mini *mini, char **key, char **value)
{
	int		j;

	j = 0;
	while (mini->env_copy[j] != NULL)
	{
		if (ft_strnstr(mini->env_copy[j], *key, ft_strlen(*key)))
		{
			free(mini->env_copy[j]);
			mini->env_copy[j] = ft_strjoin_custom(*key, *value);
			if (!mini->env_copy[j])
				return (free(*key), free(*value),
					(void)printf("Malloc failed in value\n"));
			return (free(*key), (void)free(*value));
		}
		j++;
	}
	j++;
	ft_export_addtoenv(mini, key, value, j);
}

void	ft_export_addtoenv(t_mini *mini, char **key, char **value, int i)
{
	int		j;
	char	**temp_env;

	j = 0;
	temp_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!temp_env)
		return (free(*key), free(*value),
			(void)printf("Malloc failed in temp_env\n"));
	temp_env[i] = NULL;
	temp_env[i - 1] = ft_strjoin_custom(*key, *value);
	if (!temp_env[i - 1])
		return (free(*key), free(*value),
			(void)printf("Malloc failed in temp_env\n"));
	while ((mini->env_copy)[j] != NULL)
	{
		temp_env[j] = ft_strdup((mini->env_copy)[j]);
		free((mini->env_copy)[j]);
		if (!temp_env[j])
			return (free(*key), free(*value),
				(void)printf("Malloc failed in temp_env\n"));
		j++;
	}
	free(mini->env_copy);
	mini->env_copy = temp_env;
	return (free(*key), (void)free(*value));
}

int	ft_check_valid(char *key, char *value, t_mini *mini)
{
	int		i;

	i = 0;
	if (key[0] == '\0')
	{
		printf("'=%s' not a valid identifier\n", value);
		ft_status(1, mini);
		return (-1);
	}
	while (key[i] != '\0')
	{
		if (!(ft_isalpha(key[i])) || !(key[i] != '_'))
		{
			printf("'%s=%s' not a valid identifier\n", key, value);
			ft_status(1, mini);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_process_key(t_mini *mini, char *str, char **keytemp, int i)
{
	char	*temp;

	temp = NULL;
	if (i > 0)
	{
		temp = ft_substr(str, 0, i);
		if (!temp)
			return (free(temp), printf("Malloc failed in temp\n"), -1);
		*keytemp = ft_before_expand_values(mini, temp);
		free(temp);
		if (!*keytemp)
		{
			*keytemp = ft_strdup("");
			if (!*keytemp)
				return (printf("Malloc failed in keytemp\n"), -1);
		}
	}
	else
	{
		*keytemp = ft_strdup("");
		if (!*keytemp)
			return (printf("Malloc failed in keytemp\n"), -1);
	}
	return (0);
}

int	ft_process_value(t_mini *mini, char *str, char **value, int i)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(str + i + 1);
	if (!temp)
		return (free(temp), printf("Malloc failed in temp\n"), -1);
	*value = ft_before_expand_values(mini, temp);
	free(temp);
	if (!*value)
		*value = ft_strdup("");
	return (0);
}
