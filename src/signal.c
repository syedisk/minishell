/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:02:32 by thkumara          #+#    #+#             */
/*   Updated: 2025/04/15 18:54:21 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>


void    sig_handler(int signal)
{
    (void)signal;

    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    set_signals(void)
{
    struct sigaction sa_sig;
    
    sa_sig.sa_handler = sig_handler;
    sa_sig.sa_flags = SA_RESTART;
    sigemptyset(&sa_sig.sa_mask);
    sigaction(SIGINT, &sa_sig, NULL);

    if (sigaction(SIGINT, &sa_sig, NULL) == -1)
        perror("sigaction");

    signal(SIGQUIT, SIG_IGN);
}

void ignore_sigquit(void)
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGQUIT, &sa, NULL);
}

void heredoc_sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(130);  // Bash exits heredoc on Ctrl+C with 130
}

void setup_heredoc_signals(void)
{
    signal(SIGINT, heredoc_sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

// After readline
// if (!line)
// {
//     write(STDOUT_FILENO, "exit\n", 5);
//     exit(0); // or your custom cleanup and exit
// }

// Inside child process 
// After fork
// signal(SIGQUIT, SIG_DFL);
// signal(SIGINT, SIG_DFL);