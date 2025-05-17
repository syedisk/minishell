/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/17 19:15:43 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	handle_echo(t_token *args, t_env *env_list)
{
	int		newline;
	char	*expanded;

	newline = 0;
	args = args->next;
	while (args && args->type == WORD && is_n_flag(args->value))
	{
		newline = 1;
		args = args->next;
	}
	while (args && args->type == WORD)
	{
		if (args->quoted)
			printf("%s", args->value);
		else
		{
			expanded = expand_variables(args->value, env_list, g_last_exit_status);
			if (expanded)
			{
				printf("%s", expanded);
				free(expanded);
			}
		}
		if (args->next && args->next->type == WORD)
			printf(" ");
		args = args->next;
	}
	if (!newline)
		printf("\n");
	g_last_exit_status = 0;
	return (0);
}
