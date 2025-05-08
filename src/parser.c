/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:06:49 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/06 16:44:53 by thkumara         ###   ########.fr       */
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
			if (!new_cmd)
			{
				free_commands(cmd_head); // Free previously allocated commands
				return (NULL); // handle error
			}
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
		if (!current_cmd->argv)
		{
			free_commands(cmd_head);
			return (NULL);
		}
		argc = 0;
		while (curr && curr->type != PIPE)
		{
			if (curr->type == WORD)
			{
				expanded = expand_variables(curr->value, env_list, last_exit_status);
				if (!expanded)
				{
					free_commands(cmd_head);
					return (NULL); // handle error
				}
				cleaned = remove_quotes(expanded);
				free(expanded);
				if (!cleaned)
				{
					free_commands(cmd_head);
					return (NULL); // handle error
				}
				current_cmd->argv[argc++] = cleaned;
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
					printf("Processing HEREDOC with value: %s\n", curr->value);
					if (curr->value[0] == '\'' || curr->value[0] == '"')
					// {
						expand = 0;
						// i++;
					// }
					char *delim = remove_quotes(curr->value);
					char *heredoc_path = generate_heredoc_filename(heredoc_id++);
					if (!heredoc_path)
					{
						free(delim);
						free_commands(cmd_head);
						return (NULL);
					}
					printf ("Expand is %d\n", expand);
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

