/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:13:19 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/23 20:12:50 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	read_quoted_word(const char *s, int *i, char **result, int *quote_type)
{
	int		start;
	char	quote;
	char	*chunk;

	quote = s[(*i)++];
	start = *i;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	chunk = ft_strndup(s + start, *i - start);
	if (s[*i] == quote)
		(*i)++;
	*result = ft_strjoin_free(*result, chunk);
	free(chunk);
	if (*quote_type == 0)
	{
		if (quote == '\'')
			*quote_type = 1;
		else if (quote == '"')
			*quote_type = 2;
	}
}

static int	handle_invalid_operator(const char *input, int *i,
	int len, t_parse_ctx *ctx)
{
	char	*op;

	op = ft_strndup(&input[*i], len);
	if (!op)
		return (0);
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(op, 2);
	ft_putstr_fd("'\n", 2);
	free(op);
	*i += len;
	ctx->syntax_error = 1;
	return (0);
}

void	handle_operator(t_token **tokens, const char *input,
	int *i, t_parse_ctx *ctx)
{
	int				len;
	char			*op;
	t_token_type	type;
	t_token			*new;

	type = get_operator_type(&input[*i], &len);
	if (type == TOKEN_ERROR)
	{
		if (!handle_invalid_operator(input, i, len, ctx))
			return ;
	}
	op = ft_strndup(&input[*i], len);
	if (!op)
		return ;
	new = new_token(op, type, 0);
	if (!new)
	{
		free(op);
		return ;
	}
	add_token(tokens, new);
	*i += len;
}

void	handle_word(t_token **tokens, const char *input,
	int *i, int *quote_type)
{
	char	*word;
	t_token	*new;

	word = read_word(input, i, quote_type);
	if (!word)
		return ;
	new = new_token(word, WORD, *quote_type);
	if (!new)
	{
		free(word);
		return ;
	}
	add_token(tokens, new);
}

t_token	*tokenise(const char *input, t_parse_ctx *ctx)
{
	t_token	*tokens;
	int		i;
	int		quote_type;

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
			handle_operator(&tokens, input, &i, ctx);
		else
			handle_word(&tokens, input, &i, &quote_type);
	}
	return (tokens);
}
