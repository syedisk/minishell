/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:22:32 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/17 16:58:47 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free the args array
void free_args(char **args)
{
    int i = 0;

    if (!args)
        return;
    while (args[i])
    {
        free(args[i]); // Free each argument
        i++;
    }
    free(args); // Free the array itself
}

void free_tokens(t_token *tokens)
{
	t_token *tmp;
	
	while (tokens)
	{
		tmp = tokens->next;
		if(tokens->value)
			free(tokens->value); // Free the token value
		free(tokens);   // Free the token node
		tokens = tmp;
	}
}

void	free_commands(t_command *cmds)
{
	int			i;
	t_command	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		if (cmds->argv)
		{
			i = 0;
			while (cmds->argv[i])
			{
				free(cmds->argv[i]);
				i++;
			}
			free(cmds->argv);
		}
		if (cmds->infile)
			free(cmds->infile);
		if (cmds->outfile)
			free(cmds->outfile);
		if (cmds->raw_tokens)
			free_tokens(cmds->raw_tokens);
		free(cmds);
		cmds = tmp;
	}
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