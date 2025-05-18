/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:30:30 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/18 12:41:54 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_value(char *arg)
{
	if (!ft_atoi_long(arg))
	{
		error_msg("exit_arg");
		exit(156);
	}
	exit(ft_atoi(arg));
}

int	handle_exit(char **argv)
{
	int		i;

	i = 0;
	printf("exit\n");
	if (!argv[1])
		exit(0);
	while (argv[1][i])
	{
		if (ft_isalpha(argv[1][i]))
		{
			error_msg("exit_arg");
			exit(2);
		}
		i++;
	}
	if (!argv[2])
		handle_exit_value(argv[1]);
	if (argv[2])
	{
		error_msg("exit_too_many_arg");
		return (1);
	}
	return (0);
}
