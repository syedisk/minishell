/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:05:47 by thkumara          #+#    #+#             */
/*   Updated: 2025/06/17 17:04:02 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_nonbuiltin_command(t_command *cmd, t_exec_params *param)
{
	param->pipefd[1] = -1;
	fork_and_execute(cmd, param);
	param->numpid++;
	addpid(*(param->pid), param);
}
