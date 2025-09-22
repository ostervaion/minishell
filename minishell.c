/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:27:04 by martimar          #+#    #+#             */
/*   Updated: 2025/06/24 20:05:41 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_child_work;

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	(void)argv;
	(void)argc;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_ctrl_c);
	init_mini(&mini, env);
	copy_env(&mini);
	prompt_user(&mini);
	return (0);
}

/*Initializes mini structure, it's internal
list and asign the env from the main to the 
varible env in the structure */
void	init_mini(t_mini **mini, char **env)
{
	(*mini) = malloc(sizeof(t_mini));
	if (!(*mini))
		ft_clear_all(mini, "Malloc failed in Mini\n", 1);
	(*mini)->list = malloc(sizeof(t_data *));
	if (!(*mini)->list)
		ft_clear_all(mini, "Malloc failed in list\n", 1);
	*((*mini)->list) = NULL;
	(*mini)->line = NULL;
	(*mini)->stdoutfd = dup(STDOUT_FILENO);
	(*mini)->stdinfd = dup(STDIN_FILENO);
	(*mini)->status = malloc(sizeof(uint8_t));
	*((*mini)->status) = errno;
	(*mini)->env = env;
}

void	ft_check_prereadline(t_mini **mini)
{
	if (errno != 10)
		(*(*mini)->status) = errno;
	ft_clear_list_and_exit((*mini)->list, NULL);
	ft_reset_fds(*mini);
	(*mini)->prompt = create_prompt((*mini));
	if (!(*mini)->prompt)
		ft_clear_all(mini, NULL, errno);
	(*mini)->line = readline((*mini)->prompt);
}

/*It prompts the user and gets a response that will be 
broken into pipes and fill a list of nodes with the data.
It works as an endless loop*/
void	prompt_user(t_mini **mini)
{
	while (1)
	{
		ft_check_prereadline(mini);
		if (g_child_work == 4 || g_child_work == 5)
		{
			g_child_work = 0;
			*((*mini)->status) = 130;
		}
		if (!(*mini)->line)
			return (ft_exit_command(mini, *(*mini)->list));
		if ((*mini)->line[0] != '\0' && ft_check_empty_string((*mini)->line))
		{
			add_history((*mini)->line);
			if (ft_fill_nodes((*mini)->line, (*mini)) == -1)
			{
				free((*mini)->line);
				free((*mini)->prompt);
				continue ;
			}
			ft_expand_nodes(mini);
			ft_apply_commands(mini);
		}
		free((*mini)->line);
		free((*mini)->prompt);
	}
}

/*It creates the prompt shown to the user with the 
$USER (from the copy of the environment) and the 
current path */
char	*create_prompt(t_mini *mini)
{
	char	*user;
	char	*path;
	char	*temp;
	char	*prompt;

	user = ft_get_env_var(mini->env_copy, "USER");
	if (!user)
		user = ft_strdup("");
	path = getcwd(NULL, 0);
	if (!path)
		return (free(user), printf("Error getting path"), NULL);
	temp = ft_strjoin(user, "@equipo:");
	free(user);
	if (!temp)
		return (free(path), printf("Malloc Failed"), NULL);
	prompt = ft_strjoin(temp, path);
	if (!prompt)
		return (free(temp), free(path), printf("Malloc Failed"), NULL);
	free(temp);
	free(path);
	temp = ft_strjoin(prompt, "$ ");
	if (!temp)
		return (free(prompt), printf("Malloc Failed"), NULL);
	free(prompt);
	return (temp);
}
