/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:33:46 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/22 19:29:37 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	safe_write_line(int fd, const char *line)
{
	char	*newline;
	size_t	len;

	if (!line)
		return (-1);
	len = ft_strlen(line);
	newline = malloc(len + 2);
	if (!newline)
		return (-1);
	ft_strlcpy(newline, line, len + 1);
	newline[len] = '\n';
	newline[len + 1] = '\0';
	write(fd, newline, len + 1);
	free(newline);
	return (0);
}

char	*remove_quotes(const char *str)
{
	size_t	len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2
		&& ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '"' && str[len - 1] == '"')))
	{
		result = malloc(len - 1);
		if (!result)
			return (NULL);
		ft_strlcpy(result, str + 1, len - 1);
		return (result);
	}
	return (ft_strdup(str));
}

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, s3);
	free(tmp);
	return (result);
}

int	ft_isspace(char c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f'
		|| ch == '\r')
		return (1);
	return (0);
}
