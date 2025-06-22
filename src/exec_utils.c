/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:28:53 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/22 17:43:52 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_update_fds(int *fd_in, t_command *cmd, int *pipefd)
{
	if (*fd_in > 2)
	{
		close(*fd_in);
		*fd_in = -1;
	}
	if (cmd->next && pipefd)
	{
		if (pipefd[1] > 2)
			close(pipefd[1]);
		*fd_in = pipefd[0];
		pipefd[1] = -1;
	}
}

static void	waitforchild(int last_pid, int *exit_value)
{
	int	pid;
	int	status;

	status = 0;
	pid = waitpid(last_pid, &status, 0);
	if (pid == -1)
		return ;
	if (WIFEXITED(status))
		*exit_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_value = 128 + WTERMSIG(status);
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

char	*try_path(char *dir, char *cmd)
{
	size_t	len;
	char	*full;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);
	ft_strlcpy(full, dir, len);
	ft_strlcat(full, "/", len);
	ft_strlcat(full, cmd, len);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char	*resolve_path(char *cmd)
{
	char	**paths;
	char	*env_path;
	char	*full;
	int		i;

	i = 0;
	env_path = getenv("PATH");
	if (!env_path || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full = try_path(paths[i], cmd);
		if (full)
		{
			free_split(paths);
			return (full);
		}
		i++;
	}
	free_split(paths);
	return (NULL);
}
