/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:11:17 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 20:13:17 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*generate_heredoc_filename(int id)
{
	char	*num;
	char	*filename;

	num = ft_itoa(id);
	if (!num)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc_", num);
	free(num);
	return (filename);
}

static void	write_heredoc_line(t_heredoc_info *info, int fd, char *line)
{
	char	*expanded;

	if (info->expand)
	{
		expanded = expand_variables(line, info->env_list, info->exit_value);
		safe_write_line(fd, expanded);
		free(expanded);
	}
	else
		safe_write_line(fd, line);
}

static int	heredoc_child_routine(t_heredoc_info *info)
{
	char	*line;
	int		fd;

	handle_heredoc_signals();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	fd = open(info->filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, info->delimiter) == 0)
			break ;
		write_heredoc_line(info, fd, line);
		free(line);
	}
	free(line);
	close(fd);
	exit(EXIT_SUCCESS);
}

int	create_heredoc_file(t_heredoc_info *info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		heredoc_child_routine(info);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			unlink(info->filepath);
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
