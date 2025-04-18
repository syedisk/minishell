/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 11:34:41 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/18 19:15:31 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

void	ft_free_split(char **arr);
char	*resolve_path(char *cmd);
int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, t_env *env_list);
void	execute_commands(t_command *cmd_head, t_env **env_list, char **envp);

#endif