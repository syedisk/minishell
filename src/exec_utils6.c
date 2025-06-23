/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:23:58 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/23 20:57:53 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_external_cmd(char *path, char **argv, char **envp)
{
	if (execve(path, argv, envp) == -1)
	{
		if (errno == 2)
			ft_putstr_fd(" No such file or directory\n", 2);
		else if (errno == 13)
			ft_putstr_fd(" Permission denied\n", 2);
		else
			perror("");
		free(path);
		if (errno == 13)
			exit(126);
		else
			exit(127);
	}
	exit(0);
}

static void	cleanup_and_exit(t_command *cmd, t_exec_params *param,
		int exit_code)
{
	free_commands(cmd);
	free_env_list(*(param->env_list));
	free_env_array(param->envp);
	exit(exit_code);
}

void	execute_child(t_command *cmd, t_exec_params *param)
{
	char	*full_path;
	int		status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		cleanup_and_exit(cmd, param,
			(printf("Error: Null pointer in execute_child\n"), 127));
	handle_child_redirections(cmd);
	handle_redir_fds(cmd);
	if (is_builtin(cmd->argv[0]))
	{
		status = execute_builtin(cmd, param->env_list, param->exit_value);
		cleanup_and_exit(cmd, param, status);
	}
	if (!ft_strcmp(cmd->argv[0], "export="))
		cleanup_and_exit(cmd, param, 0);
	full_path = resolve_and_validate_path(cmd->argv[0]);
	if (!full_path)
		cleanup_and_exit(cmd, param, 127);
	execute_external_cmd(full_path, cmd->argv, param->envp);
	free(full_path);
	cleanup_and_exit(cmd, param, 127);
}

int	handle_input_redirection(t_command *cmd, t_token **curr)
{
	*curr = (*curr)->next;
	if (!*curr || (*curr)->type != WORD)
		return (ft_putstr_fd(" No such file or directory\n", 2), 1);
	cmd->redir_fd_in = open((*curr)->value, O_RDONLY);
	if (cmd->redir_fd_in == -1)
	{
		if (errno == 2)
			ft_putstr_fd(" No such file or directory\n", 2);
		else if (errno == 13)
			ft_putstr_fd(" Permission denied\n", 2);
		else
			perror("");
		return (1);
	}
	*curr = (*curr)->next;
	return (0);
}
