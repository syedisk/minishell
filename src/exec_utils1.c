/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:16:16 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/08 16:08:34 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *try_path(char *dir, char *cmd)
{
	size_t len;
	char *full;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);
	ft_strlcpy(full, dir, len);
	ft_strlcat(full, "/", len);
	ft_strlcat(full, cmd, len);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char *resolve_path(char *cmd)
{
	char **paths;
	char *env_path;
	char *full;
	int i;

	i = 0;
	env_path = getenv("PATH");
	if (!env_path || ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		full = try_path(paths[i], cmd);
		if (full)
		{
			ft_free_split(paths);
			return (full);
		}
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}