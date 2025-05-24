/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:23:58 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 22:13:40 by sbin-ham         ###   ########.fr       */
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

void	execute_child(t_command *cmd, t_exec_params *param)
{
	char	*full_path;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit((printf("Error: Null pointer in execute_child\n"), 127));
	handle_child_redirections(cmd);
	handle_redir_fds(cmd);
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(cmd, param->env_list, param->exit_value));
	if (!ft_strcmp(cmd->argv[0], "export="))
		exit(0);
	full_path = resolve_and_validate_path(cmd->argv[0]);
	if (!full_path)
		exit(127);
	execute_external_cmd(full_path, cmd->argv, param->envp);
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

