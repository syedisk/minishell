/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:46:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/19 20:17:57 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void wait_for_child_processes(int last_pid, int *exit_value)
{
    int pid;
	int status;

    pid = 0;
    while ((pid = wait(&status)) > 0)
    {
        // printf("pid %d\n", pid);
        if (pid == last_pid)
        {
            if (WIFEXITED(status))
                *exit_value = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                *exit_value = 128 + WTERMSIG(status);
        }
        // else if (last_pid > 0)
        // {
        //     waitpid(last_pid, &status, 0);

        //     if (WIFEXITED(status))
        //     {
        //         *exit_value = WEXITSTATUS(status);
        //         if (*exit_value != 0)
        //             return ;
        //     }
        //     else if (WIFSIGNALED(status))
        //         *exit_value = 128 + WTERMSIG(status);
        // }
    }
}
int fork_and_execute(t_command *cmd, t_env **env_list, char **envp, int fd_in, int *pipefd, int *exit_value)
{
    int pid;
    
    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        if (fd_in != 0) 
        {
           if (dup2(fd_in, STDIN_FILENO) == -1)
                exit((ft_putstr_fd(" dup_2 failed\n", 2),EXIT_FAILURE));
            close(fd_in);
        }
        if (pipefd) 
        {
            close(pipefd[0]);
            if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                exit((ft_putstr_fd(" dup_2 failed\n", 2),EXIT_FAILURE));
            close(pipefd[1]);
        }
        
        execute_child(cmd, env_list, envp, NULL, exit_value);
    }
    else if (pid == -1)
        exit((ft_putstr_fd(" fork failed\n", 2),EXIT_FAILURE));
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

void execute_commands(t_command *cmd, t_env **env_list, char **envp, int *exit_value)
{
    int pipefd[2];
    int fd_in = 0;
    int pid = -1;

    pipefd[0] = -1;
    while (cmd)
    {
        if (!cmd->argv || !cmd->argv[0])
        {
            cmd = cmd->next;
            continue;
        }
        if (is_builtin(cmd->argv[0]) && !cmd->next && fd_in == 0)
        {
            handle_input_redirs(cmd);
            handle_output_redirs(cmd);
            *exit_value = execute_builtin(cmd, env_list, exit_value);
            if (ft_strcmp(cmd->argv[0], "exit") == 0)
            {
                free_env_list(*env_list); // optional cleanup
                free_commands(cmd);       // optional cleanup
                free_split(envp);         // optional cleanup
                exit(*exit_value);
            }
            cmd = cmd->next;
            continue;
        }
        if (cmd->argv[0][0] == '$' && cmd->argv[0][1] != '\0')
        { 
            ft_putstr_fd(" command not found\n", 2);
            return;
        }
        if (cmd->next)
        {
            if (pipe(pipefd) == -1)
            {
                write(2, "pipe failed\n", 12);
                exit(EXIT_FAILURE);
            }
            pid = fork_and_execute(cmd, env_list, envp, fd_in, pipefd, exit_value);
            if (pid == -1)
            {
                close(pipefd[0]);
                close(pipefd[1]);
                exit((perror("fork failed"), EXIT_FAILURE));
            }
        }
        else
            pid = fork_and_execute(cmd, env_list, envp, fd_in, NULL, exit_value);
        if (pid == -1)
            exit((perror("fork failed"), EXIT_FAILURE));
        if (cmd->next)
            close_and_update_fds(&fd_in, cmd, pipefd);
        else
            close_and_update_fds(&fd_in, cmd, NULL);
        cmd = cmd->next;
    }
    wait_for_child_processes(pid, exit_value);
}
