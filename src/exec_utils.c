/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:28:53 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/18 15:38:27 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n') // bash supports -nnnnnn
			return (0);
		i++;
	}
	return (1);
}

int	handle_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 0;
	while (argv[i] && is_n_flag(argv[i])) // supports multiple -n flags
	{
		newline = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!newline)
		printf("\n");
	return (0);
}

void	handle_export(char *arg)
{
	char	**value;
	char	**env;
	char	*existing_value;
	int		i;

	i = 0;
	if (!arg)
	{
		while (environ[i])
		{
			printf("declare -x %s\n", environ[i]);
			i++;
		}
		return ;
	}
	if (arg[0])
		env = ft_split(arg, ' ');
	else
		env = &arg;
	while (env[i])
	{
		value = ft_split(env[i], '=');
		i++;
	}
	if (!value || !value[1])
	{
		printf("export: invalid format, use KEY=VALUE %s\n", value[1]);
		return ;
	}
	i = 0;
	while (env[i])
	{
		existing_value = getenv(value[i]);
		if (existing_value)
			printf("Updating existing variable: %s=%s\n", value[i],
				existing_value);
		else
			printf("Creating new variable: %s=%s\n", value[i], value[i + 1]);
		handle_newenv(value[i], value[i + 1]);
		i++;
	}
	free(env);
	free(value);
	return ;
}

void	handle_unset(char *var)
{
	if (!var)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	ft_unsetenv(var);
}
