/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:06:49 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/03/29 16:32:30 by sbin-ham         ###   ########.fr       */
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
				cmd_head = new_cmd;
			else
				current_cmd->next = new_cmd;
			current_cmd = new_cmd;
			if (curr->type == PIPE)
				curr = curr->next;
		}

		int argc = 0;
		t_token *temp = curr;
		while (temp && temp->type != PIPE)
		{
			if (temp->type == WORD)
				argc++;
			else if (temp->type == REDIR_IN || temp->type == REDIR_OUT || temp->type == APPEND)
				temp = temp->next;
			temp = temp->next;
		}
		current_cmd->argv = malloc(sizeof(char *) * (argc + 1));
		argc = 0;
		while (curr && curr->type != PIPE)
		{
			if (curr->type == WORD)
				current_cmd->argv[argc++] = strdup(curr->value);
			else if (curr->type == REDIR_IN)
			{
				curr = curr->next;
				if (curr)
					current_cmd->infile = strdup(curr->value);
			}
			else if (curr->type ==  REDIR_OUT)
			{
				curr = curr->next;
				if (curr)
				{
					current_cmd->outfile = strdup(curr->value);
					current_cmd->append_out = 0;
				}
			}
			else if (curr->type == APPEND)
			{
				curr = curr->next;
				if (curr)
				{
					current_cmd->outfile = strdup(curr->value);
					current_cmd->append_out = 1;
				}
			}
			curr = curr->next;
		}
		current_cmd->argv[argc] = NULL;
	}
	return cmd_head;
}

void	free_commands(t_command *cmds)
{
	int	i;
	t_command *tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->argv)
		{
			i = 0;
			while (cmds->argv[i])
			{
				free(cmds->argv[i]);
				i++;
			}
			free(cmds->argv);
		}
		if (cmds->infile)
			free(cmds->infile);
		if (cmds->outfile)
			free(cmds->outfile);
		free(cmds);
		cmds = tmp;
	}
}
