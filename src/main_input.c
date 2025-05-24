/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:40:18 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 12:41:22 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_readline_active = 0;

char *custom_readline(const char *prompt)
{
    is_readline_active = 1;
    char *line = readline(prompt);
    is_readline_active = 0;
	if (!line)
        return NULL;
    return line;
}

int readline_active_state(void)
{
    return is_readline_active;
}