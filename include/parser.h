/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:47:05 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/03/29 16:37:16 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_command
{
	char	**argv;
	char	*infile;
	char	*outfile;
	int		append_out;
	struct	s_command *next;
}			t_command;

t_command	*parse_tokens(t_token *tokens);
void free_commands(t_command *cmds);

#endif
