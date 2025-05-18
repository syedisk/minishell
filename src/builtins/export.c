/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:10:24 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/18 19:31:31 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_valid_identifier(const char *key)
{
	int i = 0;

	if (!key || !key[0])
		return 0;
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return 0;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return 0;
		i++;
	}
	return 1;
}

static void	handle_newenv(t_env **env_list, char *key, char *value)
{
	// printf("key is %s\n", key);
	t_env *curr = *env_list;

	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value =  ft_strdup(value);
			error_msg("export_fail");
			return;
		}
		curr = curr->next;
	}
	t_env *new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("malloc");
		return ;
	}
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env_list;
	*env_list = new;
}

static int check_exportvalue(char **argv)
{
	int	i;
	char **key_value;
	
	i = 1;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '='))
		{
			key_value = ft_split(argv[i], '=');
			if (!key_value || !key_value[0] || !is_valid_identifier(key_value[0]))
			{
				if (key_value)
					ft_free_split(key_value);
				error_msg("export_fail");
				return (1);
			}
			ft_free_split(key_value);
		}
		else
		{
			if (!is_valid_identifier(argv[i]))
			{
				error_msg("export_fail");
				return (1);
			}
		}
		i++;
	}
	return 0;
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
	i = 1;
	while (argv[i])
	{
		// printf("argv[i] is %s\n", argv[i]);
		if (!ft_strchr(argv[i], '='))
		{
			i++;
			continue ;
		}
		// printf("argv[i] is %s\n", argv[i]);
		key_value = ft_split(argv[i], '=');
		// printf("key_value[0] is %s\n", key_value[0]);
		if (!key_value || !key_value[0])
		{
			if (key_value)
				ft_free_split(key_value);
			i++; 
			continue ;
		}
	handle_newenv(env_list, key_value[0], key_value[1]);
	ft_free_split(key_value);
	i++;
	}
	return (0);
}
