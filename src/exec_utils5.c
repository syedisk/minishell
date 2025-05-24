/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:22:22 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 19:44:56 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_input(t_command *cmd)
{
	int	fd;
	int	dup_result;
	int	unlink_result;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd(" No such file or directory\n", 2), 1);
	dup_result = dup2(fd, STDIN_FILENO);
	if (dup_result == -1)
		return (ft_putstr_fd(" No such file or directory\n", 2), 1);
	close(fd);
	unlink_result = unlink(cmd->infile);
	(void)unlink_result;
	return (0);
}

int	handle_output_file(t_command *cmd, t_token *tokens, int *fd)
{
	int		tmp_fd;

	tmp_fd = -1;
	if (cmd->append_out)
		tmp_fd = open(tokens->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		tmp_fd = open(tokens->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		if (errno == 2)
			ft_putstr_fd(" No such file or directoryrtertr\n", 2);
		else if (errno == 13)
			ft_putstr_fd(" Permission denied\n", 2);
		else
			perror(" ");
		return (1);
	}
	*fd = tmp_fd;
	return (0);
}

void	handle_child_redirections(t_command *cmd)
{
	int	result;

	result = handle_all_redirs(cmd);
	if (result != 0)
		exit(1);
}

void	handle_redir_fds(t_command *cmd)
{
	if (cmd->redir_fd_out != -1)
	{
		if (dup2(cmd->redir_fd_out, STDOUT_FILENO) == -1)
			exit((ft_putstr_fd(" No such file or directory\n", 2), 1));
		close(cmd->redir_fd_out);
	}
	if (cmd->redir_fd_in != -1)
	{
		if (dup2(cmd->redir_fd_in, STDIN_FILENO) == -1)
			exit((ft_putstr_fd(" No such file or directory\n", 2), 1));
		close(cmd->redir_fd_in);
	}
}

char	*resolve_and_validate_path(char *cmd_name)
{
	char	*path;

	path = resolve_path(cmd_name);
	if (!path)
	{
		ft_putstr_fd(" command not found\n", 2);
		return (NULL);
	}
	if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		free(path);
		exit(126);
	}
	if (is_directory(cmd_name))
	{
		ft_putstr_fd(" Is a directory\n", 2);
		free(path);
		exit(126);
	}
	return (path);
}
