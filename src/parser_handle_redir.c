/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:32:22 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 17:32:47 by sbin-ham         ###   ########.fr       */
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

int	handle_heredoc(t_command *cmd, t_token **curr, t_parse_ctx *ctx)
{
	char	*delim;
	char	*heredoc_path;
	int		expand;
	t_token	*next;
	
	next = (*curr)->next;
	if (!next)
		return (0);
	expand = 1;
	if ((*curr)->value[0] == '\'' || (*curr)->value[0] == '"')
		expand = 0;
	delim = remove_quotes((*curr)->value);
	if (!delim)
		return (0);
	heredoc_path = generate_heredoc_filename((*ctx->heredoc_id)++);
	if (!heredoc_path)
	{
		free(delim);
		return (0);
	}
	create_heredoc_file(heredoc_path, delim, expand, ctx->env_list, ctx->exit_value);
	cmd->heredoc = 1;
	cmd->infile = heredoc_path;
	free(delim);
	*curr = next->next;
	return (1);
}