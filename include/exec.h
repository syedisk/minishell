/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:34:41 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/19 19:25:13 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// exec.c
int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, t_env **env_list, int *exit_value);
void	execute_commands(t_command *cmd_head, t_env **env_list, char **envp, int *exit_value);
void wait_for_child_processes(int last_pid, int *exit_value);
void    execute_child(t_command *cmd, t_env **env_list, char **envp, int *pipefd, int *exit_value);
void    close_and_update_fds(int *fd_in, t_command *cmd, int *pipefd);
int        fork_and_execute(t_command *cmd, t_env **env_list, char **envp, int fd_in, int *pipefd , int *exit_value);


// exec_utils.c
void    set_signals(void);
char    *try_path(char *dir, char *cmd);
char    *resolve_path(char *cmd);
void	handle_infile(t_command *cmd, int fd_in);
void	handle_outfile(t_command *cmd, int *pipefd);
char    *ft_strcat(char *dest, const char *src);
void	handle_input_redirs(t_command *cmd);
#endif  