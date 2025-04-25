/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:16:16 by thkumara          #+#    #+#             */
/*   Updated: 2025/04/25 16:50:53 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"
#include "heredoc.h"
#include <fcntl.h>

int last_exit_status = 0;

void	ft_free_split(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *resolve_path(char *cmd)
{
	char **paths;
	char *env_path;
	char *full;
	int i;
	size_t len;

	i = 0;
	env_path = getenv("PATH");
	if (!env_path || ft_strchr(cmd, '/'))
		return ft_strdup(cmd);
	paths = ft_split(env_path, ':');
	while (paths[i]) 
	{
		len = ft_strlen(paths[i]) + ft_strlen(cmd) + 2; // why +2?
		full = malloc(len);
		if (!full)
		{
			ft_free_split(paths);
			return (NULL);
		}
		ft_strlcpy(full, paths[i], len);
		ft_strlcat(full, "/", len);
		ft_strlcat(full, cmd, len);

		if (access(full, X_OK) == 0) // what is access??
		{
			ft_free_split(paths);
			return full;
		}
		free(full);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

int	is_builtin(char	*cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"));
}

// use this instead for modularity?

// int	is_builtin(char *cmd)
// {
// 	const char *builtins[] = {"cd", "pwd", "echo", "env", "exit", "export", "unset", NULL};
// 	int i = 0;

// 	while (builtins[i])
// 	{
// 		if (!ft_strcmp(cmd, builtins[i]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }


int	execute_builtin(t_command *cmd, t_env **env_list)
{
	if (!cmd || !cmd->argv[0])
		return (0);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		if(!cmd->argv[1])
		{
			write(2, "cd: Argument missing\n", 21); // in most shells, cd with no arguments sends you to the $HOME directory. check obsidan 18 Apr
			last_exit_status = 1; // on error
			return (1);
		}
		if (chdir(cmd->argv[1]) != 0)  // if changing directory fails
		{
			perror("cd");
			last_exit_status = 1; // on error
			return (1);
		}
		last_exit_status = 0; // on success
		return (0);
	}
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		char cwd[1024]; // buffer size enough? use PATH_MAX with <limits.h>? or #define PATH_MAX 4096?
		if (getcwd(cwd, sizeof(cwd)))
			printf("%s\n", cwd);
		else
		{
			perror("pwd");
			last_exit_status = 1; // on error
			return (1);
		}
		last_exit_status = 0; // on success
		return (0);
	}
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		return (handle_echo(cmd->argv, *env_list));
	else if (!ft_strcmp(cmd->argv[0], "export"))	//Do we need to handle echo & export error?
		return (handle_export(cmd->argv, env_list));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (handle_unset(cmd->argv, env_list));
	else if (!ft_strcmp(cmd->argv[0], "env"))
	 	return (ft_env(*env_list));
	else if (!ft_strcmp(cmd->argv[0], "exit"))
	{
		if (cmd->argv[1])
			exit(ft_atoi(cmd->argv[1])); // `echo $?` prints exit code of the last command. //Handled
		else
			exit(0);
	}
	else
		return (0);
}

void	execute_commands(t_command *cmd_head, t_env **env_list, char **envp)
{
	int fd_in;
	int fd;
	int pipefd[2];
	pid_t	pid;
	pid_t	last_pid = -1;
	int		status;

	fd_in = 0;
	while (cmd_head)
	{
		if (is_builtin(cmd_head->argv[0]) && !cmd_head->next && fd_in == 0)
		{
			execute_builtin(cmd_head, env_list);
			cmd_head = cmd_head->next;
			continue;  
		}
		if (cmd_head->next && pipe(pipefd) == -1)
		{
			perror("pipe failed");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		// waitpid(pid, &status, 0);	// Wait for all children and capture last command’s exit status
		if (pid == -1)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (cmd_head->heredoc)
			{
				// fd = create_heredoc_file(cmd_head->infile, cmd_head->delimiter, 1, envp);
				fd = open(cmd_head->infile, O_RDONLY);
				if (fd == -1)
				{
					perror("heredoc failed");
					exit(EXIT_FAILURE);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
				unlink(cmd_head->infile); // clean up temp file
			}
			else if (cmd_head->infile)
			{
				fd = open(cmd_head->infile, O_RDONLY);
				if (fd == -1)
				{
					perror("open infile failed");
					exit(EXIT_FAILURE);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			else if (fd_in != 0) // why would fd_in not be zero? it is set to zero above.
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (cmd_head->outfile)
			{
				if (cmd_head->append_out)
					fd = open(cmd_head->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					fd = open(cmd_head->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1)
				{
					perror("open outfile failed");
					exit(EXIT_FAILURE);
				}
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			else if (cmd_head->next)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
				close(pipefd[0]);
			}
			if (is_builtin(cmd_head->argv[0]))
				execute_builtin(cmd_head, env_list);
			else
			{
				char *full_path = resolve_path(cmd_head->argv[0]);
				if (!full_path)
				{
					perror("Command not found");
					exit(127);
				}
				if (execve(full_path, cmd_head->argv, envp) == -1)  // changed environ to envp and 1 to -1
				{
					perror("execve failed");
					exit(EXIT_FAILURE);
				}
			}
			exit(EXIT_SUCCESS);
		}
		else
			last_pid = pid;
		if (fd_in != 0)
			close(fd_in);
		if (cmd_head->next)
		{
			close(pipefd[1]);
			fd_in = pipefd[0];
		}
		cmd_head = cmd_head->next;
	}
	// while (wait(NULL) > 0); Replace by below block of code
	// Wait for all children and capture last command’s exit status
	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_exit_status = 128 + WTERMSIG(status);
		}
	}
}
