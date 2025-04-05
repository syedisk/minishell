/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:11:17 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/05 17:56:17 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "expander.h"
#include "utils.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int create_heredoc_file(char *delimiter, int expand, char **envp)
{
	char	*line;
	int		fd;

	fd = open("/tmp/.heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcm)
	}
}