/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:17:05 by martimar          #+#    #+#             */
/*   Updated: 2025/06/24 13:59:10 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It makes a copy of the env stored in the 
"mini" structure and store it in env_copy"*/
void	copy_env(t_mini **mini)
{
	int		i;

	i = 0;
	while (((*mini)->env)[i] != NULL)
		i++;
	(*mini)->env_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!((*mini)->env_copy))
		ft_clear_all(mini, "Malloc failed", 1);
	(*mini)->env_copy[i] = NULL;
	i = 0;
	while (((*mini)->env)[i] != NULL)
	{
		((*mini)->env_copy)[i] = ft_strdup(((*mini)->env)[i]);
		if (!(((*mini)->env_copy)[i]))
			ft_clear_all(mini, "Malloc failed", 1);
		i++;
	}
}

/*env built-in command. Prints the 
enviroment variables*/
void	ft_env_command(t_mini *mini, t_data *list)
{
	int		i;
	char	*str;

	i = 0;
	if (list->arg)
	{
		str = ft_before_expand_values(mini, list->arg);
		if (!str)
			return ((void)printf("Malloc failed in env command\n"));
		if (ft_check_env(str))
			return (free(str), (void)printf("No arguments/flags allowed\n"));
		free(str);
	}
	while (mini->env_copy[i] != NULL)
	{
		printf("%s\n", mini->env_copy[i]);
		i++;
	}
	ft_status(0, mini);
}

/*It searches for the enviroment variable given and resturns 
its value if it exits, otherwise it return NULL*/
char	*ft_get_env_var(char **env_copy, char *str)
{
	int		i;
	char	*env_var;
	char	*key;

	i = 0;
	while (env_copy[i] != NULL)
	{
		key = ft_unset_command_getkey(env_copy[i]);
		if (!key)
			return (printf("Malloc failed in Key\n"), NULL);
		if (ft_strcmp_custom(str, key))
		{
			env_var = ft_strdup(env_copy[i] + ft_strlen(str) + 1);
			if (!env_var)
				return (free(key), printf("Malloc failed"), NULL);
			return (free(key), env_var);
		}
		free(key);
		i++;
	}
	return (NULL);
}
