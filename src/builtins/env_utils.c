/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:34:32 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/15 19:39:28 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include <stddef.h>

t_env	*create_env_node(char *env_str)
{
	t_env	*node;
	char	**split;

	split = ft_split(env_str, '=');
	if (!split)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(split[0]);
	if (split[1])
		node->value = ft_strdup(split[1]);
	else
		node->value = NULL;
	node->next = NULL;
	free(split[0]);
	if (split[1])
		free(split[1]);
	free(split);
	return (node);
}

t_env	*create_env_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
	return (head);
}

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*curr;
	t_env	*new_node;

	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
}

int	env_size(t_env *env)
{
	int count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**convert_env_to_array(t_env *env)
{
	int		size;
	char	**envp;
	char	*joined;
	int		i;

	size = env_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	i = 0;
	if (!envp)
		return (NULL); // need to print error message to stderr??
	while (env)
	{
		if (env->value)
		{
			joined = ft_strjoin_three(env->key, "=", env->value);
			envp[i++] = joined;
		}
		else
		{
			envp[i++] = ft_strdup(env->key); // CHECK export VAR with no value.
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}


void	free_env_list(t_env *env)
{
	t_env	*tmp;
	
	while (env)
	{
		tmp = env;
		free(env->key);
		free(env->value);
		env = env->next;
		free(tmp);
	}
}