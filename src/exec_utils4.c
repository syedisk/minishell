/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42singapor>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:01:54 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/21 22:14:17 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline_segment(t_command *cmd, t_exec_params *param)
{
	int	exec_pid;

	exec_pid = -1;
	if (cmd->next)
	{
		handle_fork_and_pipe(cmd, param);
	}
	else
	{
		exec_pid = fork_and_execute(cmd, param);
		*(param->pid) = exec_pid;
	}
	if (cmd->next)
		close_and_update_fds(param->fd_in, cmd, param->pipefd);
	else
		close_and_update_fds(param->fd_in, cmd, NULL);
}

static int	redirect_and_exec_builtin(t_command *cmd, t_exec_params *param)
{
	*param->pid = fork();
	if (*param->pid == 0)
	{
		if (dup2(cmd->redir_fd_out, STDOUT_FILENO) == -1)
			return (ft_putstr_fd("No such file or directory\n", 2), exit(1), 0);
		close(cmd->redir_fd_out);
		execute_builtin(cmd, param->env_list, param->exit_value);
		exit(0);
	}
	return (1);
}

static void	handle_exit_if_needed(t_command *cmd, t_exec_params *param)
{
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		free_env_list(*(param->env_list));
		free_commands(cmd);
		free_split(param->envp);
		exit(*(param->exit_value));
	}
}

int	check_and_execute_single_builtin(t_command *cmd, t_exec_params *param)
{
	int	result;

	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (0);
	if (is_builtin(cmd->argv[0]) && !cmd->next)
	{
		if (param->pipefd[0] >= 0)
			close(param->pipefd[0]);
		if (param->pipefd[1] >= 0)
			close(param->pipefd[1]);
		if (handle_output_redirs(cmd) != 0 || handle_input_redirs(cmd) != 0)
			return (*param->exit_value = 1, 1);
		if (cmd->redir_fd_out > -1)
			return (redirect_and_exec_builtin(cmd, param));
		else
			result = execute_builtin(cmd, param->env_list, param->exit_value);
		*(param->exit_value) = result;
		handle_exit_if_needed(cmd, param);
	}
	return (0);
}

void	addpid(int pid, t_exec_params *con)
{
	int	*temp;
	int	i;

	i = 0;
	temp = (int *)malloc(sizeof(int) * ((*con).numpid));
	if ((*con).pids != NULL)
	{
		while (i < (*con).numpid - 1)
		{
			temp[i] = ((*con).pids)[i];
			i++;
		}
		free((*con).pids);
	}
	temp[i] = (pid);
	(*con).pids = temp;
}
