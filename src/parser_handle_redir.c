/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:32:22 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 22:12:46 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_file_redir(t_command *cmd, t_token **curr)
{
	t_token	*next;

	next = (*curr)->next;
	if (!next)
		return (0);
	if ((*curr)->type == REDIR_IN)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(next->value);
	}
	else if ((*curr)->type == REDIR_OUT || (*curr)->type == APPEND)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = ft_strdup(next->value);
		cmd->append_out = ((*curr)->type == APPEND);
	}
	*curr = next->next;
	return (1);
}

t_heredoc_info	init_heredoc_info(const char *filepath, char *delimiter,
		int expand, t_parse_ctx *ctx)
{
	t_heredoc_info	info;

	info.filepath = filepath;
	info.delimiter = delimiter;
	info.expand = expand;
	info.env_list = ctx->env_list;
	info.exit_value = ctx->exit_value;
	return (info);
}

int	handle_heredoc(t_command *cmd, t_token **curr, t_parse_ctx *ctx)
{
	char			*delim;
	char			*heredoc_path;
	t_token			*next;
	t_heredoc_info	info;

	next = (*curr)->next;
	if (!next)
		return (0);
	delim = remove_quotes(next->value);
	if (!delim)
		return (0);
	heredoc_path = generate_heredoc_filename((*ctx->heredoc_id)++);
	if (!heredoc_path)
		return (free(delim), 0);
	info = init_heredoc_info(heredoc_path, delim,
			!(next->value[0] == '\'' || next->value[0] == '"'), ctx);
	if (create_heredoc_file(&info) == -1)
		return (free(delim), free(heredoc_path), 0);
	cmd->heredoc = 1;
	cmd->infile = heredoc_path;
	free(delim);
	*curr = next->next;
	return (1);
}
