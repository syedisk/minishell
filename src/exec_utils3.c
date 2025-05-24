/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:32:14 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/24 20:08:31 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dest, const char *src)
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

int	has_input_redir(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == REDIR_IN)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	init_exec_params(t_exec_params *param, t_param_config *config)
{
	param->numpid = 0;
	param->pids = NULL;
	param->fd_in = config->fd_in;
	param->pipefd[0] = config->pipefd[0];
	param->pipefd[1] = config->pipefd[1];
	param->pid = config->pid;
	param->exit_value = config->exit_value;
	param->env_list = config->env_list;
	param->envp = config->envp;
}

int	is_invalid_dollar_cmd(t_command *cmd)
{
	return (cmd->argv[0][0] == '$' && cmd->argv[0][1] != '\0');
}

