/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:06:49 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 16:37:03 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "heredoc.h"
#include "utils.h"

t_command	*start_new_command(t_command **head, t_command *prev, t_token **curr)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	init_command(new_cmd);
	if (!(*head))
		*head = new_cmd;
	else
		prev->next = new_cmd;
	if ((*curr)->type == PIPE)
		*curr = (*curr)->next;
	return (new_cmd);
}

void	init_command(t_command *cmd)
{
	cmd->argv = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append_out = 0;
	cmd->next = NULL;
	cmd->heredoc = 0;
	cmd->raw_tokens = NULL;
}

int	set_raw_tokens(t_command *cmd, t_token *start)
{
	t_token	*end;

	end = start;
	while (end && end->type != PIPE)
		end = end->next;
	cmd->raw_tokens = dup_token_list(start, end);
	return (cmd->raw_tokens != NULL);
}

int	setup_args_and_redirects(t_command *cmd, t_token **curr, t_parse_ctx *ctx)
{
	int		argc;
	char 	*arg;

	argc = count_args(*curr);
	cmd->argv = malloc(sizeof(char *) * (argc + 1));
	if (!cmd->argv)
		return (0);
	argc = 0;
	while (*curr && (*curr)->type != PIPE)
	{
		if ((*curr)->type == WORD)
		{
			if (!expand_word((*curr), ctx->env_list, ctx->exit_value, &arg))
			{
				while(argc-- > 0)
					free(cmd->argv[argc]);
				free(cmd->argv);
				return (0);
			}
			if (arg != NULL)
				cmd->argv[argc++] = arg;
		}
		else
		{
			if (!handle_redirection(cmd, curr, ctx))
			{
				while (argc-- > 0)
					free(cmd->argv[argc]);
				free(cmd->argv);
				return (0);
			}
			continue;
		}
		*curr = (*curr)->next;
	}
	cmd->argv[argc] = NULL;
	return (1);
}

int	handle_redirection(t_command *cmd, t_token **curr, t_parse_ctx *ctx)
{
	if ((*curr)->type == REDIR_IN || (*curr)->type == REDIR_OUT || (*curr)->type == APPEND)
		return (handle_file_redir(cmd, curr));
	if ((*curr)->type == HEREDOC)
		return (handle_heredoc(cmd, curr, ctx));
	return (1);
}

int	handle_file_redir(t_command *cmd, t_token **curr)
{
	t_token	*next;

	next = (*curr)->next;
	if (!next)
		return (0);

	if ((*curr)->type == REDIR_IN)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(next->value);
	}
	else if ((*curr)->type == REDIR_OUT || (*curr)->type == APPEND)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(next->value);
		cmd->append_out = ((*curr)->type == APPEND);
	}
	*curr = next->next;
	return (1);
}

int	handle_heredoc(t_command *cmd, t_token **curr, t_parse_ctx *ctx)
{
	char	*delim;
	char	*heredoc_path;
	int		expand;
	t_token	*next;
	
	next = (*curr)->next;
	if (!next)
		return (0);
	// *curr = (*curr)->next;
	// if (!(*curr))
	// 	return (1);
	expand = 1;
	if ((*curr)->value[0] == '\'' || (*curr)->value[0] == '"')
		expand = 0;
	delim = remove_quotes((*curr)->value);
	if (!delim)
		return (0);
	heredoc_path = generate_heredoc_filename((*ctx->heredoc_id)++);
	if (!heredoc_path)
	{
		free(delim);
		return (0);
	}
	create_heredoc_file(heredoc_path, delim, expand, ctx->env_list, ctx->exit_value);
	cmd->heredoc = 1;
	cmd->infile = heredoc_path;
	free(delim);
	*curr = next->next;
	return (1);
}



int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		else if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == APPEND)
			token = token->next;
		token = token->next;
	}
	return (count);
}

int	expand_word(t_token *token, t_env *env_list, int *exit_value, char **out)
{
	char	*expanded;
	char	*cleaned;

	if (token->quote_type == 1)
		expanded = ft_strdup(token->value);
	else
		expanded = expand_variables(token->value, env_list, exit_value);
	if (!expanded)
		return (0);
	cleaned = ft_strdup(expanded);
	free(expanded);
	if (!cleaned)
		return (0);
	if (cleaned[0] == '\0')
	{
		free(cleaned);
		*out = NULL;
		return (1);
	}
	*out = cleaned;
	return (1);
}


t_token *dup_token_list(t_token *start, t_token *end)
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
	t_command	*curr_cmd;
	t_token		*curr;
	int			heredoc_id;
	t_parse_ctx ctx;

	heredoc_id = 0;
	cmd_head = NULL;
	curr_cmd = NULL;
	curr = tokens;
	ctx.env_list = env_list;
	ctx.exit_value = exit_value;
	ctx.heredoc_id = &heredoc_id;
	while (curr)
	{
		if (!cmd_head || curr->type == PIPE)
			curr_cmd = start_new_command(&cmd_head, curr_cmd, &curr);
		if (!curr_cmd)
			return (free_commands(cmd_head), NULL);
		if (!set_raw_tokens(curr_cmd, curr))
			return (free_commands(cmd_head), NULL);
		if (!setup_args_and_redirects(curr_cmd, &curr, &ctx))
			return (free_commands(cmd_head), NULL);
	}
	return (cmd_head);
}

