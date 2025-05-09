/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:31:20 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/09 14:27:25 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_infile(t_command *cmd, int fd_in)
{
	int fd;

    fd = -1;
	if (cmd->heredoc)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror("heredoc failed");
			exit(EXIT_FAILURE);
		}
		unlink(cmd->infile);
	}
	else if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		{
			perror("open infile failed");
			exit(EXIT_FAILURE);
		}
	}
	else if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		return;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void handle_outfile(t_command *cmd, int *pipefd)
{
	int fd;

    fd = -1;
	if (cmd->outfile)
	{
		if (cmd->append_out)
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open outfile failed");
			exit(EXIT_FAILURE);
		}
	}
	else if (cmd->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		return;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void execute_child(t_command *cmd, t_env **env_list,
	char **envp, int *pipefd)
{
	char *full_path;

	handle_infile(cmd, 0);
	handle_outfile(cmd, pipefd);
    if (!cmd || !cmd->argv || !cmd->argv[0])
    {
        fprintf(stderr, "Error: Null pointer in execute_child\n");
        exit(127);
    }
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(cmd, env_list));
    else
    {
	    full_path = resolve_path(cmd->argv[0]);
	    if (!full_path)
		    exit((perror("Command not found"), 127));
	    if (execve(full_path, cmd->argv, envp) == -1)
	    {
		    perror("execve failed");
            free(full_path);
		    exit(EXIT_FAILURE);
	    }
    }
	    exit(EXIT_SUCCESS);
}

