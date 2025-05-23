/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:13:56 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/23 19:37:38 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_command *cmd, t_env **env_list, int *exit_value)
{
	if (!cmd || !cmd->argv[0])
		return (0);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (handle_cd(cmd->argv));
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (handle_pwd());
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		return (handle_echo(cmd->raw_tokens, *env_list, exit_value));
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (handle_export(cmd->argv, env_list));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (handle_unset(cmd->argv, env_list));
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (handle_env(*env_list));
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (handle_exit(cmd->argv));
	return (1);
}

int	is_builtin(char	*cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset"));
}
