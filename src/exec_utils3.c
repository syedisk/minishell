/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:32:14 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/22 20:33:04 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strcat(char *dest, const char *src)
{
	char	*dest_start;

	dest_start = dest;
	while (*dest != '\0')
		dest++;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_start);
}

int has_input_redir(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIR_IN)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int is_directory(const char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) == -1)
        return 0;
    return S_ISDIR(path_stat.st_mode);
}