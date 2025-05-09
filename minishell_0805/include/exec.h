/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:34:41 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/03 16:17:47 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// exec.c
void	ft_free_split(char **arr);
char	*resolve_path(char *cmd);
int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, t_env **env_list);
void	execute_commands(t_command *cmd_head, t_env **env_list, char **envp);


// exec_utils.c
int		is_n_flag(char *str);
int     handle_echo(char **argv, t_env  *env_list);
int		handle_export(char **argv, t_env **env_list);
void	handle_newenv(t_env **env_list, char *key, char *value);
int		handle_unset(char **args, t_env **env_list);
void    set_signals(void);

#endif  