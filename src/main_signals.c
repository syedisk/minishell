/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:41:49 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 13:14:01 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_received = 0;

int	handle_interrupt_signal(char **input, int *exit_value)
{
	if (g_sig_received == 130)
	{
		*exit_value = 130;
		g_sig_received = 0;
		if (**input == '\0')
		{
			free(*input);
			return (0);
		}
	}
	return (1);
}
