
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:46:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/23 13:18:45 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_and_execute(t_command *cmd, t_exec_params *param)
{
	int pid;
	
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (*(param->fd_in) != 0)
		{
			 //printf("🔁 1. %s dup2: redirecting %d to %d\n", cmd->argv[0], *param->fd_in, STDIN_FILENO);
		   if (dup2(*param->fd_in, STDIN_FILENO) == -1)
				exit((ft_putstr_fd(" dup_2 failedasdasd\n", 2),EXIT_FAILURE));
			close(*param->fd_in);
		}
		if (param->pipefd[1] > -1) 
		{
			close(param->pipefd[0]);
			// printf("🔁 2. %s dup2: redirecting %d to %d\n", cmd->argv[0], param->pipefd[1], STDOUT_FILENO);
			if (dup2(param->pipefd[1], STDOUT_FILENO) == -1)
				exit((ft_putstr_fd(" dup_2 failedfffff\n", 2),EXIT_FAILURE));
			close(param->pipefd[1]);
			param->pipefd[0] = -1;
		}
		execute_child(cmd, param);
	}
	else if (pid == -1)
		exit((ft_putstr_fd(" fork failed\n", 2),EXIT_FAILURE));
	*(param->pid) = pid;
	return (pid);
}

void	handle_fork_and_pipe(t_command *cmd, t_exec_params *param)
{
	int	status;

	status = pipe(param->pipefd);
	if (status == -1)
	{
		perror("pipe failed");
		*(param->exit_value) = 1;
		return ;
	}
	*(param->pid) = fork_and_execute(cmd, param);
}

void	execute_pipeline_segment(t_command *cmd, t_exec_params *param)
{
	// int	forked;
	int	exec_pid;

	// forked = 0;
	exec_pid = -1;
	if (cmd->next)
	{
		handle_fork_and_pipe(cmd, param);
		// forked = 1;
	}
	else
	{	exec_pid = fork_and_execute(cmd, param);
	// if (exec_pid == -1)
	// {
	// 	perror("fork failed");
	// 	if (forked)
	// 	{
	// 		close(param->pipefd[0]);
	// 		close(param->pipefd[1]);
	// 	}
	// 	*(param->exit_value) = 1;
	// 	return ;
	// }
	*(param->pid) = exec_pid;
	}
	if (cmd->next)
		close_and_update_fds(param->fd_in, cmd, param->pipefd);
	else
		close_and_update_fds(param->fd_in, cmd, NULL);
}

int	check_and_execute_single_builtin(t_command *cmd, t_exec_params *param)
{
	int	result;

	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		return (0);
	// if (!is_builtin(cmd->argv[0]) || cmd->next || *(param->fd_in) != 0)
	// 	return (0);
	if (is_builtin(cmd->argv[0]) && !cmd->next)// && *param->fd_in == 0)
	{
		close(param->pipefd[0]);
		close(param->pipefd[1]);
		if (handle_output_redirs(cmd) != 0 || handle_input_redirs(cmd) != 0) // open/create outfile first
		{
			*param->exit_value = 1;
			return (1);
		}
		if (cmd->redir_fd_out > -1)
		{
			*param->pid = fork();
			if (*param->pid == 0)
			{
				// printf("🔁 5. dup2: redirecting %d to %d\n", fd, STDOUT_FILENO);
				result = dup2(cmd->redir_fd_out, STDOUT_FILENO);
				if (result == -1)
					return (ft_putstr_fd(" No such file or directory\n", 2), exit(1), 0);
				close(cmd->redir_fd_out);
				result = execute_builtin(cmd, param->env_list, param->exit_value);
				exit (0);
			}
		}
		else
		{
		// printf("1./n");
			result = execute_builtin(cmd, param->env_list, param->exit_value);
			*(param->exit_value) = result;
		}
		if (ft_strcmp(cmd->argv[0], "exit") == 0)
		{
			free_env_list(*(param->env_list));
			free_commands(cmd);
			free_split(param->envp);
			exit(*(param->exit_value));
		}
}
return (0);
}
void	addpid(int pid, t_exec_params *con)
{
	int		*temp;
	int			i;

	i = 0;
	temp = (int *)malloc(sizeof(int) * ((*con).numpid));
	// if (!temp)
	// 	memerr_exit(1);
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

void	execute_commands(t_command *cmd, t_env **env_list,
	char **envp, int *exit_value)
{
	t_exec_params	param;
	int				fd_in;
	int				pipefd[2];
	int				pid;
	int				final_exit;

	final_exit = -1;
	fd_in = 0;
	pipefd[0] = -1;
	pipefd[1] = -1;
	pid = -1;
	param.numpid = 0;
	param.pids = NULL;
	param.fd_in = &fd_in;
	param.pipefd = pipefd;
	param.pid = &pid;
	param.exit_value = exit_value;
	param.env_list = env_list;
	param.envp = envp;
	while (cmd)
	{
		if (!cmd->next && check_and_execute_single_builtin(cmd, &param))
			return ;
		if (!cmd->next && is_builtin(*cmd->argv) && cmd->redir_fd_out == -1)
			final_exit = *param.exit_value;
		if (cmd->argv[0][0] == '$' && cmd->argv[0][1] != '\0')
			return ;
		if (cmd->next)
			execute_pipeline_segment(cmd, &param);
		if (!cmd->next && !is_builtin(*cmd->argv)){
			param.pipefd[1] = -1;
			fork_and_execute(cmd, &param);
		}
		if (!is_builtin(*cmd->argv)){
		param.numpid++;
		addpid(*(param.pid), &param);
		//printf("numpid: %d\n", *(param.pid));
		//printf("lastpid: %d\n", param.pids[param.numpid - 1]);
		}
		cmd = cmd->next;
	}
	wait_for_child_processes(&param, exit_value);
	// for (int i = 0; i < param.numpid; i++)
	// {
	// 	free(param.pids)
	// }
	if (final_exit != -1){
		param.exit_value = &final_exit;
		*exit_value = final_exit;
	}
	free(param.pids);

}
