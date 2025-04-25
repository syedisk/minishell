/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:58:54 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/23 19:00:53 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "exec.h"
# include "utils.h"
# include "expander.h"
# include <fcntl.h> // open
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>    // for printf
# include <stdlib.h>   // for malloc, free, exit, NULL
# include <sys/wait.h> // for wait
# include <unistd.h>   // for fork, execve, pipe

extern	int	last_exit_status;

#endif
