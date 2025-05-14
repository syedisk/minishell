/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:10:24 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/14 18:14:07 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_newenv(t_env **env_list, char *key, char *value)
{
	t_env *curr = *env_list;

	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value =  ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	t_env *new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("malloc");
		last_exit_status = 1;
		return ;
	}
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env_list;
	*env_list = new;
	last_exit_status = 0;
}

static int check_exportvalue(char **argv)
{
	int	i;
	
	i = 1;
	while (argv[i])
	{
		if (!(ft_strchr(argv[i], '=')))
		{
			i++;
			error_msg("export_fail");
			continue;
		}
		if (ft_strchr(argv[i], '-') || ft_strchr(argv[i], '+') || ft_strchr(argv[i], ' '))
		{
			error_msg("export_fail");
			last_exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_export(char **argv, t_env **env_list)
{
	int		i;
	char	**key_value;
	t_env	*curr;

	curr = *env_list;
	if (!argv[1])
	{
		while (curr)
		{
			if (curr->value)
				printf("declare -x %s=\"%s\"\n", curr->key, curr->value); //Check with bash
			else
				printf("declare -x %s\n", curr->key);
			curr = curr->next;
		}
		return (0);
	}
	if (check_exportvalue(argv) != 0)
		return (1);
	else
        return (0);
	i = 1;
	while (argv[i])
	{
		key_value = ft_split(argv[i], '=');

		if (!key_value || !key_value[0] || !key_value[1])
		{
			printf("export: `%s': not a valid identifier\n", argv[i]);
			if (key_value)
				ft_free_split(key_value);
			i++; 
			return (1);
		}
	handle_newenv(env_list, key_value[0], key_value[1]);
	ft_free_split(key_value);
	i++;
	}
	last_exit_status = 0;
	return (0);
}
