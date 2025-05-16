/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:07:47 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/15 15:33:14 by thkumara         ###   ########.fr       */
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

    int len = ft_strlen(trim);
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
       // printf("minishell: syntax error: empty input\n");
        return (1);
    }

    if (has_unclosed_quotes(input)) 
    {
        write(2, "minishell: syntax error: unclosed quote\n", 40);
        return (1);
    }

    if (has_trailing_operator(input)) 
    {
        write(2, "minishell: syntax error near unexpected token `newline`\n", 57);
        return (1);
    }
    return (0);
}

void error_msg(char *error)
{
    if (ft_strcmp(error, "execve_fail") == 0)
        write(2, "command not found\n", 19);
    else if (ft_strcmp(error, "outfile_fail") == 0)
        write(2, "Permission denied\n", 19);
    else if (ft_strcmp(error, "infile_fail") == 0)
        write(2, "Permission denied\n", 19);
    else if (ft_strcmp(error, "heredoc_fail") == 0)
        write(2, "command not found\n", 19);
    else if (ft_strcmp(error, "is_directory") == 0)
        write(2, "Is a directory\n", 16);
    else if (ft_strcmp(error, "export_fail") == 0)
        write(2, "not a valid identifier\n", 24);
    else if (ft_strcmp(error, "unset_fail") == 0)
        write(2, "unset: not a valid identifier\n", 31);
    else if (ft_strcmp(error, "cd_fail") == 0)
        write(2, "cd: no such file or directory\n", 31);
    else if (ft_strcmp(error, "dup2_failed_fd") == 0)
        write(2, "dup2 failed for fd\n", 20);
    else if (ft_strcmp(error, "pwd_got_arg") == 0)
        write (2, "pwd: too many arguments\n", 24);
    else
    {
        write(2, "Error: ", 7);
        write(2, error, ft_strlen(error));
        write(2, "\n", 1);
    }
}