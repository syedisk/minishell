/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:31:20 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/15 16:49:01 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_directory(const char *path)
{
    struct stat path_stat;

    // Use stat to get information about the file
    if (stat(path, &path_stat) == -1)
        return 0; // Return 0 if stat fails
    // Check if the path is a directory
    return S_ISDIR(path_stat.st_mode);
}

void handle_infile(t_command *cmd, int fd_in)
{
	int fd;

    fd = -1;
	if (cmd->heredoc)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		exit((error_msg("heredoc_fail"), EXIT_FAILURE));
		unlink(cmd->infile);
	}
	else if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
		exit((error_msg("infile_fail"), EXIT_FAILURE));
		dup2(fd, STDIN_FILENO);
        close(fd);
	}
	else if (fd_in != 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit((perror("dup2 failed for fd_in"),EXIT_FAILURE));
		close(fd_in);
	}
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
			exit((error_msg("outfile_fail"), EXIT_FAILURE));
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (cmd->next && pipefd)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit((perror("dup2 failed for pipefd[1]"), EXIT_FAILURE));
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

void execute_child(t_command *cmd, t_env **env_list,
	char **envp, int *pipefd)
{
	char *full_path;

	if (pipefd != NULL)
		handle_infile(cmd, pipefd[0]);
	else
		handle_infile(cmd, 0);
	if (pipefd != NULL)
		handle_outfile(cmd, pipefd);
	else
		handle_outfile(cmd, NULL);
	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit((printf("Error: Null pointer in execute_child\n"), 127));
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(cmd, env_list));
	if (is_directory(cmd->argv[0]) != 0)
		exit((error_msg("is_directory"), 126));
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "export="))
		exit(0);
    else
    {
	    full_path = resolve_path(cmd->argv[0]);
	    if (!full_path)
		    exit((perror("Command not found"), 127));
	    if ((execve(full_path, cmd->argv, envp) == -1) && cmd->argv[0])
		    exit((free(full_path), error_msg("execve_fail"), 127));
		free(full_path);
	}
	    exit(EXIT_SUCCESS);
}
char *ft_strcat(char *dest, const char *src)
{
	char	*dest_start;

	dest_start = dest;
	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_start);
}