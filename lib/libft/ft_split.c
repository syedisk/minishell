/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:03:24 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/03/13 17:33:22 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_splits(const char *s, char c)
{
	size_t	count;
	int		in_substring;

	count = 0;
	in_substring = 0;
	while (*s)
	{
		if (*s != c && in_substring == 0)
		{
			in_substring = 1;
			count++;
		}
		else if (*s == c)
		{
			in_substring = 0;
		}
		s++;
	}
	return (count);
}

static void	free_split_result(char **result, size_t i)
{
	while (i > 0)
	{
		free(result[i]);
		i--;
	}
	free(result[0]);
	free(result);
}

static char	*get_substring(char const *s, char c, size_t *len)
{
	size_t		str_len;
	const char	*next_del;

	next_del = ft_strchr(s, c);
	if (!next_del)
		str_len = ft_strlen(s);
	else
		str_len = next_del - s;
	*len = str_len;
	return (ft_substr(s, 0, str_len));
}

static char	**alloc_fill(char const *s, char c)
{
	char	**result;
	size_t	len;
	size_t	i;

	result = (char **)malloc((count_splits(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			result[i++] = get_substring(s, c, &len);
			if (!result[i - 1])
			{
				free_split_result(result, i - 1);
				return (NULL);
			}
			s += len;
		}
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	else
		return (alloc_fill(s, c));
}
