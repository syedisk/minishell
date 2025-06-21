/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42singapor>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:30:30 by thkumara          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/21 23:21:40 by thkumara         ###   ########.fr       */
=======
/*   Updated: 2025/06/21 22:09:22 by thkumara         ###   ########.fr       */
>>>>>>> 5b9f1f655f599a548d38380c8e7938bde31e71c5
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
<<<<<<< HEAD
		return (0);
=======
		return(0);
>>>>>>> 5b9f1f655f599a548d38380c8e7938bde31e71c5
	while (argv[1][i])
	{
		if (ft_isalpha(argv[1][i]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
<<<<<<< HEAD
			return (2);
=======
			return(2);
>>>>>>> 5b9f1f655f599a548d38380c8e7938bde31e71c5
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
