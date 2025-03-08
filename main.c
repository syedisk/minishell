/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:38:43 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/03/08 15:42:14 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	char	*args[4];

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break;
		if (ft_strncmp(input, "exit", 4) == 0 && input[4] == '\0')
		{
			free(input);
			break;
		}
		args[0] = "/bin/sh";
		args[1] = "-c";
		args[2] = input;
		args[3] = NULL;
		if (fork() == 0)
			execve(args[0], args, NULL);
		else
			wait(NULL);
		free(input);
	}
	return (0);
}
