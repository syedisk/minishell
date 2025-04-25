/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:06:49 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/23 18:58:41 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "heredoc.h"
#include "utils.h"

t_command	*parse_tokens(t_token *tokens, t_env *env_list)
{
	t_command	*cmd_head;
	t_command	*current_cmd;
	t_token		*curr;
	t_command	*new_cmd;
	int			argc;
	t_token		*temp;
	char		*expanded;
	char		*cleaned;
	int	heredoc_id = 0;

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
			new_cmd->heredoc = 0;
			if (!cmd_head)
				cmd_head = new_cmd;
			else
				current_cmd->next = new_cmd;
			current_cmd = new_cmd;
			if (curr->type == PIPE)
				curr = curr->next;
		}
		argc = 0;
		temp = curr;
		while (temp && temp->type != PIPE)
		{
			if (temp->type == WORD)
				argc++;
			else if (temp->type == REDIR_IN || temp->type == REDIR_OUT
				|| temp->type == APPEND)
				temp = temp->next;
			temp = temp->next;
		}
		current_cmd->argv = malloc(sizeof(char *) * (argc + 1));
		argc = 0;
		while (curr && curr->type != PIPE)
		{
			if (curr->type == WORD)
			{
				expanded = expand_variables(curr->value, env_list, last_exit_status);
				cleaned = remove_quotes(expanded);
				current_cmd->argv[argc++] = cleaned;
				free(expanded);
			}
			else if (curr->type == REDIR_IN)
			{
				curr = curr->next;
				if (curr)
					current_cmd->infile = ft_strdup(curr->value);
			}
			else if (curr->type == REDIR_OUT)
			{
				curr = curr->next;
				if (curr)
				{
					current_cmd->outfile = ft_strdup(curr->value);
					current_cmd->append_out = 0;
				}
			}
			else if (curr->type == APPEND)
			{
				curr = curr->next;
				if (curr)
				{
					current_cmd->outfile = ft_strdup(curr->value);
					current_cmd->append_out = 1;
				}
			}
			else if (curr->type == HEREDOC)
			{
				curr = curr->next;
				if (curr)
				{
					int expand = 1;
					if (curr->value[0] == '\'' || curr->value[0] == '"')
						expand = 0;
					char *delim = remove_quotes(curr->value);
					char *heredoc_path = generate_heredoc_filename(heredoc_id++);
					if (!heredoc_path)
						return (NULL); // handle error
					create_heredoc_file(heredoc_path, delim, expand, env_list);
					current_cmd->heredoc = 1;
					free(delim);
					current_cmd->infile = heredoc_path;
				}
			}
			curr = curr->next;
		}
		current_cmd->argv[argc] = NULL;
	}
	return (cmd_head);
}

void	free_commands(t_command *cmds)
{
	int			i;
	t_command	*tmp;

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
