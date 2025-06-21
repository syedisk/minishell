/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42singapor>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:30:30 by thkumara          #+#    #+#             */
/*   Updated: 2025/06/21 23:29:31 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_value(char *arg)
{
	if (!ft_atoi(arg))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (156);
	}
	return (ft_atoi(arg));
}

int	handle_exit(char **argv)
{
	int		i;

	i = 0;
	printf("exit\n");
	if (!argv[1])
		return (0);
	while (argv[1][i])
	{
		if (ft_isalpha(argv[1][i]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			return (2);
		}
		i++;
	}
	if (!argv[2])
		return (handle_exit_value(argv[1]));
	if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}
