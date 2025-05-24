/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:28:53 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/22 22:20:46 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_update_fds(int *fd_in, t_command *cmd, int *pipefd)
{
	if (*fd_in != 0)
		close(*fd_in);
	if (cmd->next && pipefd)
	{
		close(pipefd[1]);
		*fd_in = pipefd[0];
	}
}

static void waitforchild(int last_pid, int *exit_value)
{
	int	pid;
	int	status;

	pid = 0;
	while (1)
	{
        pid = waitpid(last_pid, &status, 0);
		if (pid == -1 || pid > 0)
		{
			if (WIFEXITED(status))
				*exit_value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*exit_value = 128 + WTERMSIG(status);
            break ;
		}
	}
}

void	wait_for_child_processes(t_exec_params *con, int *exit_value)
{
	int	i;
	int	j;

	i = 0;
	j = (con)->numpid;
	while (j > 0)
	{
		waitforchild((con)->pids[i], exit_value);
		i++;
		j--;
	}
}