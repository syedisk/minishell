/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:10:24 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/20 15:05:51 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *key)
{
	int	i;

	i = 0;
	if (!key || !key[0])
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	handle_newenv(t_env **env_list, char *key, char *value)
{
	t_env	*curr;
	t_env	*new;

	curr = *env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free (curr->value);
			curr->value = ft_strdup(value);
			ft_putstr_fd(" not a valid identifier\n", 2);
			return ;
		}
		curr = curr->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
	{
		ft_putstr_fd(" malloc failed\n", 2);
		return ;
	}
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env_list;
	*env_list = new;
}
