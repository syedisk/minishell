/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:05:47 by thkumara          #+#    #+#             */
/*   Updated: 2025/06/22 17:08:29 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_nonbuiltin_command(t_command *cmd, t_exec_params *param)
{
	param->pipefd[1] = -1;
	fork_and_execute(cmd, param);
	if (!cmd->next)
		close_and_update_fds(param->fd_in, cmd, param->pipefd);
	param->numpid++;
	addpid(*(param->pid), param);
}
