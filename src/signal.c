/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:02:32 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/17 21:00:54 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void sig_handler(int sig)
{
    (void)sig;
    g_sig_received = 130;

    // If readline is active, interrupt it immediately
    write(1, "\n", 2);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();

    rl_done = 1; // This causes readline to return
}

void set_signals(void)
{
    struct sigaction sa_sig;

    sa_sig.sa_handler = sig_handler;
    sigemptyset(&sa_sig.sa_mask);
    sa_sig.sa_flags = SA_RESTART;

    if (sigaction(SIGINT, &sa_sig, NULL) == -1)
        perror("sigaction SIGINT");
    signal(SIGQUIT, SIG_IGN);
}

void ignore_sigquit(void)
{
    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGQUIT, &sa, NULL);
    g_sig_received = 131; // Set exit value for SIGQUIT
}

void heredoc_sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(130);  // Bash exits heredoc on Ctrl+C with 130
}

void handle_heredoc_signals(void)
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