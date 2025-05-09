/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:46:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/09 16:10:18 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int last_exit_status = 0;

void wait_for_child_processes(int last_pid)
{
    int pid;
	int status;

    pid = 0;
    while ((pid = wait(&status)) > 0)
    {
        if (pid == last_pid)
        {
            if (WIFEXITED(status))
                last_exit_status = WEXITSTATUS(status);
            else
                last_exit_status = 128 + WTERMSIG(status);
        }
    }
}
int fork_and_execute(t_command *cmd, t_env **env_list, char **envp, int fd_in, int *pipefd)
{
    int pid;
    
    pid = fork();
    if (pid == 0)
    {
        if (fd_in != 0) 
        {
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (cmd->next) 
        {
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);
        }
        execute_child(cmd, env_list, envp, NULL);
    }
    return pid;
}

void close_and_update_fds(int *fd_in, t_command *cmd, int *pipefd)
{
    if (*fd_in != 0)
        close(*fd_in);
    if (cmd->next && pipefd)
    {
        close(pipefd[1]);
        *fd_in = pipefd[0];
    }
}

void execute_commands(t_command *cmd, t_env **env_list, char **envp)
{
    int pipefd[2];
    int fd_in = 0;
    int pid = -1;

    while (cmd)
    {
        if (!cmd->argv || !cmd->argv[0])
        {
            cmd = cmd->next;
            continue;
        }
        if (is_builtin(cmd->argv[0]) && !cmd->next && fd_in == 0)
        {
            last_exit_status = execute_builtin(cmd, env_list);
            cmd = cmd->next;
            continue;
        }
        if (cmd->next)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe failed");
                exit(EXIT_FAILURE);
            }
        }
        pid = fork_and_execute(cmd, env_list, envp, fd_in, pipefd);
        if (pid == -1)
            exit((perror("fork failed"), EXIT_FAILURE));
        close_and_update_fds(&fd_in, cmd, pipefd);
        cmd = cmd->next;
    }
    wait_for_child_processes(pid);
}
