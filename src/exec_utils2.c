/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:31:20 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/24 19:42:49 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_output_redirection(t_command *cmd, t_token **curr)
{
	int	result;

	*curr = (*curr)->next;
	if (!*curr || (*curr)->type != WORD)
		return (ft_putstr_fd(" No such file or directory\n", 2), 1);
	result = handle_output_file(cmd, *curr, &cmd->redir_fd_out);
	if (result != 0)
		return (1);
	*curr = (*curr)->next;
	return (0);
}

int	handle_all_redirs(t_command *cmd)
{
	t_token	*tokens;

	tokens = cmd->raw_tokens;
	if (cmd->heredoc)
		return (handle_heredoc_input(cmd));
	while (tokens)
	{
		if (tokens->type == REDIR_OUT || tokens->type == APPEND)
		{
			if (handle_output_redirection(cmd, &tokens) != 0)
				return (1);
			continue ;
		}
		if (tokens->type == REDIR_IN)
		{
			if (handle_input_redirection(cmd, &tokens) != 0)
				return (1);
			continue ;
		}
		tokens = tokens->next;
	}
	return (0);
}

int	handle_output_redirs(t_command *cmd)
{
	t_token	*tokens;
	int		fd;
	int		result;

	tokens = cmd->raw_tokens;
	fd = -1;
	while (tokens)
	{
		if (tokens->type == REDIR_OUT || tokens->type == APPEND)
		{
			tokens = tokens->next;
			if (!tokens || tokens->type != WORD)
				return (ft_putstr_fd(" No such file or directory\n", 2), 1);
			if (fd != -1)
				close(fd);
			result = handle_output_file(cmd, tokens, &fd);
			if (result != 0)
				return (1);
		}
		cmd->redir_fd_out = fd;
		tokens = tokens->next;
	}
	return (0);
}

int	process_input_file(t_command *cmd, t_token **curr, int *fd)
{
	*curr = (*curr)->next;
	if (!*curr || (*curr)->type != WORD)
		return (ft_putstr_fd(" No such file or directory\n", 2), 1);
	if (*fd != -1)
		close(*fd);
	*fd = open((*curr)->value, O_RDONLY);
	if (*fd == -1)
	{
		if (errno == 2)
			ft_putstr_fd(" No such file or directory\n", 2);
		else if (errno == 13)
			ft_putstr_fd(" Permission denied\n", 2);
		else
			perror("");
		return (1);
	}
	cmd->redir_fd_in = *fd;
	*curr = (*curr)->next;
	return (0);
}

int	handle_input_redirs(t_command *cmd)
{
	t_token	*tokens;
	int		fd;

	tokens = cmd->raw_tokens;
	fd = -1;
	if (cmd->heredoc)
		return (handle_heredoc_input(cmd));
	while (tokens)
	{
		if (tokens->type == REDIR_IN)
		{
			if (process_input_file(cmd, &tokens, &fd) != 0)
				return (1);
			continue ;
		}
		tokens = tokens->next;
	}
	return (0);
}
