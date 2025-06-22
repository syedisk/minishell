/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:40:39 by thkumara          #+#    #+#             */
/*   Updated: 2025/06/22 21:05:13 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*custom_readline(const char *prompt, t_shell_context *context)
{
	char	*line;

    line = NULL;
    if (context->is_readline_active == 0)
    {
	    context->is_readline_active = 1;
	    line = readline(prompt);
    }
    if (context)
	    context->is_readline_active = 0;
	return (line);
}

int	is_readline_active(t_shell_context *context)
{
    if (context)
	    return (context->is_readline_active);
    return (0);
}