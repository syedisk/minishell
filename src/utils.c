/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:33:46 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/05 17:34:00 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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