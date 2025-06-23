/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_raw_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:35:01 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/23 19:32:14 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*dup_one_token(t_token *src)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(src->value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = src->type;
	new->quote_type = src->quote_type;
	new->next = NULL;
	return (new);
}

t_token	*dup_token_list(t_token *start, t_token *end)
{
	t_token	*new_head;
	t_token	*new_tok;
	t_token	*last;

	new_head = NULL;
	last = NULL;
	while (start && start != end)
	{
		new_tok = dup_one_token(start);
		if (!new_tok)
		{
			free_tokens(new_head);
			return (NULL);
		}
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
