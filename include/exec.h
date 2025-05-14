/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:34:41 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/14 18:31:07 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// exec.c
int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, t_env **env_list);
void	execute_commands(t_command *cmd_head, t_env **env_list, char **envp);
void    wait_for_child_processes(int last_pid);
void    execute_child(t_command *cmd, t_env **env_list, char **envp, int *pipefd);
void    close_and_update_fds(int *fd_in, t_command *cmd, int *pipefd);
int        fork_and_execute(t_command *cmd, t_env **env_list, char **envp, int fd_in, int *pipefd);


// exec_utils.c
void    set_signals(void);
char    *try_path(char *dir, char *cmd);
void	ft_free_split(char **arr);
char    *resolve_path(char *cmd);
void	handle_infile(t_command *cmd, int fd_in);
void	handle_outfile(t_command *cmd, int *pipefd);
char    *ft_strcat(char *dest, const char *src);

#endif  