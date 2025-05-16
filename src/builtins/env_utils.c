/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42singapor>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:34:32 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/16 23:12:24 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

t_env	*create_env_node(char *env_str, char *sep)
{
	t_env	*node;
	char	**split;
	
	split = ft_split(env_str, '=');
	if (!split)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (!node)
        return (free(split), NULL);
	if (sep)
		{
			*sep = '\0'; // Temporarily split key and value
			node->key = ft_strdup(env_str);       // Before '='
			node->value = ft_strdup(sep + 1);     // After '='
			*sep = '='; // Restore original string
		}
	else
	{
		node->key = ft_strdup(split[0]);
		if (!node->key)
		{
			free(node);
			return (free(split), NULL);
		}
		if (split[1])
			node->value = ft_strdup(split[1]);
		else
			node->value = NULL;
	}
	if (split[1] && !node->value)
	{
		free(node->key);
		free(node);
		return (free(split), NULL);
	}
	node->next = NULL;
	return (free(split), node);
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
        {
            free_env_list(head);
            return (NULL);
        }
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
static void	update_env_value(t_env *curr, const char *key, const char *value)
{
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			char *new_value = ft_strdup(value);
			if (!new_value)
			{
				free(curr->key);
				free(curr);
				printf("Error: Memory allocation failed in set_env_value\n");
				exit(1);
			}
			free(curr->value);
			curr->value = new_value;
			return ;
		}
		curr = curr->next;
	}
}

static void	add_env_var(t_env **env, const char *key, const char *value)
{
	t_env *new_node;
	char *dup_key;
	char *dup_value;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	dup_key = ft_strdup(key);
	if (!dup_key)
	{
		free(new_node);
		return ;
	}
	dup_value = ft_strdup(value);
	if (!dup_value)
	{
		free(dup_key);
		free(new_node);
		return ;
	}
	new_node->key = dup_key;
	new_node->value = dup_value;
	new_node->next = *env;
	*env = new_node;
}
void	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env *curr;

	curr = *env;
	update_env_value(curr, key, value);

	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return ;
		curr = curr->next;
	}
	add_env_var(env, key, value);
}
// void	set_env_value(t_env **env, const char *key, const char *value)
// {
// 	t_env	*curr;
// 	t_env	*new_node;

// 	curr = *env;
// 	while (curr)
// 	{
// 		if (ft_strcmp(curr->key, key) == 0)
// 		{
// 			free(curr->value);
// 			curr->value = ft_strdup(value);
// 			if (!curr->value)
// 			{
// 				free(curr->key);
// 				free(curr);
// 				printf("Error: Memory allocation failed in set_env_value\n");
// 				exit(1);
// 			}
// 			return ;
// 		}
// 		curr = curr->next;
// 	}
// 	new_node = malloc(sizeof(t_env));
// 	if (!new_node)
// 		return ;
// 	new_node->key = ft_strdup(key);
// 	if (!new_node->key)
//     {
//         free(new_node);
//         return;
//     }
// 	new_node->value = ft_strdup(value);
// 	if (!new_node->value)
//     {
//         free(new_node->key);
//         free(new_node);
//         return;
//     }
// 	new_node->next = *env;
// 	*env = new_node;
// }

static char **env_new(t_env *env)
{
	int count;
	char **envp;
	
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
