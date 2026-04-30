/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:53:09 by juetxeba          #+#    #+#             */
/*   Updated: 2026/04/30 13:42:12 by juetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigpipe_handler(int sig, int pid)
{
	(void)sig;
	printf("SIGPIPE,id= %i", pid);
}

void	sigttin_handler(int sig)
{

	(void)sig;
	printf("SIGTTIN\n");
}

void	sigint_handler(int signo)
{
	(void)signo;
	printf("SIGINT\n");
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*falta poner child_work a cero cuando todos 
los hijs terminan para que funcione normal. 
No funciona coon el heredoc, 
tratarlo como modo "interactivo"*/
void	signal_ctrl_c(int sig)
{
	(void)sig;
	if (g_child_work == 3)
	{
		close(STDIN_FILENO);
		g_child_work = 2;
	}
	else if (g_child_work == 0 || g_child_work == 4
		|| g_child_work == 2 || g_child_work == 5)
	{
		if (g_child_work == 0 || g_child_work == 4)
			ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		if (g_child_work == 0)
			g_child_work = 4;
		else if (g_child_work == 2)
			g_child_work = 5;
	}
}
