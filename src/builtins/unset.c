/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42singapor>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:40:22 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/16 21:16:04 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env_key(t_env **env, const char *key)
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
static void 	ft_unset(char **args, t_env **env)
{
	int	i = 1;

	while (args[i])
	{
		// Optional: check if the identifier is valid??
		unset_env_key(env, args[i]);
		i++;
	}
}
int	handle_unset(char **args, t_env **env_list)
{
	if (!args[1])
	{
		g_last_exit_status = 0; // on error
		return (0);
	}
	ft_unset(args, env_list);
	g_last_exit_status = 0; // on success
	return (0);
}