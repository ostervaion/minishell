/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_values3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:06:48 by martimar          #+#    #+#             */
/*   Updated: 2025/06/11 18:23:26 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Creates the path for the file with the 
getenv function and opens the fd*/
void	ft_createpath_openfile(int *fd)
{
	*fd = open("/tmp/.temporary_file", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd == -1)
		return ((void)printf("Error opening file: %s\n", strerror(errno)));
}

/*Because norminette*/
void	ft_put_number_fd(t_mini *mini, int fd, int *i)
{
	ft_putnbr_fd(*(mini->status), fd);
	(*i)++;
}

/*Because norminette*/
void	ft_init_values(char **to_expand, char **to_join)
{
	*to_expand = NULL;
	*to_join = NULL;
}

void	ft_change_command(t_data *aux, char **str)
{
	char	*auxstr;
	int		length;
	char	*com;

	length = 0;
	auxstr = *str;
	while (*auxstr && ft_isspace(*auxstr))
		auxstr++;
	com = auxstr;
	while (*auxstr && !ft_isspace(*auxstr))
		auxstr++;
	length = auxstr - com;
	while (*auxstr && ft_isspace(*auxstr))
		auxstr++;
	if (*auxstr)
	{
		ft_break_command(com, length, aux, auxstr);
		free(*str);
	}
	else
	{
		free(aux -> command);
		aux -> command = *str;
	}
}
