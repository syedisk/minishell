/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:38:43 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 11:15:51 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

volatile sig_atomic_t g_sig_received = 0;

static int is_readline_active = 0;

char **tokens_to_args(t_token *tokens)
{
	int	count = 0;
	t_token *tmp = tokens;
	char **args;

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

void	debug_print_env_list(t_env *env) //debugger to delete
{
	printf("\n--- ENVIRONMENT DEBUG ---\n");
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		else
			printf("%s (no value)\n", env->key);
		env = env->next;
	}
	printf("--- END ENV ---\n\n");
}



int readline_active_state(void)
{
    return is_readline_active;
}

char *custom_readline(const char *prompt)
{
    is_readline_active = 1;
    char *line = readline(prompt);
    is_readline_active = 0;
	if (!line)
        return NULL;
    return line;
}

static int is_only_whitespace(const char *str)
{
    while (*str)
    {
        if (!ft_isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
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

int	handle_interrupt_signal(char **input, int *exit_value)
{
	if (g_sig_received == 130)
	{
		*exit_value = 130;
		g_sig_received = 0;
		if (**input == '\0')
		{
			free(*input);
			return (0);
		}
	}
	return (1);
}

int	is_skippable_input(char *input)
{
	if (*input == '\0' || is_only_whitespace(input))
	{
		free(input);
		return (1);
	}
	return (0);
}

int	is_command_empty(t_command *cmd)
{
	return (!cmd || !cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0');
}

int	process_and_execute(char *input, t_env **env_list, int *exit_value)
{
	t_token		*tokens;
	t_command	*commands;
	char		**env_array;

	tokens = tokenise(input);
	commands = parse_tokens(tokens, *env_list, exit_value);

	if (!commands || is_command_empty(commands))
	{
		free_tokens(tokens);
		free_commands(commands);
		free(input);
		*exit_value = 0;
		return (0);
	}
	env_array = convert_env_to_array(*env_list);
	execute_commands(commands, env_list, env_array, exit_value);

	free(input);
	free_tokens(tokens);
	free_commands(commands);
	free_split(env_array);
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
			continue;
		if (!handle_interrupt_signal(&input, exit_value))
			continue;
		if (is_skippable_input(input))
			continue;
		add_history(input);
		if (check_syntax_error(input))
		{
			free(input);
			continue;
		}
		if (!process_and_execute(input, env_list, exit_value))
			continue;
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
