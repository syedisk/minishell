/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:43:42 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/20 19:24:32 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int quote_type; // 0 = unquoted, 1 = single, 2 = double
	struct s_token	*next;
}					t_token;

// lexer.c
t_token				*tokenise(const char *input);
void				free_tokens(t_token *tokens);
void				add_token(t_token **head, t_token *new);

// lexer_read_word.c
char				*read_word(const char *s, int *i, int *quote_type);

// in lexer_utils.c
int					is_operator_char(char c);
int					ft_isspace(char c);

#endif