/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:10:24 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/15 17:25:58 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_export_format(const char *str)
{
	int	i = 0;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **args, t_env **env)
{
	int		i;
	char	**kv;

	i = 1;
	if (!args[1])
	{
		t_env *curr = *env;
		while (curr)
		{
			if (curr->value)
				printf("declare -x %s=\"%s\"\n", curr->key, curr->value);
			else
				printf("declare -x %s\n", curr->key);
			curr = curr->next;
		}
		return ;
	}
	while (args[i])
	{
		if (!is_valid_export_format(args[i]))
		{
			printf("export: `%s`: not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
		kv = ft_split(args[i], '=');
		if (!kv)
			return ;
		set_env_value(env, kv[0], kv[1]);
		free(kv[0]);
		if (kv[1])
			free(kv[1]);
		free(kv);
		i++;
	}
}
