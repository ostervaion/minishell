/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:42:03 by martimar          #+#    #+#             */
/*   Updated: 2025/06/24 13:30:51 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Start of the cd command*/
void	ft_cd_command(t_mini *mini, t_data *list)
{
	int		i;
	int		check;
	char	**arr;

	i = 0;
	check = 0;
	if (!(list->arg) || ft_strcmp_custom(list->arg, "~"))
		return (ft_cd_command_no_path(mini));
	arr = ft_concatenate_args(list);
	if (!arr)
		return ((void)printf("Malloc failed in arr\n"));
	if (arr[1] && arr[1][0] == '-' && ft_isalpha(arr[1][1]))
		return (ft_free_split(&arr), (void)printf("No flags allowed\n"));
	while (list->arg[i] != '\0')
	{
		if (ft_isspace(list->arg[i]))
			check = 1;
		else if (check)
			return (ft_status(1, mini), ft_free_split(&arr),
				(void)printf("Too many arguments\n"));
		i++;
	}
	if (ft_strcmp_custom(list->arg, "-"))
		return (ft_free_split(&arr), ft_cd_command_returnoldpwd(mini));
	return (ft_free_split(&arr), ft_cd_command_with_path(mini, list));
}

/*If cd command is execute with no path(no arguments), 
it wil use the HOME variable to go back to the HOME route,
it also updates the env*/
void	ft_cd_command_no_path(t_mini *mini)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_get_env_var(mini->env_copy, "PWD");
	if (!oldpwd)
		return (ft_status(1, mini), (void)printf("cd: PWD not set\n"));
	ft_cd_command_addtoenv(mini, "OLDPWD=", oldpwd);
	free(oldpwd);
	pwd = ft_get_env_var(mini->env_copy, "HOME");
	if (!pwd)
		return (ft_status(1, mini), (void)printf("cd: HOME not set\n"));
	ft_cd_command_addtoenv(mini, "PWD=", pwd);
	if (chdir(pwd) == -1)
		return (ft_status(1, mini), free(pwd),
			(void)printf("Failed to change directory\n"));
	free (pwd);
	return ((void)ft_status(0, mini));
}

/*Goes back to the OLDPWD in when the input 
is "cd -" and updates the env*/
void	ft_cd_command_returnoldpwd(t_mini *mini)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_get_env_var(mini->env_copy, "OLDPWD");
	if (!oldpwd)
		return ((void)printf("cd: OLDPWD not set\n"));
	printf("%s\n", oldpwd);
	if (chdir(oldpwd) == -1)
		return (ft_status(1, mini), free(oldpwd),
			(void)printf("cd: No such file or directory\n"));
	free(oldpwd);
	oldpwd = ft_get_env_var(mini->env_copy, "PWD");
	if (!oldpwd)
		return ((void)printf("cd: PWD not set\n"));
	ft_cd_command_addtoenv(mini, "OLDPWD=", oldpwd);
	free(oldpwd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ((void)printf("Malloc failed in pwd\n"));
	ft_cd_command_addtoenv(mini, "PWD=", pwd);
	free(pwd);
	return ((void)ft_status(0, mini));
}

/*It changes the working directory to the one defined
by the argument, it also updates the env*/
void	ft_cd_command_with_path(t_mini *mini, t_data *list)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = ft_get_env_var(mini->env_copy, "PWD");
	if (!oldpwd)
		return (ft_status(1, mini),
			(void)printf("cd: PWD not set\n"));
	ft_cd_command_addtoenv(mini, "OLDPWD=", oldpwd);
	free(oldpwd);
	if (chdir(list->arg) == -1)
		return (ft_status(1, mini),
			(void)printf("cd: No such file or directory\n"));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ((void)printf("Malloc failed in pwd\n"));
	ft_cd_command_addtoenv(mini, "PWD=", pwd);
	free(pwd);
	return ((void)ft_status(0, mini));
}

/*It updates the env based on the key given*/
void	ft_cd_command_addtoenv(t_mini *mini, char *key, char *value)
{
	int		i;

	i = 0;
	while (mini->env_copy[i] != NULL)
	{
		if (ft_strnstr(mini->env_copy[i], key, ft_strlen(key)))
		{
			free(mini->env_copy[i]);
			mini->env_copy[i] = ft_strjoin(key, value);
			if (!mini->env_copy[i])
				return (free(value), (void)printf("Malloc failed\n"));
		}
		i++;
	}
}
