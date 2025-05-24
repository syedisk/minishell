/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:38:43 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 19:51:24 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

char	**tokens_to_args(t_token *tokens)
{
	int		count;
	t_token	*tmp;
	char	**args;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
			count++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	tmp = tokens;
	count = 0;
	while (tmp)
	{
		if (tmp->type == WORD)
			args[count++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	args[count] = NULL;
	return (args);
}

int	handle_exit_if_null(char *input, t_env *env_list)
{
	if (!input)
	{
		printf("exit\n");
		free_env_list(env_list);
		exit(0);
	}
	return (1);
}

void	run_shell_loop(t_env **env_list, int *exit_value)
{
	char	*input;

	while (1)
	{
		set_signals();
		input = custom_readline("$minishell ");
		if (!handle_exit_if_null(input, *env_list))
			continue ;
		if (!handle_interrupt_signal(&input, exit_value))
			continue ;
		if (is_skippable_input(input))
			continue ;
		add_history(input);
		if (check_syntax_error(input))
		{
			free(input);
			continue ;
		}
		if (!process_and_execute(input, env_list, exit_value))
			continue ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	int		exit_value;

	(void)argc;
	(void)argv;
	exit_value = 0;
	env_list = create_env_list(envp);
	if (!env_list)
		return (printf("Error: Failed to create environment list\n"), 1);
	run_shell_loop(&env_list, &exit_value);
	return (free_env_list(env_list), 0);
}
