/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:11:17 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/08 20:18:29 by sbin-ham         ###   ########.fr       */
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

int create_heredoc_file(const char *filepath, char *delimiter, int expand, char **envp)
{
	char	*line;
	char	*expanded;
	int		fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
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
			expanded = expand_variables(line, envp);
			safe_write_line(fd, expanded);
			free(expanded);
		}
		else
			safe_write_line(fd, line);
		free(line);
	}
	close(fd);
	return (0);
}

