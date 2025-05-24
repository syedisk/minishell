/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:34:41 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 20:05:04 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_command	t_command;

typedef struct s_exec_params
{
	int						*fd_in;
	int						*pipefd;
	int						*pid;
	int						*exit_value;
	t_env					**env_list;
	char					**envp;
	int						*pids;
	int						numpid;
}							t_exec_params;

typedef struct s_param_config
{
	int						*fd_in;
	int						*pid;
	int						pipefd[2];
	t_env					**env_list;
	char					**envp;
	int						*exit_value;
}							t_param_config;

// exec_utils.c
void						close_and_update_fds(int *fd_in, t_command *cmd,
								int *pipefd);
void						wait_for_child_processes(t_exec_params *last_pid,
								int *exit_value);
char						*try_path(char *dir, char *cmd);
char						*resolve_path(char *cmd);

// exec_utils1.c
int							fork_and_execute(t_command *cmd,
								t_exec_params *param);
void						handle_fork_and_pipe(t_command *cmd,
								t_exec_params *param);

// exec_utils2.c
int							handle_output_redirection(t_command *cmd,
								t_token **curr);
int							handle_all_redirs(t_command *cmd);
int							handle_output_redirs(t_command *cmd);
int							process_input_file(t_command *cmd, t_token **curr,
								int *fd);
int							handle_input_redirs(t_command *cmd);

// exec_utils3.c
char						*ft_strcat(char *dest, const char *src);
int							has_input_redir(t_token *tokens);
int							is_directory(const char *path);
void						init_exec_params(t_exec_params *param, t_param_config *config);
int							is_invalid_dollar_cmd(t_command *cmd);

// exec_utils4.c
void						execute_pipeline_segment(t_command *cmd,
								t_exec_params *param);
int							check_and_execute_single_builtin(t_command *cmd,
								t_exec_params *param);
void						addpid(int pid, t_exec_params *con);

// exec_utils5.c
int							handle_heredoc_input(t_command *cmd);
int							handle_output_file(t_command *cmd, t_token *tokens,
								int *fd);
void						handle_child_redirections(t_command *cmd);
void						handle_redir_fds(t_command *cmd);
char						*resolve_and_validate_path(char *cmd_name);

// exec_utils6.c
void						execute_external_cmd(char *path, char **argv,
								char **envp);
void						execute_child(t_command *cmd, t_exec_params *param);
int							handle_input_redirection(t_command *cmd,
								t_token **curr);

// exec.c
void						execute_commands(t_command *cmd, t_env **env_list,
								char **envp, int *exit_value);

// exec_builtin.c
int							execute_builtin(t_command *cmd, t_env **env_list,
								int *exit_value);
int							is_builtin(char *cmd);

#endif