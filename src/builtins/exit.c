/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:30:30 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/19 17:34:37 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_value(char *arg)
{
	if (!ft_atoi(arg))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
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
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit(2);
		}
		i++;
	}
	if (!argv[2])
		handle_exit_value(argv[1]);
	if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}
