/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:47:05 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/18 16:22:32 by sbin-ham         ###   ########.fr       */
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

t_command	*parse_tokens(t_token *tokens, t_env *env_list, int *exit_value);
void					free_commands(t_command *cmds);

#endif
