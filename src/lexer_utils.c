/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:43:23 by thkumara          #+#    #+#             */
/*   Updated: 2025/06/23 15:30:29 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_quoted(const char *s, int *i)
{
	char	quote;
	int		start;
	char	*val;

	quote = s[(*i)++];
	start = *i;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	val = ft_strndup(s + start, *i - start);
	if (s[*i])
		(*i)++;
	return (val);
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token_type	get_operator_type(const char *s, int *len)
{
	if ((s[0] == '>' && s[1] == '>' && s[2] == '>') || (s[0] == '<'
			&& s[1] == '<' && s[2] == '<') || (s[0] == '>' && s[1] == '<')
		|| (s[0] == '<' && s[1] == '>') || (s[0] == '>' && s[1] == '|')
		|| (s[0] == '<' && s[1] == '|') || (s[0] == '|' && s[1] == '|'))
	{
		*len = 1;
		return (TOKEN_ERROR);
	}
	if (s[0] == '|')
		return (*len = 1, PIPE);
	if (s[0] == '<' && s[1] == '<')
		return (*len = 2, HEREDOC);
	if (s[0] == '>' && s[1] == '>')
		return (*len = 2, APPEND);
	if (s[0] == '<')
		return (*len = 1, REDIR_IN);
	if (s[0] == '>')
		return (*len = 1, REDIR_OUT);
	return (WORD);
}

t_token	*new_token(char *value, t_token_type type, int quote_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->quote_type = quote_type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*cur;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
