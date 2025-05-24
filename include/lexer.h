/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:43:42 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 17:11:52 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

struct s_parse_ctx;
typedef struct s_parse_ctx t_parse_ctx;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	TOKEN_ERROR
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quote_type; // 0 = unquoted, 1 = single, 2 = double
	struct s_token	*next;
}					t_token;

t_token	*tokenise(const char *input, t_parse_ctx *ctx);
void	free_tokens(t_token *tokens);
void	add_token(t_token **head, t_token *new);
int		ft_isspace(char c);
char	*read_quoted(const char *s, int *i);
int	    is_operator_char(char c);
t_token_type	get_operator_type(const char *s, int *len);
t_token	*new_token(char *value, t_token_type type, int quote_type);


#endif