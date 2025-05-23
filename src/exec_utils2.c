/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:31:20 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/23 19:36:35 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_heredoc_input(t_command *cmd)
{
	int fd;
	int dup_result;
	int unlink_result;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd(" No such file or directory\n", 2), 1);
	// printf("🔁 4. dup2: redirecting %d to %d\n", fd, STDIN_FILENO);
	dup_result = dup2(fd, STDIN_FILENO);
	if (dup_result == -1)
		return (ft_putstr_fd(" No such file or directory\n", 2), 1);
	close(fd);
	unlink_result = unlink(cmd->infile);
	(void)unlink_result;
	return (0);
}

int handle_input_redirs(t_command *cmd)
{
	t_token *tokens;
	int fd;
	int dup_result;

	tokens = cmd->raw_tokens;
	fd = -1;
	if (cmd->heredoc)
		return handle_heredoc_input(cmd);
	while (tokens)
	{
		if (tokens->type == REDIR_IN)
		{
			tokens = tokens->next;
			if (!tokens || tokens->type != WORD)
				return (ft_putstr_fd(" No such file or directory\n", 2), 1);
			if (fd != -1)
				close(fd);
			fd = open(tokens->value, O_RDONLY);
			if (fd == -1)
			{
				if (errno == 2)
					ft_putstr_fd(" No such file or directory\n", 2);
				else if (errno == 13)
					ft_putstr_fd(" Permission denied\n", 2);
				else
					perror("");
				return (1);
			}
		}
		tokens = tokens->next;
	}
	if (fd != -1)
	{
		// printf("🔁 3. dup2: redirecting %d to %d\n", fd, STDIN_FILENO);
		dup_result = dup2(fd, STDIN_FILENO);
		if (dup_result == -1)
			return (ft_putstr_fd(" No such file or directory\n", 2), 1);
		close(fd);
	}
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
			ft_putstr_fd(" No such file or directory\n", 2);
		else if (errno == 13)
			ft_putstr_fd(" Permission denied\n", 2);
		else
			perror(" ");
		return (1);
	}
	*fd = tmp_fd;
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
		tokens = tokens->next;
	}
	if (fd != -1)
	{
		// printf("🔁 5. dup2: redirecting %d to %d\n", fd, STDOUT_FILENO);
		result = dup2(fd, STDOUT_FILENO);
		if (result == -1)
			return (ft_putstr_fd(" No such file or directory\n", 2), 1);
		close(fd);
	}
	return (0);
}

void	handle_child_redirections(t_command *cmd, int *pipefd)
{
	int	result;
	pipefd = 0;

	result = handle_input_redirs(cmd);
	if (result != 0)
		exit(1);
	// if (!cmd->heredoc && !has_input_redir(cmd->raw_tokens) && pipefd[0] != -1)
	// {
	// 	printf("🔁 6. dup2: redirecting %d to %d\n", pipefd[0], STDIN_FILENO);
	// 	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	// 		exit((ft_putstr_fd(" No such file or directory\n", 2), 1));
	// 	close(pipefd[0]);
	// }
	result = handle_output_redirs(cmd);
	if (result != 0)
		exit(1);
	// if (cmd->next && pipefd[1] != -1)
	// {
	// 	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	// 		ft_putstr_fd(" No such file or directory\n", 2);
	// 	close(pipefd[1]);
	// 	close(pipefd[0]);
	// }
}

void	execute_child(t_command *cmd, t_exec_params *param)
{
	char		*full_path;

	// printf("2./n");
	handle_child_redirections(cmd, param->pipefd);
	if (!cmd || !cmd->argv || !cmd->argv[0])
		exit((printf("Error: Null pointer in execute_child\n"), 127));
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(cmd, param->env_list, param->exit_value));
	if (cmd->argv[0] && !ft_strcmp(cmd->argv[0], "export="))
		exit(0);
	full_path = resolve_path(cmd->argv[0]);
	if (!full_path)
		exit((ft_putstr_fd(" command not found\n", 2), 127));
	if (access(full_path, F_OK) == 0 && access(full_path, X_OK) != 0)
		exit((ft_putstr_fd(" Permission denied\n", 2), 126));
	if (is_directory(cmd->argv[0]) != 0)
		exit((ft_putstr_fd(" Is a directory\n", 2), 126));
	if ((execve(full_path, cmd->argv, param->envp) == -1))
	{
		if (errno == 2)
			exit((ft_putstr_fd(" No such file or directory\n", 2), 127));
		else if (errno == 13)
			exit((ft_putstr_fd(" Permission denied\n", 2), 126));
		else
			exit((perror(""), 127));
	}
	else
		exit(0);
	exit((free(full_path),0));
}
