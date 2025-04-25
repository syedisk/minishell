/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:28:53 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/25 16:18:45 by thkumara         ###   ########.fr       */
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

int	handle_echo(char **argv, t_env	*env_list)
{
	int	i;
	int	newline;
	char	*expanded;

	i = 1;
	newline = 0;
	while (argv[i] && is_n_flag(argv[i])) // supports multiple -n flags
	{
		newline = 1;
		i++;
	}
	while (argv[i])
	{
		expanded = expand_variables(argv[i], env_list, last_exit_status);
		if (expanded)
		{
			printf("%s", expanded);
			free(expanded);
		}
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!newline)
		printf("\n");
	last_exit_status = 0; // on success
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
				printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
			else
				printf("declare -x %s\n", curr->key); // does this match bash behaviour?
			curr = curr->next;
		}
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
	last_exit_status = 0; // on success
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
		last_exit_status = 1; // on error
		return ;
	}
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env_list;
	*env_list = new;
	last_exit_status = 0; // on success
}

int	handle_unset(char **args, t_env **env_list)
{
	if (!args[1])
	{
		printf("unset: not enough arguments\n"); // to check with bash
		last_exit_status = 1; // on error
		return (1);
	}
	ft_unset(args, env_list);
	last_exit_status = 0; // on success
	return (0);
}
