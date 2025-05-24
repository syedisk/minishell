/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_raw_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:35:01 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 19:15:28 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*dup_token_list(t_token *start, t_token *end)
{
	t_token	*new_head;
	t_token	*new_tok;
	t_token	*last;

	new_head = NULL;
	last = NULL;
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

int	set_raw_tokens(t_command *cmd, t_token *start)
{
	t_token	*end;

	end = start;
	while (end && end->type != PIPE)
		end = end->next;
	cmd->raw_tokens = dup_token_list(start, end);
	return (cmd->raw_tokens != NULL);
}
