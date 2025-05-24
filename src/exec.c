/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:46:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/24 20:37:45 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_nonbuiltin_command(t_command *cmd, t_exec_params *param)
{
	param->pipefd[1] = -1;
	fork_and_execute(cmd, param);
	param->numpid++;
	addpid(*(param->pid), param);
}

static void	handle_command(t_command *cmd, t_exec_params *param,
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

static void	init_param_config(t_param_config *config, t_config_inputs *inputs)
{
	*(inputs->fd_in) = 0;
	*(inputs->pid) = -1;
	config->fd_in = inputs->fd_in;
	config->pid = inputs->pid;
	config->pipefd[0] = -1;
	config->pipefd[1] = -1;
	config->env_list = inputs->env_list;
	config->envp = inputs->envp;
	config->exit_value = inputs->exit_value;
}

static void	process_commands(t_command *cmd, t_exec_params *param,
	int *final_exit)
{
while (cmd)
{
	handle_command(cmd, param, final_exit);
	cmd = cmd->next;
}
}

void	execute_commands(t_command *cmd, t_env **env_list, char **envp,
	int *exit_value)
{
	t_exec_params		param;
	t_param_config		config;
	t_config_inputs		inputs;
	int					fd_in;
	int					pid;
	int					final_exit;

	inputs.fd_in = &fd_in;
	inputs.pid = &pid;
	inputs.env_list = env_list;
	inputs.envp = envp;
	inputs.exit_value = exit_value;

	init_param_config(&config, &inputs);
	init_exec_params(&param, &config);
	final_exit = -1;
	process_commands(cmd, &param, &final_exit);
	wait_for_child_processes(&param, exit_value);
	if (final_exit != -1)
		*exit_value = final_exit;
	free(param.pids);
}
