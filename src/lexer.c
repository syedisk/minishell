/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:13:19 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/17 20:17:59 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f'
		|| ch == '\r')
		return (1);
	return (0);
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

	cur = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token_type	get_operator_type(const char *s, int *len)
{
	if (s[0] == '|')
	{
		*len = 1;
		return (PIPE);
	}
	if (s[0] == '<' && s[1] == '<')
	{
		*len = 2;
		return (HEREDOC);
	}
	if (s[0] == '>' && s[1] == '>')
	{
		*len = 2;
		return (APPEND);
	}
	if (s[0] == '<')
	{
		*len = 1;
		return (REDIR_IN);
	}
	if (s[0] == '>')
	{
		*len = 1;
		return (REDIR_OUT);
	}
	return (WORD);
}

char	*read_word(const char *s, int *i)
{
	int		start;
	char	quote;

	start = *i;
	while (s[*i] && !ft_isspace(s[*i]) && !is_operator_char(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			quote = s[(*i)++];
			while (s[*i] && s[*i] != quote)
				(*i)++;
			if (s[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	return (ft_strndup(s + start, *i - start));
}

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
t_token	*tokenise(const char *input)
{
	t_token			*tokens;
	int				i;
	int				op_len;
	t_token_type	type;
	char			*op;
	char			*quoted;
	char			*word;
	char			quote;
	int				quote_type;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		if (is_operator_char(input[i]))
		{
			type = get_operator_type(&input[i], &op_len);
			op = ft_strndup(&input[i], op_len);
			add_token(&tokens, new_token(op, type, 0));
			i += op_len;
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i];
			quoted = read_quoted(input, &i); // Extract quoted string
			if (quote == '\'')
				quote_type = 1;
			else
				quote_type = 2;
            add_token(&tokens, new_token(quoted, WORD, quote_type));
		}
		else
		{
			word = read_word(input, &i);
			add_token(&tokens, new_token(word, WORD, 0));
		}
	}
	return (tokens);
}
