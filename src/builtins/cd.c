/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:20:23 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/14 18:48:21 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_to_home(char **argv)
{
	char	*home;
	char	*new_path;

	home = getenv("HOME");
	if (!home)
	{
		write(2, "cd: HOME not set\n", 17);
		last_exit_status = 1;
		return (1);
	}
	new_path = malloc(strlen(home) + ft_strlen(argv[1]) + 1);
	if (!new_path)
		return (1);
	ft_strcpy(new_path, home);
	ft_strcat(new_path, argv[1] + 1);
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

int	handle_cd(char **argv)
{
	if (!argv[1])
	{
		write(2, "cd: Argument missing\n", 21);
		last_exit_status = 1;
		return (1);
	}
	if (argv[2])
	{
		write(2, "cd: too many arguments\n", 23);
		last_exit_status = 1;
		return (1);
	}
	if (ft_strcmp(argv[1], "ft_strcat~") == 0)
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
