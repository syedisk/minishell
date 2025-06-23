/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:46:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/06/23 12:00:59 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	init_config(t_param_config	*config, t_env **env_list,
	char **envp, int *exit_value)
{
	config->pipefd[0] = -1;
	config->pipefd[1] = -1;
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
	init_config(&config, env_list, envp, exit_value);
	config.fd_in = &fd_in;
	config.pid = &pid;
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
