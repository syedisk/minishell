/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:37:35 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/12/06 16:12:16 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_line(char **storage)
{
	char	*newline_pos;
	char	*line;
	char	*temp;

	newline_pos = ft_strchr(*storage, '\n');
	if (newline_pos)
	{
		line = ft_substr(*storage, 0, newline_pos - *storage + 1);
		temp = ft_strdup(newline_pos + 1);
		if (!line || !temp)
			return (free(line), free(temp), NULL);
	}
	else
	{
		line = ft_strdup(*storage);
		temp = NULL;
		if (!line)
			return (NULL);
	}
	free(*storage);
	*storage = temp;
	return (line);
}

static int	read_update_storage(int fd, char **storage)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*temp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	while (!ft_strchr(*storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), -1);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*storage, buffer);
		if (!temp)
			return (free(buffer), -1);
		free(*storage);
		*storage = temp;
	}
	free(buffer);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*storage[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
	{
		if (fd >= 0 && fd < MAX_FD && storage[fd])
			return (free(storage[fd]), storage[fd] = NULL, NULL);
		return (NULL);
	}
	if (!storage[fd])
	{
		storage[fd] = ft_strdup("");
		if (!storage[fd])
			return (NULL);
	}
	if (read_update_storage(fd, &storage[fd]) == -1)
		return (free(storage[fd]), storage[fd] = NULL, NULL);
	if (storage[fd] && *storage[fd])
	{
		line = extract_line(&storage[fd]);
		if (!line)
			return (free(storage[fd]), storage[fd] = NULL, NULL);
		return (line);
	}
	return (free(storage[fd]), storage[fd] = NULL, NULL);
}
