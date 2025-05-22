/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:13:19 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/22 16:50:03 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*read_word(const char *s, int *i, int *quote_type)
{
	char	*result;
	char	*chunk;
	int		start;

	result = ft_strdup("");
	*quote_type = 0;
	while (s[*i] && !ft_isspace(s[*i]) && !is_operator_char(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '"')
			read_quoted_word(s, i, &result, quote_type);
		else
		{
			start = *i;
			while (s[*i] && !ft_isspace(s[*i]) && !is_operator_char(s[*i])
				&& s[*i] != '\'' && s[*i] != '"')
				(*i)++;
			chunk = ft_strndup(s + start, *i - start);
			result = ft_strjoin_free(result, chunk);
			free(chunk);
		}
	}
	return (result);
}

void	handle_operator(t_token **tokens, const char *input, int *i)
{
	int				op_len;
	char			*op;
	t_token_type	type;

	type = get_operator_type(&input[*i], &op_len);
	op = ft_strndup(&input[*i], op_len);
	add_token(tokens, new_token(op, type, 0));
	*i += op_len;
}

void	handle_word(t_token **tokens, const char *input,
	int *i, int *quote_type)
{
	char	*word;

	word = read_word(input, i, quote_type);
	add_token(tokens, new_token(word, WORD, *quote_type));
}

t_token	*tokenise(const char *input)
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
			handle_operator(&tokens, input, &i);
		else
			handle_word(&tokens, input, &i, &quote_type);
	}
	return (tokens);
}
