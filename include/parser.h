/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:47:05 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/22 21:11:44 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_command
{
	char				**argv; // command and arguments
	char				*infile; // <
	char				*outfile; // > or >>
	int					append_out; // 1 if '>>', 0 if '>'
	int					heredoc; // 1 if uses heredoc '<<'
	char				*delimiter; // delimiter for heredoc
	int					pipe_after; // 1 if pipe to next command, 0 if not
	int					is_builtin; // 1 if command is builtin
	t_token				*raw_tokens;
	int					exit_value; // exit value of the command
	struct s_command	*next;
}						t_command;

typedef struct s_parse_ctx
{
	t_env	*env_list;
	int		*exit_value;
	int		*heredoc_id;
}	t_parse_ctx;


t_command	*parse_tokens(t_token *tokens, t_env *env_list, int *exit_value);
void					free_commands(t_command *cmds);
t_token *dup_token_list(t_token *start, t_token *end);
int	expand_word(t_token *token, t_env *env_list, int *exit_value, char **out);
int	count_args(t_token *token);
int	handle_heredoc(t_command *cmd, t_token **curr, t_parse_ctx *ctx);
int	handle_file_redir(t_command *cmd, t_token **curr);
int	handle_redirection(t_command *cmd, t_token **curr, t_parse_ctx *ctx);
int	setup_args_and_redirects(t_command *cmd, t_token **curr, t_parse_ctx *ctx);
int	set_raw_tokens(t_command *cmd, t_token *start);
void	init_command(t_command *cmd);
t_command	*start_new_command(t_command **head, t_command *prev, t_token **curr);

#endif
