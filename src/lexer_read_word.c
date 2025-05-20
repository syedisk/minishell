/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:30:15 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/20 18:37:37 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_quoted_chunk(const char *s, int *i,
	char **result, int *quote_type)
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

static void	append_unquoted_chunk(const char *s, int *i, char **result)
{
	int		start;
	char	*chunk;

	start = *i;
	while (s[*i] && !ft_isspace(s[*i]) && !is_operator_char(s[*i])
		&& s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	chunk = ft_strndup(s + start, *i - start);
	*result = ft_strjoin_free(*result, chunk);
	free(chunk);
}

char	*read_word(const char *s, int *i, int *quote_type)
{
	char	*result;

	result = ft_strdup("");
	*quote_type = 0;
	while (s[*i] && !ft_isspace(s[*i]) && !is_operator_char(s[*i]))
	{
		if (s[*i] == '\'' || s[*i] == '"')
			append_quoted_chunk(s, i, &result, quote_type);
		else
			append_unquoted_chunk(s, i, &result);
	}
	return (result);
}
