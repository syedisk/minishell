/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:13:19 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/20 20:26:49 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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


static void handle_operator(const char *input, int *i, t_token **tokens)
{
	int				op_len;
	char			*op;
	t_token_type	type;

	type = get_operator_type(&input[*i], &op_len);
	op = ft_strndup(&input[*i], op_len);
	add_token(tokens, new_token(op, type, 0));
	*i += op_len;
}

static void	handle_word(const char *input, int *i, t_token **tokens)
{
	char	*word;
	int		quote_type;

	word = read_word(input, i, &quote_type);
	add_token(tokens, new_token(word, WORD, quote_type));
}

t_token	*tokenise(const char *input)
{
	t_token			*tokens;
	int				i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		else if (is_operator_char(input[i]))
			handle_operator(input, &i, &tokens);
		else
			handle_word(input, &i, &tokens);
	}
	return (tokens);
}
