/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:07:47 by thkumara          #+#    #+#             */
/*   Updated: 2025/04/30 17:18:50 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_quote(char c) 
{
    if (c == '\'' || c == '"')
        return (1);
    return (0);
}

// Checks if quotes are balanced
int has_unclosed_quotes(const char *input) 
{
    char quote = 0;
    while (*input)
    {
        if (!quote && is_quote(*input))
            quote = *input;
        else if (quote && *input == quote)
            quote = 0;
        input++;
    }
    if (quote)
        return (1); // Unclosed quote found
    return (0);
}

// Checks for invalid syntax at the end (like "|", "||", ">", etc.)
int has_trailing_operator(const char *input) 
{
    const char *trim = input;
    while (*trim == ' ')
        trim++;

    int len = strlen(trim);
    if (len == 0)
        return (1);

    // Skip trailing spaces
    while (len > 0 && trim[len - 1] == ' ')
        len--;

    if (len == 0)
        return (1);

    // Check trailing operator
    if (trim[len - 1] == '|' || trim[len - 1] == '<' || trim[len - 1] == '>')
        return (1);
    return (0);
}

int check_syntax_error(const char *input) 
{
    if (!input || *input == '\0') 
    {
        fprintf(stderr, "minishell: syntax error: empty input\n");
        return (1);
    }

    if (has_unclosed_quotes(input)) 
    {
        fprintf(stderr, "minishell: syntax error: unclosed quote\n");
        return (1);
    }

    if (has_trailing_operator(input)) 
    {
        fprintf(stderr, "minishell: syntax error near unexpected token `newline`\n");
        return (1);
    }
    return (0);
}
