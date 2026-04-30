/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:05:04 by martimar          #+#    #+#             */
/*   Updated: 2025/06/19 17:29:55 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Unset command start, if the KEY matches with the arg,
it calls another function to delte it. Otherwise, it does
nothing.*/
void	ft_unset_command(t_mini *mini, t_data *list)
{
	int		j;
	char	**arr;

	j = 1;
	arr = ft_concatenate_args(list);
	if (!arr)
		return ((void)printf("Malloc failed in arr\n"));
	if (arr[1] && arr[1][0] == '-' && ft_isalpha(arr[1][1]))
		return (ft_free_split(&arr), (void)printf("No flags allowed\n"));
	while (arr[j] != NULL)
	{
		ft_unset_command_arr(mini, arr[j]);
		j++;
	}
	ft_free_split(&arr);
	ft_status(0, mini);
}

/*It iterates a doble pointer to check each string and delete it 
form the env if the key is valid (matches with one from the enviroment*/
void	ft_unset_command_arr(t_mini *mini, char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (mini->env_copy[i] != NULL)
	{
		key = ft_unset_command_getkey(mini->env_copy[i]);
		if (!key)
			return ((void)printf("Malloc failed in Key\n"));
		if (str && ft_strcmp_custom(str, key))
			return (free(key), (void)ft_unset_deletefrom_env(mini, str));
		free(key);
		i++;
	}
}

/*The function copies the env_copy, except for the 
string that matches the KEY*/
void	ft_unset_deletefrom_env(t_mini *mini, char *arg)
{
	int		i;
	char	**temp_env;

	i = 0;
	while (mini->env_copy[i] != NULL)
		i++;
	temp_env = (char **)malloc(sizeof(char *) * i);
	if (!temp_env)
		return ((void)printf("Malloc failed in temp_env"));
	temp_env[i - 1] = NULL;
	i = 0;
	ft_unset_update_env(mini, arg, &temp_env, &i);
	ft_unset_command_free_update_env(mini, &temp_env, i);
}

/*Upsdate the env by deleting the keyy=value pair*/
void	ft_unset_update_env(t_mini *mini, char *arg, char ***temp_env, int *i)
{
	int		j;
	char	*key;

	j = 0;
	while (mini->env_copy[*i] != NULL)
	{
		key = ft_unset_command_getkey(mini->env_copy[*i]);
		if (!key)
			return ((void)printf("Malloc failed in Key\n"));
		if (!(ft_strcmp_custom(arg, key)))
		{
			(*temp_env)[j] = ft_strdup((mini->env_copy)[*i]);
			if (!(*temp_env)[j])
				return (free(key), (void)printf("Malloc failed in temp_env\n"));
			j++;
		}
		free(key);
		free((mini->env_copy)[*i]);
		(*i)++;
	}
}

/*Free the rest of env_copy and 
assigns the temp_eenv to it*/
void	ft_unset_command_free_update_env(t_mini *mini, char ***temp_env, int i)
{
	while ((mini->env_copy)[i] != NULL)
	{
		free((mini->env_copy)[i]);
		i++;
	}
	free(mini->env_copy);
	mini->env_copy = *temp_env;
}
