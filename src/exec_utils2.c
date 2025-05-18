/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:31:20 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/18 21:01:46 by thkumara         ###   ########.fr       */
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
		if (dup2(fd, STDIN_FILENO) == -1)
			exit((error_msg("dup2_failed"), EXIT_FAILURE));
		close(fd);
		unlink(cmd->infile);
	}
	else if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd == -1)
        {
            if (errno == ENOENT)
            	error_msg("No_file");
            else if (errno == EACCES)
            	error_msg("infile_fail");
            else
                perror("infile");
            exit(EXIT_FAILURE);
        }
		dup2(fd, STDIN_FILENO);
        close(fd);
	}
	else if (fd_in != 0)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit((error_msg("dup2_failed"),EXIT_FAILURE));
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
		{
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
		{
			fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (fd == -1)
        {
            if (errno == ENOENT)
            	error_msg("No_file");
            else if (errno == EACCES)
            	error_msg("outfile_fail");
            else
                perror("outfile");
            exit(EXIT_FAILURE);
        }
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (cmd->next && pipefd)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit((error_msg("outfile_fail"), EXIT_FAILURE));
		close(pipefd[1]);
		close(pipefd[0]);
	}
}

void execute_child(t_command *cmd, t_env **env_list,
	char **envp, int *pipefd, int *exit_value)
{
	char *full_path;

	//printf("1. execve failed for %s\n", cmd->argv[0]);
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
		exit(execute_builtin(cmd, env_list, exit_value));
	if (is_directory(cmd->argv[0]) != 0)
		exit((error_msg("is_directory"), 126));
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "export="))
		exit(0);
    else
    {
	    full_path = resolve_path(cmd->argv[0]);
	    if (!full_path)
			exit((error_msg("execve_fail"), 127));
	    if ((execve(full_path, cmd->argv, envp) == -1))
		    exit((error_msg("execve_fail"), 127));
		// execve(full_path, cmd->argv, envp);

	// If we got here, execve failed
	// perror(cmd->argv[0]);  // prints: command: error message
	free(full_path);
	// exit(127);
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