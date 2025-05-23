/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:06:49 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 18:59:28 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "heredoc.h"
#include "utils.h"

static t_token *dup_token_list(t_token *start, t_token *end)
{
	t_token *new_head = NULL;
	t_token *new_tok;
	t_token *last = NULL;

	while (start && start != end)
	{
		new_tok = malloc(sizeof(t_token));
		if (!new_tok)
			return (free_tokens(new_head), NULL);
		new_tok->value = ft_strdup(start->value);
		new_tok->type = start->type;
		new_tok->quote_type = start->quote_type;
		new_tok->next = NULL;
		if (last)
			last->next = new_tok;
		else
			new_head = new_tok;
		last = new_tok;
		start = start->next;
	}
	return (new_head);
}

t_command	*parse_tokens(t_token *tokens, t_env *env_list, int *exit_value)
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
			new_cmd->raw_tokens = NULL;
			if (!cmd_head)
				cmd_head = new_cmd;
			else
				current_cmd->next = new_cmd;
			current_cmd = new_cmd;
			if (curr->type == PIPE)
				curr = curr->next;
			t_token *tok_start = curr;
			t_token *tok_end = curr;
			while (tok_end && tok_end->type != PIPE)
				tok_end = tok_end->next;
			current_cmd->raw_tokens = dup_token_list(tok_start, tok_end);
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
				if (curr->quote_type == 1)
				{
					expanded = ft_strdup(curr->value);
					cleaned = ft_strdup(expanded);
				}
				else
				{
					expanded = expand_variables(curr->value, env_list, exit_value);
					cleaned = ft_strdup(expanded);
				}
				if (!expanded || !cleaned)
				{
					free(expanded);
					free(cleaned);
					free_commands(cmd_head);
					return (NULL); // handle error
				}
				if (cleaned[0] != '\0')
        			current_cmd->argv[argc++] = cleaned;
				else
					free(cleaned);
				free(expanded);
				// current_cmd->argv[argc++] = cleaned;
				// current_cmd->argv[argc] = NULL;
			}
			else if (curr->type == REDIR_IN)
			{
				// free(current_cmd->infile);
				// current_cmd->infile = ft_strdup(curr->next->value);
				// curr = curr->next;
				curr = curr->next;
				if (curr)
				{
					if (current_cmd->infile)
						free(current_cmd->infile);
					current_cmd->infile = ft_strdup(curr->value);
				}
			}
			else if (curr->type == REDIR_OUT)
			{
				// free(current_cmd->outfile);
				// current_cmd->outfile = ft_strdup(curr->next->value);
				// current_cmd->append_out = 0;
				// curr = curr->next;
				curr = curr->next;
				if (curr)
				{
					if (current_cmd->outfile)
						free(current_cmd->outfile);
					current_cmd->outfile = ft_strdup(curr->value);
					current_cmd->append_out = 0;
				}
			}
			else if (curr->type == APPEND)
			{
				// free(current_cmd->outfile);
				// current_cmd->outfile = ft_strdup(curr->next->value);
				// current_cmd->append_out = 1;
				// curr = curr->next;
				curr = curr->next;
				if (curr)
				{
					if (current_cmd->outfile)
						free(current_cmd->outfile);
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
					//printf("Processing HEREDOC with value: %s\n", curr->value);
					if (curr->value[0] == '\'' || curr->value[0] == '"')
					// {
						expand = 0;
						// i++;
					// }
					char *delim = remove_quotes(curr->value);
					if (!delim)
       	 			{
            			free_commands(cmd_head);
            			return (NULL);
       				}
					char *heredoc_path = generate_heredoc_filename(heredoc_id++);
					if (!heredoc_path)
					{
						free(delim);
						free_commands(cmd_head);
						return (NULL);
					}
					//printf ("Expand is %d\n", expand);
					create_heredoc_file(heredoc_path, delim, expand, env_list, exit_value);
					current_cmd->heredoc = 1;
					current_cmd->infile = heredoc_path;
					free(delim);
				}
			}
			curr = curr->next;
		}
		current_cmd->argv[argc] = NULL;
	}
	return (cmd_head);
}

