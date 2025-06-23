/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:01:37 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/23 20:02:33 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
