/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:07:47 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/24 16:21:48 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	has_unclosed_quotes(const char *input)
{
	char	quote;

	quote = 0;
	while (*input)
	{
		if (!quote && is_quote(*input))
			quote = *input;
		else if (quote && *input == quote)
			quote = 0;
		input++;
	}
	if (quote)
		return (1);
	return (0);
}

int	has_trailing_operator(const char *input)
{
	const char	*trim;
	int			len;

	trim = input;
	while (*trim == ' ')
		trim++;
	len = ft_strlen(trim);
	if (len == 0)
		return (1);
	while (len > 0 && trim[len - 1] == ' ')
		len--;
	if (len == 0)
		return (1);
	if (trim[len - 1] == '|' || trim[len - 1] == '<' || trim[len - 1] == '>')
		return (1);
	return (0);
}

int	check_syntax_error(const char *input)
{
	if (!input || *input == '\0')
		return (1);
	if (has_unclosed_quotes(input))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (1);
	}
	if (has_trailing_operator(input))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (1);
	}
	return (0);
}
