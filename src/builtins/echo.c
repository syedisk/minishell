/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/15 14:30:22 by thkumara         ###   ########.fr       */
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

int	handle_echo(char **argv, t_env	*env_list)
{
	int		i;
	int		newline;
	char	*expanded;

	i = 1;
	newline = 0;
	while (argv[i] && is_n_flag(argv[i]))
	{
		newline = 1;
		i++;
	}
	while (argv[i])
	{
		expanded = expand_variables(argv[i], env_list, last_exit_status);
		if (expanded)
		{
			printf("%s", expanded);
			free(expanded);
		}
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!newline)
		printf("\n");
	last_exit_status = 0;
	return (0);
}
