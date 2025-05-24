/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:16:16 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/24 18:03:37 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	setup_input_redirection(int fd_in)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit((ft_putstr_fd("dup2 failed on input\n", 2), EXIT_FAILURE));
		close(fd_in);
	}
}

static void	setup_output_redirection(int *pipefd)
{
	if (pipefd[1] > -1)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit((ft_putstr_fd("dup2 failed on output\n", 2), EXIT_FAILURE));
		close(pipefd[1]);
		pipefd[0] = -1;
	}
}

int	fork_and_execute(t_command *cmd, t_exec_params *param)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		restore_signals();
		setup_input_redirection(*(param->fd_in));
		setup_output_redirection(param->pipefd);
		execute_child(cmd, param);
	}
	else if (pid == -1)
		exit((ft_putstr_fd("fork failed\n", 2), EXIT_FAILURE));
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


