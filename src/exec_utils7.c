/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:48:35 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 21:51:21 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec_params(t_exec_params *param, t_param_config *config)
{
	param->numpid = 0;
	param->pids = NULL;
	param->fd_in = config->fd_in;
	param->pipefd[0] = config->pipefd[0];
	param->pipefd[1] = config->pipefd[1];
	param->pid = config->pid;
	param->exit_value = config->exit_value;
	param->env_list = config->env_list;
	param->envp = config->envp;
}

int	is_invalid_dollar_cmd(t_command *cmd)
{
	return (cmd->argv[0][0] == '$' && cmd->argv[0][1] != '\0');
}

void	exec_nonbuiltin_command(t_command *cmd, t_exec_params *param)
{
	param->pipefd[1] = -1;
	fork_and_execute(cmd, param);
	param->numpid++;
	addpid(*(param->pid), param);
}

void	handle_command(t_command *cmd, t_exec_params *param,
	int *final_exit)
{
	if (!cmd->next && check_and_execute_single_builtin(cmd, param))
		return ;
	if (!cmd->next && is_builtin(*cmd->argv) && cmd->redir_fd_out == -1)
		*final_exit = *param->exit_value;
	if (is_invalid_dollar_cmd(cmd))
		return ;
	if (cmd->next)
		execute_pipeline_segment(cmd, param);
	else if (!is_builtin(*cmd->argv))
		exec_nonbuiltin_command(cmd, param);
	if (!cmd->next || !is_builtin(*cmd->argv))
	{
		param->numpid++;
		addpid(*(param->pid), param);
	}
}
