/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:13:56 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/08 18:33:48 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int last_exit_status;

static int cd_to_home(char **argv)
{
	char *home;
	char *new_path;

	home = getenv("HOME");
	if (!home)
	{
		write(2, "cd: HOME not set\n", 17);
		last_exit_status = 1;
		return (1);
	}
	new_path = malloc(strlen(home) + strlen(argv[1]) + 1);
	if (!new_path)
		return (1);
	strcpy(new_path, home);
	strcat(new_path, argv[1] + 1);
	if (chdir(new_path) != 0)
	{
		perror("cd");
		free(new_path);
		last_exit_status = 1;
		return (1);
	}
	free(new_path);
	return (0);
}

static int handle_cd(char **argv)
{
	if (!argv[1])
	{
		write(2, "cd: Argument missing\n", 21);
		last_exit_status = 1;
		return (1);
	}
	if (ft_strcmp(argv[1], "~") == 0)
		return (cd_to_home(argv));
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		last_exit_status = 1;
		return (1);
	}
	last_exit_status = 0;
	return (0);
}

static int handle_exit_value(char *arg)
{
	if (!ft_atoi_long(arg))
	{
		printf("exit: %s: numeric argument required\n", arg);
		exit(2);
	}
	exit(ft_atoi(arg));
}

static int handle_exit(char **argv)
{
	int i;

	printf("exit\n");
	if (!argv[1])
		exit(0);
	i = 0;
	while (argv[1][i])
	{
		if (ft_isalpha(argv[1][i]))
		{
			printf("exit: %s: numeric argument required\n", argv[1]);
			exit(2);
		}
		i++;
	}
	if (!argv[2])
		handle_exit_value(argv[1]);
	if (argv[2])
	{
		printf("exit: too many arguments\n");
		last_exit_status = 1;
		return (1);
	}
	return (0);
}

int execute_builtin(t_command *cmd, t_env **env_list)
{
	if (!cmd || !cmd->argv[0])
		return (0);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (handle_cd(cmd->argv));
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (handle_pwd());
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		return (handle_echo(cmd->argv, *env_list));
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (handle_export(cmd->argv, env_list));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (handle_unset(cmd->argv, env_list));
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (ft_env(*env_list));
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (handle_exit(cmd->argv));
	return (0);
}
