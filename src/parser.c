/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:06:49 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 17:25:02 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "heredoc.h"
#include "minishell.h"
#include "utils.h"

t_command	*start_new_command(t_command **head, t_command *prev,
		t_token **curr)
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
	cmd->redir_fd_out = -1;
	cmd->redir_fd_in = -1;
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

t_command	*parse_tokens(t_token *tokens, t_parse_ctx *ctx)
{
	t_command	*cmd_head;
	t_command	*curr_cmd;
	t_token		*curr;

	cmd_head = NULL;
	curr_cmd = NULL;
	curr = tokens;
	while (curr)
	{
		if (!cmd_head || curr->type == PIPE)
			curr_cmd = start_new_command(&cmd_head, curr_cmd, &curr);
		if (!curr_cmd)
			return (free_commands(cmd_head), NULL);
		if (!set_raw_tokens(curr_cmd, curr))
			return (free_commands(cmd_head), NULL);
		if (!setup_args_and_redirects(curr_cmd, &curr, ctx))
			return (free_commands(cmd_head), NULL);
	}
	return (cmd_head);
}
