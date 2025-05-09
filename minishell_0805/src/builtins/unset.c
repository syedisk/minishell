/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:40:22 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/15 17:46:49 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env_key(t_env **env, const char *key)
{
	t_env	*curr = *env;
	t_env	*prev = NULL;

	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;

			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
void	ft_unset(char **args, t_env **env)
{
	int	i = 1;

	while (args[i])
	{
		// Optional: check if the identifier is valid??
		unset_env_key(env, args[i]);
		i++;
	}
}
