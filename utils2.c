/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:25:20 by juetxeba          #+#    #+#             */
/*   Updated: 2025/06/11 17:07:57 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fds(int **fds, int op_amount)
{
	int	i;

	i = 0;
	while (i < op_amount && (*fds)[i] > 0)
		close((*fds)[i++]);
	free(*fds);
	*fds = NULL;
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

/*Returns 1 when both string are equal, 0 if not*/
int	ft_strcmp_custom(char *s1, char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == '\0' || s2[i] == '\0' || s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	ft_free_and_null(void **str)
{
	free (*str);
	*str = NULL;
}

void	ft_reset_fds(t_mini *mini)
{
	if (dup2(mini -> stdoutfd, STDIN_FILENO) == -1)
		printf("Setting the stdin failed\n");
	if (dup2(mini -> stdinfd, STDOUT_FILENO) == -1)
		printf("Setting the stdout failed\n");
}
