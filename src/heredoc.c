/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:11:17 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/18 13:18:39 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "expander.h"
#include "utils.h"
#include "libft.h"
#include <fcntl.h>
#include <readline/readline.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

char *generate_heredoc_filename(int id)
{
	char *num;
	char *filename;

	num = ft_itoa(id);
	if (!num)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	return (filename);
}

int create_heredoc_file(const char *filepath, char *delimiter, int expand, t_env *env_list, int *exit_value)
{
	char	*line;
	char	*expanded;
	int		fd;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		// CHILD PROCESS: handle heredoc
		handle_heredoc_signals();  // Heredoc signal handler
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			exit(EXIT_FAILURE); // exit on failure in child
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			if (expand)
			{
				expanded = expand_variables(line, env_list, exit_value);
				safe_write_line(fd, expanded);
				free(expanded);
			}
			else
				safe_write_line(fd, line);
			free(line);
		}
		close(fd);
		exit(EXIT_SUCCESS); // exit from child process properly
	}
	else if (pid > 0)
	{
		// PARENT: wait for child
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status)) //This is a macro that checks if the child was terminated by a signal (like SIGINT from Ctrl+C). Returns true if the process didn’t exit normally (e.g., interrupted).
		{
			unlink(filepath); //cleanup if interrupted
			return (-1);
		}
	}
	else
	{
		perror("fork failed");
		return (-1);
	}
	return (0);
}

