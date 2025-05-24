/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:46:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/24 22:11:43 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_fd_and_pid(int *fd_in, int *pid)
{
	*fd_in = 0;
	*pid = -1;
}

static void	init_config(t_param_config *config, t_env **env_list, char **envp)
{
	config->pipefd[0] = -1;
	config->pipefd[1] = -1;
	config->env_list = env_list;
	config->envp = envp;
}

static void	setup_config(t_param_config *config, int *fd_in, int *pid,
	int *exit_value)
{
	config->fd_in = fd_in;
	config->pid = pid;
	config->exit_value = exit_value;
}

static void	process_all_commands(t_command *cmd, t_exec_params *param, int *final_exit)
{
	while (cmd)
	{
		handle_command(cmd, param, final_exit);
		cmd = cmd->next;
	}
}

void	execute_commands(t_command *cmd, t_env **env_list,
	char **envp, int *exit_value)
{
	t_exec_params	param;
	t_param_config	config;
	int				fd_in;
	int				pid;
	int				final_exit;

	reset_fd_and_pid(&fd_in, &pid);
	init_config(&config, env_list, envp);
	setup_config(&config, &fd_in, &pid, exit_value);
	init_exec_params(&param, &config);
	final_exit = -1;
	process_all_commands(cmd, &param, &final_exit);
	wait_for_child_processes(&param, exit_value);
	if (final_exit != -1)
		*exit_value = final_exit;
	free(param.pids);
}
