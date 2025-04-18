/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:28:53 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/18 19:15:46 by sbin-ham         ###   ########.fr       */
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

int	handle_export(char **argv, t_env **env_list)
{
	int		i;
	char	**key_value;

	if (!argv[1])
	{
		for (int j = 0; (*env_list) && (env_list[j]); j++) // change for to if, or use print_env_list?
			printf("declare -x %s=\"%s\"\n", env_list[j]->key, env_list[j]->value);
		return (0);
	}
	
	i = 1;
	while (argv[i])
	{
		key_value = ft_split(argv[i], '=');
		if (!key_value || !key_value[0]) // removed !key_value[1] ; VAR= is set to empty string. what about VAR without =?
		{
			printf("export: `%s': not a valid identifier\n", argv[i]);
			if (key_value)
				ft_free_split(key_value);
			i++;
			continue ;
		}

	// Debug
	if (get_env_value(*env_list, key_value[0]))
		printf("Updating: %s=%s\n", key_value[0], key_value[1]);
	else
		printf("Creating: %s=%s\n", key_value[0], key_value[1]);

	handle_newenv(env_list, key_value[0], key_value[1]);
	ft_free_split(key_value);
	i++;
	}
	return (0);
}

void	handle_newenv(t_env **env_list, char *key, char *value)
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

	// add new variable
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

void	handle_unset(char *var)
{
	if (!var)
	{
		printf("unset: not enough arguments\n");
		return ;
	}
	ft_unsetenv(var);
}
