/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:40:18 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 13:13:15 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*custom_readline(const char *prompt)
{
	char	*line;

	set_readline_active_state(1);
	line = readline(prompt);
	set_readline_active_state(0);
	if (!line)
		return (NULL);
	return (line);
}

int	readline_active_state(void)
{
	static int	is_readline_active = 0;

	return (is_readline_active);
}

void	set_readline_active_state(int state)
{
	static int	is_readline_active = 0;

	is_readline_active = state;
}
