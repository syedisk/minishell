/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:06:49 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/03/20 14:15:22 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*cmd_head;
	t_command	*current_cmd;
	t_token		*curr;
	t_command	*new_cmd;

	cmd_head = NULL;
	current_cmd = NULL;
	curr = tokens;
	while (curr)
	{
		if (!cmd_head || curr->type == PIPE)
		{
			new_cmd = malloc(sizeof(t_command));
			new_cmd->argv = NULL;
			new_cmd->infile = NULL;
			new_cmd->outfile = NULL;
			new_cmd->append_out = 0;
			new_cmd->next = NULL;

			if (!cmd_head)
				cmd_head
		}
	}
}
