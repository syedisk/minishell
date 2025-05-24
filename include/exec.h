/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:34:41 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 19:36:45 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_exec_params {
	int			*fd_in;
	int			*pipefd;
	int			*pid;
	int			*exit_value;
	t_env		**env_list;
	char		**envp;
	int			*pids;
	int			numpid;
} 	t_exec_params;
// exec.c
int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, t_env **env_list, int *exit_value);
void	execute_commands(t_command *cmd, t_env **env_list,
	char **envp, int *exit_value);
void wait_for_child_processes(t_exec_params *last_pid, int *exit_value);
void	execute_child(t_command *cmd, t_exec_params *param);
void    close_and_update_fds(int *fd_in, t_command *cmd, int *pipefd);
int	fork_and_execute(t_command *cmd, t_exec_params *param);


// exec_utils.c
void    set_signals(void);
char    *try_path(char *dir, char *cmd);
char    *resolve_path(char *cmd);
char    *ft_strcat(char *dest, const char *src);
int	handle_input_redirs(t_command *cmd);
int	handle_output_redirs(t_command *cmd);
int has_input_redir(t_token *tokens);
int is_directory(const char *path);
#endif  