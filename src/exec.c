/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:46:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/24 22:16:27 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_exec_params(t_exec_params *param, t_param_config *config)
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

void	init_config(t_param_config *config, t_env **env_list,
	char **envp, int *exit_value)
{
	config->env_list = env_list;
	config->envp = envp;
	config->exit_value = exit_value;
}

void	execute_commands(t_command *cmd, t_env **env_list,
	char **envp, int *exit_value)
{
	t_exec_params	param;
	t_param_config	config;
	int				fd_in;
	int				pid;
	int				final_exit;

	fd_in = 0;
	pid = -1;
	final_exit = -1;
	config.fd_in = &fd_in;
	config.pid = &pid;
	config.pipefd[0] = -1;
	config.pipefd[1] = -1;
	init_config(&config, env_list, envp, exit_value);
	init_exec_params(&param, &config);
	while (cmd)
	{
		handle_command(cmd, &param, &final_exit);
		cmd = cmd->next;
	}
	wait_for_child_processes(&param, exit_value);
	if (final_exit != -1)
		*exit_value = final_exit;
	free(param.pids);
}
