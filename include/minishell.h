/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:58:54 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/15 19:40:24 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "builtins.h"
# include "utils.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>    // for printf
# include <stdlib.h>   // for malloc, free, exit, NULL
# include <sys/wait.h> // for wait
# include <unistd.h>   // for fork, execve, pipe

#endif
