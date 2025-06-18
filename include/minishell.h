/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:58:54 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/18 23:34:02 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "error_handle.h"
# include "exec.h"
# include "expander.h"
# include "heredoc.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "signals.h"
# include "utils.h"
# include <errno.h>
# include <fcntl.h> // open
# include <limits.h>
# include <stdio.h>    // for printf
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>   // for malloc, free, exit, NULL
# include <sys/stat.h> // for stat
# include <sys/wait.h> // for wait
# include <unistd.h>   // for fork, execve, pipe

// main.c
char							**tokens_to_args(t_token *tokens);
int								handle_exit_if_null(char *input,
									t_env *env_list);
void							run_shell_loop(t_env **env_list,
									int *exit_value);

// main_utils.c
int								is_only_whitespace(const char *str);
int								is_skippable_input(char *input);
int								is_command_empty(t_command *cmd);

// main_utils2.c
int								process_and_execute(char *input,
									t_env **env_list, int *exit_value);

// main_signals.c
extern volatile sig_atomic_t	g_sig_received;
int								handle_interrupt_signal(char **input,
									int *exit_value);

// main_input.c
char							*custom_readline(const char *prompt);
int								readline_active_state(void);
void							set_readline_active_state(int state);

#endif
