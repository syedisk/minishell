/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:33:46 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/12 18:27:00 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int	safe_write_line(int fd, const char *line)
{
	char *newline;
	size_t len;

	if (!line)
		return (-1);
	len = ft_strlen(line);
	newline = malloc(len + 2); // +1 for \n, +1 for \0
	if (!newline)
		return (-1);
	ft_strlcpy(newline, line, len + 1); // copy till null
	newline[len] = '\n'; // overwrite null with newline
	newline[len + 1] = '\0'; // reterminate string
	write(fd, newline, len + 1); // write includes newline, not null
	free(newline);
	return (0);
}

char	*remove_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;
	size_t	len;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 1); // max size: original length
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				result[j++] = str[i++];
			if (str[i] == quote)
				i++; // skip closing quote
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	free_split(char **split)
{
	int	i = 0;

	if (!split)
		return;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

