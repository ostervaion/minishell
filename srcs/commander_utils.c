/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:18:57 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/11 16:51:15 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	comms_increment(int *comms, int *comms2, char c)
{
	if (c == '"')
		(*comms)++;
	else if (c == '\'')
		(*comms2)++;
}

void	ft_expand_env_builtin(t_mini **mini, t_data *node)
{
	char	*str;

	if ((ft_strcmp_custom(node->command, "cd")
			|| ft_strcmp_custom(node->command, "env")
			|| ft_strcmp_custom(node->command, "exit")
			|| ft_strcmp_custom(node->command, "pwd")) && node -> arg)
	{
		str = ft_before_expand_values(*mini, node -> arg);
		if (!str)
			return ;
		free(node -> arg);
		node -> arg = str;
	}
}

int	ft_do_builtin(t_mini **mini, t_data *node)
{
	if ((*((*mini)->list))->oper)
	{
		if (!ft_set_opers(mini, node))
			return (1);
	}
	ft_expand_env_builtin(mini, node);
	if (ft_strcmp_custom((node)->command, "echo"))
		return (ft_echo_command((*mini), node), 1);
	else if (ft_strcmp_custom((*((*mini)->list))->command, "cd"))
		return (ft_cd_command((*mini), node), 1);
	else if (ft_strcmp_custom((*((*mini)->list))->command, "pwd"))
		return (ft_pwd_command(*mini, node), 1);
	else if (ft_strcmp_custom((*((*mini)->list))->command, "env"))
		return (ft_env_command((*mini), node), 1);
	else if (ft_strcmp_custom((*((*mini)->list))->command, "export"))
		return (ft_export_command((*mini), node), 1);
	else if (ft_strcmp_custom((*((*mini)->list))->command, "unset"))
		return (ft_unset_command((*mini), node), 1);
	else if (ft_strcmp_custom((*((*mini)->list))->command, "exit"))
		return (ft_exit_command(mini, node), 1);
	return (0);
}

int	ft_do_builtin_forked(t_mini **mini, t_data *node)
{
	ft_expand_env_builtin(mini, node);
	if (ft_strcmp_custom((node)->command, "echo"))
		return (ft_echo_command((*mini), node), 1);
	else if (ft_strcmp_custom((node)->command, "cd"))
		return (ft_cd_command((*mini), node), 1);
	else if (ft_strcmp_custom((node)->command, "pwd"))
		return (ft_pwd_command(*mini, node), 1);
	else if (ft_strcmp_custom((node)->command, "env"))
		return (ft_env_command((*mini), node), 1);
	else if (ft_strcmp_custom((node)->command, "export"))
		return (ft_export_command((*mini), node), 1);
	else if (ft_strcmp_custom((node)->command, "unset"))
		return (ft_unset_command((*mini), node), 1);
	else if (ft_strcmp_custom((node)->command, "exit"))
		return (ft_exit_command(mini, node), 1);
	return (0);
}

char	**ft_concatenate_args(t_data *node)
{
	char	**argv;
	int		size;
	int		addedstr;
	int		i;

	size = ft_get_argv_size(node);
	argv = (char **)malloc((sizeof(char *) * (size + 1)));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(node -> command);
	if (!node -> command)
		return (free(argv), NULL);
	i = 1;
	if (i < size + 1)
		argv[i++] = NULL;
	addedstr = ft_split_args(node -> arg, argv);
	if (addedstr != size)
	{
		ft_free_split(&argv);
		argv = NULL;
	}
	return (argv);
}
