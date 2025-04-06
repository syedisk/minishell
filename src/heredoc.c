/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:11:17 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/06 13:04:48 by sbin-ham         ###   ########.fr       */
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

int create_heredoc_file(char *delimiter, int expand, char **envp)
{
	char	*line;
	char	*clean_delim;
	char	*expanded;
	int		fd;

	fd = open("/tmp/.heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	clean_delim = remove_quotes(delimiter);
	if (!clean_delim)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, clean_delim) == 0)
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
	free(clean_delim);
	close(fd);
	return (0);
}
