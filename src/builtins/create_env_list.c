/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:34:32 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/20 14:40:16 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

static t_env	*allocate_env_node(char **split)
{
	t_env	*node;
	char	*key;
	char	*value;

	node = malloc(sizeof(t_env));
	if (!node)
		return (free_split(split), NULL);
	key = ft_strdup(split[0]);
	if (!key)
	{
		free(node);
		return (free_split(split), NULL);
	}
	value = NULL;
	if (split[1])
		value = ft_strdup(split[1]);
	if (split[1] && !value)
	{
		free(key);
		return (free(node), free_split(split), NULL);
	}
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*create_env_node(char *env_str, char *sep)
{
	t_env	*node;
	char	**split;
	char	*key;

	split = ft_split(env_str, '=');
	if (!split)
		return (NULL);
	if (sep)
	{
		*sep = '\0';
		key = ft_strdup(env_str);
		node = allocate_env_node((char *[]){key, sep + 1, NULL});
		*sep = '=';
		free(key);
	}
	else
		node = allocate_env_node(split);
	free_split(split);
	return (node);
}

t_env	*create_env_list(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	char	*sep;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		sep = ft_strchr(envp[i], '=');
		new_node = create_env_node(envp[i], sep);
		if (!new_node)
			return (free_env_list(head), NULL);
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
	return (head);
}

static	char	**env_new(t_env *env)
{
	int		count;
	char	**envp;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	return (envp);
}

char	**convert_env_to_array(t_env *env)
{
	char	**envp;
	char	*joined;
	int		i;

	envp = env_new(env);
	i = 0;
	while (env)
	{
		if (env->value)
			joined = ft_strjoin_three(env->key, "=", env->value);
		else
			joined = ft_strdup(env->key);
		if (!joined)
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		envp[i++] = joined;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
