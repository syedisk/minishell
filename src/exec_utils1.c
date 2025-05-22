/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:16:16 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/22 15:24:22 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*try_path(char *dir, char *cmd)
{
	size_t	len;
	char	*full;

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

char	*resolve_path(char *cmd)
{
	char	**paths;
	char	*env_path;
	char	*full;
	int		i;

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
			free_split(paths);
			return (full);
		}
		i++;
	}
	free_split(paths);
	return (NULL);
}
