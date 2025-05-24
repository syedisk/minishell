/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:47:05 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 13:36:58 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_command
{
	char				**argv;
	char				*infile;
	char				*outfile;
	int					append_out;
	int					heredoc;
	char				*delimiter;
	int					pipe_after;
	int					is_builtin;
	t_token				*raw_tokens;
	int					exit_value;
	struct s_command	*next;
}						t_command;

typedef struct s_parse_ctx
{
	t_env				*env_list;
	int					*exit_value;
	int					*heredoc_id;
}						t_parse_ctx;

// parser.c
t_command				*start_new_command(t_command **head, t_command *prev,
							t_token **curr);
void					init_command(t_command *cmd);
int						expand_word(t_token *token, t_env *env_list,
							int *exit_value, char **out);
t_command				*parse_tokens(t_token *tokens, t_env *env_list,
							int *exit_value);

// parser_setup_args.c
int						count_args(t_token *token);
int						handle_redirection(t_command *cmd, t_token **curr,
							t_parse_ctx *ctx);
int						setup_args_and_redirects(t_command *cmd, t_token **curr,
							t_parse_ctx *ctx);

// parser_handle_redir.c
int						handle_heredoc(t_command *cmd, t_token **curr,
							t_parse_ctx *ctx);
int						handle_file_redir(t_command *cmd, t_token **curr);

// parser_raw_tokens.c
t_token					*dup_token_list(t_token *start, t_token *end);
int						set_raw_tokens(t_command *cmd, t_token *start);

// free_utils.c
void					free_commands(t_command *cmds);

#endif
