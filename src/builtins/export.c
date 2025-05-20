/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:00:38 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/20 15:06:32 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exportvalue(char **argv)
{
	int		i;
	char	**key_value;

	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			key_value = ft_split(argv[i], '=');
			if (!key_value || !key_value[0] || !key_value[0][0]
				|| !is_valid_identifier(key_value[0]))
			{
				free_split(key_value);
				return (ft_putstr_fd(" not a valid identifier\n", 2), 1);
			}
			free_split(key_value);
		}
		else
		{
			if (!is_valid_identifier(argv[i]))
				return (ft_putstr_fd(" not a valid identifier\n", 2), 1);
		}
		i++;
	}
	return (0);
}

static void	print_exported_variables(t_env *env_list)
{
	t_env	*curr;
	int		i;

	curr = env_list;
	i = 0;
	while (curr)
	{
		if (curr->value)
			printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
		else
			printf("declare -x %s\n", curr->key);
		curr = curr->next;
		i++;
	}
}

static void	process_export_arguments(char **argv, t_env **env_list)
{
	int		i;
	char	**key_value;

	i = 1;
	while (argv[i])
	{
		if (!ft_strchr(argv[i], '='))
		{
			i++;
			continue ;
		}
		key_value = ft_split(argv[i], '=');
		if (!key_value || !key_value[0])
		{
			if (key_value)
				free_split(key_value);
			i++;
			continue ;
		}
		handle_newenv(env_list, key_value[0], key_value[1]);
		free_split(key_value);
		i++;
	}
}

int	handle_export(char **argv, t_env **env_list)
{
	if (!argv[1])
	{
		print_exported_variables(*env_list);
		return (0);
	}
	if (check_exportvalue(argv) != 0)
		return (1);
	process_export_arguments(argv, env_list);
	return (0);
}
