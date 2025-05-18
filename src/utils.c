/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:33:46 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/18 11:40:23 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "minishell.h"

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
	size_t	len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2
		&& ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '"' && str[len - 1] == '"')))
	{
		result = malloc(len - 1); // len - 2 for content, +1 for '\0'
		if (!result)
			return (NULL);
		ft_strlcpy(result, str + 1, len - 1); // skip first and last quote
		return (result);
	}
	return (ft_strdup(str));
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

long long	ft_atoi_long(const char *str)
{
	long long	result;
	int	sign;
	int digit;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return 0;

		digit = *str - '0';

		if (sign == 1)
		{
			if (result > (LLONG_MAX - digit) / 10)
				return 0; // Overflow for positive (LLONG_MAX is 9223372036854775807)
		}
		else
		{
			if (result > (-(LLONG_MIN + digit)) / 10)
				return 0; // Overflow for negative (LLONG_MIN is -9223372036854775808)
		}
		result = result * 10 + digit;
		str++;
	}
	result *= sign;
	return (result);
}