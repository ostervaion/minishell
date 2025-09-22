/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martimar <martimar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:02:00 by martimar          #+#    #+#             */
/*   Updated: 2025/06/23 10:13:47 by martimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <stdint.h>

extern int	g_child_work;

typedef struct s_data
{
	char			*command;
	int				oper_amount;
	char			*arg;
	char			*oper;
	int				*next_pipefd;
	int				*prev_pipefd;
	int				*fds;
	struct s_data	*next;
}					t_data;

typedef struct s_mini
{
	struct termios	shell_termios;
	char			**env;
	char			**env_copy;
	char			*prompt;
	char			*line;
	uint8_t			*status;
	int				stdinfd;
	int				stdoutfd;
	t_data			**list;
}					t_mini;

void	init_mini(t_mini **mini, char **env);
void	copy_env(t_mini **mini);
void	prompt_user(t_mini **mini);
char	*create_prompt(t_mini *mini);
char	*ft_get_env_var(char **env_copy, char *str);
char	*return_line(char *str, int *size);
int		ft_fill_nodes(char *str, t_mini *mini);
int		ft_check_empty_string(char *str);
int		ft_new_node(t_data **list, char *str);
void	ft_clear_list_and_exit(t_data **list, char *str);
void	ft_free_and_null(void **str);
void	ft_free_split(char ***splited);
void	ft_clear_all(t_mini **mini, char *str, int status);
void	ft_close_fds(int **fds, int op_amount);
void	ft_close_parent_pipes(t_data **list);
void	ft_close_and_free_pipe(int **fd);
void	ft_reset_fds(t_mini *mini);
void	ft_status(int status, t_mini *mini);
//---------------COMMANDER------------------------
void	ft_apply_commands(t_mini **mini);
void	comms_increment(int *comms, int *comms2, char c);
int		ft_set_opers(t_mini **mini, t_data *node);
int		ft_do_builtin(t_mini **mini, t_data *node);
int		ft_do_builtin_forked(t_mini **mini, t_data *node);
char	**ft_getpath(char **env);
char	*ft_check_access(char **env, char **coms);
int		ft_get_argv_size(t_data *node);
void	ft_add_to_argv(char **argv, char *str1, char *str2, int *size);
int		ft_split_args(char *str, char **argv);
char	**ft_concatenate_args(t_data *node);
void	ft_check_pipes(t_data *node);
int		ft_check_builtin(t_data *node);
void	ft_count_comm_str(char **str, int *size, int increase);
void	ft_check_pipes(t_data *node);
void	ft_wait_for_childs(t_mini **mini);
void	ft_expand_argv_args(t_mini **mini, char **argv);
//---------------NODES---------------------------
void	ft_change_command(t_data *aux, char **str);
void	ft_break_command(char *com, int length, t_data *aux, char *auxstr);
int		ft_check_coms(int coms, int coms2);
void	ft_add_to_coms(int *coms, int *coms2, char c);
int		ft_substr_join_to_str(char	*initialstr,
			int endofstr, char **strtojoin);
void	ft_add_node_back(t_data **list, t_data *node);
void	ft_add_to_oper_with_comms(t_data *node, char *aux,
			char **str, int *check_error);
int		ft_add_new_data(t_data *node, char **str);
void	ft_check_error_oper(char **str, int *check_error);
void	ft_loop_data_insertion(t_data *node, char **str, int *check_error);
char	*ft_add_noncommed_data(t_data *node, char **str, int *check_error);
char	*ft_add_commed_data(char **str, int *coms,
			int *coms2, int *check_error);
void	ft_add_to_oper(t_data *node, char **str, int *check_error);
int		ft_oper_found(t_data *node, char **str,
			char **aux, int *check_error);
void	ft_advance_commed_str(char **str);
//---------------OPERATORS------------------------
int		ft_reset_heredoc_fd(int *fd, char *path);
int		ft_set_heredoc(t_mini **mini);
char	*ft_get_oper(char **opers);
int		ft_heredoc(char *opers, int **fds, int *actual_op);
int		ft_append(char *opers, int **fds, int *actual_op);
int		ft_input(char *opers, int **fds, int *actual_op);
int		ft_redirection(char *opers, int **fds, int *actual_op);
int		ft_heredoc_create(char	**path);
int		ft_write_heredoc(int fd, char *end);
int		ft_do_opers(t_mini **mini, char *opers, int *fds,
			int (*apply_oper_func)(char **, int **, int *, t_mini **));
int		ft_heredoc_open(int **fds, int *actual_op);
//---------------TERMINAL----------------------------
void	ft_save_shell_termios(t_mini **mini);
void	ft_restore_shell_termios(t_mini **mini);
//------------------SIGNALS-------------------------
void	signal_heredoc(int sig);
void	sigttin_handler(int sig);
void	sigpipe_handler(int sig, int pid);
void	signal_ctrl_c(int sig);
//---------------MATXINADA-DE-MANUAL-----------------
int		ft_isspace(char c);
void	ft_check_quotes(char c, int *sp_quotes, int *db_quotes);
void	ft_check_quoted_pipe(char *str, int *i, int *sp_quotes);
int		ft_check_openpipes(char *str);

void	ft_env_command(t_mini *mini, t_data *list);
int		ft_check_env(char *str);

void	ft_cd_command(t_mini *mini, t_data *list);
void	ft_cd_command_no_path(t_mini *mini);
void	ft_cd_command_with_path(t_mini *mini, t_data *list);
void	ft_cd_command_addtoenv(t_mini *mini, char *key, char *value);
void	ft_cd_command_returnoldpwd(t_mini *mini);

void	ft_export_command(t_mini *mini, t_data *list);
void	ft_export_comand_start(t_mini *mini, t_data *list);
void	ft_break_string(char *aux, int *i);
void	ft_process_string_export(t_mini *mini, char *str);
int		ft_process_value(t_mini *mini, char *str, char **value, int i);
int		ft_process_key(t_mini *mini, char *str, char **keytemp, int i);
int		ft_check_valid(char *key, char *value, t_mini *mini);
void	ft_export_addtoenv(t_mini *mini, char **key, char **value, int i);
void	ft_export_command_search(t_mini *mini, char **key, char **value);

void	ft_unset_command(t_mini *mini, t_data *list);
void	ft_unset_deletefrom_env(t_mini *mini, char *arg);
void	ft_unset_command_free_env(t_mini *mini, char ***temp_env, int i);
char	*ft_unset_command_getkey(char *str);

void	ft_pwd_command(t_mini *mini, t_data *node);

void	ft_unset_command(t_mini *mini, t_data *list);
void	ft_unset_command_arr(t_mini *mini, char *str);
void	ft_unset_deletefrom_env(t_mini *mini, char *arg);
void	ft_unset_command_free_update_env(t_mini *mini, char ***temp_env, int i);
void	ft_exit_command(t_mini **mini, t_data *list);
void	ft_unset_update_env(t_mini *mini, char *arg, char ***temp_env, int *i);

int		ft_strcmp_custom(char *s1, char *s2);
void	ft_concatenate_args_expanded(t_mini *mini, t_data *list, char ***arr);
char	*ft_strjoin_custom(char *s1, char *s2);
char	*ft_strtrim_custom(char *s1, char const *set);

void	ft_expand_nodes(t_mini **mini);
char	*ft_before_expand_values(t_mini *mini, char *str);
int		ft_join_string(t_mini *mini, char *str, char **temp, int len);
int		ft_process_string(t_mini *mini, char **str, char **temp, char c);
int		ft_expand_variable(char **env_copy, char *str, int fd, int *i);
void	ft_put_number_fd(t_mini *mini, int fd, int *i);
char	*ft_expand_values(t_mini *mini, char *str);
void	ft_createpath_openfile(int *fd);
char	*ft_close_fd_return_line(int fd);
char	*ft_check_if_env_var(char **env_copy, char *str);
void	ft_check_temp(char **temp);
void	ft_init_values(char **to_expand, char **to_join);
void	ft_process_tojoin(char **to_join, char **temp2, int check);

void	ft_echo_command(t_mini *mini, t_data *list);
void	ft_echo_print(char *s, int flag);
char	*ft_advance_in_str(char *str, int *flag);
char	*ft_return_string(char *str);
char	*ft_adv_return_string(char *str, int i, int *flag);

#endif
