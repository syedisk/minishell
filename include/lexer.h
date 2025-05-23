/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:43:42 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 21:54:41 by thkumara         ###   ########.fr       */
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
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quote_type; // 0 = unquoted, 1 = single, 2 = double
	struct s_token	*next;
}					t_token;

t_token_type	get_operator_type(const char *s, int *len);
t_token			*tokenise(const char *input);
t_token			*new_token(char *value, t_token_type type, int quote_type);
int				ft_isspace(char c);
int				is_operator_char(char c);
char			*read_quoted(const char *s, int *i);
void			free_tokens(t_token *tokens);
void			add_token(t_token **head, t_token *new);





#endif