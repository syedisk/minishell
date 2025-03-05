/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:38:43 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/03/05 17:58:16 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;
	char	*args[4];

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break;
		if (strcmp(input, "exit") == 0)
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
