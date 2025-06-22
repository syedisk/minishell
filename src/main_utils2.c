/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:47:56 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/22 17:40:00 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_parse_context(t_parse_ctx *ctx, t_env **env_list,
		int *exit_value)
{
	static int	heredoc_id = 0;

	ctx->env_list = env_list;
	ctx->exit_value = exit_value;
	ctx->heredoc_id = &heredoc_id;
	ctx->syntax_error = 0;
}

static int	check_and_handle_syntax_error(t_token *tokens, t_parse_ctx *ctx,
		char *input, int *exit_value)
{
	if (ctx->syntax_error)
	{
		free_tokens(tokens);
		*exit_value = 2;
		free(input);
		return (1);
	}
	return (0);
}

static void	handle_empty_command(t_token *tokens, t_command *commands,
		char *input, int *exit_value)
{
	free_tokens(tokens);
	free_commands(commands);
	free(input);
	*exit_value = 0;
}

static void	cleanup_execution(char *input, t_token *tokens, t_command *commands,
		char **env_array)
{
	free(input);
	free_tokens(tokens);
	free_commands(commands);
	free_split(env_array);
}

int	process_and_execute(char *input, t_env **env_list, int *exit_value)
{
	t_token		*tokens;
	t_command	*commands;
	char		**env_array;
	t_parse_ctx	ctx;

	init_parse_context(&ctx, env_list, exit_value);
	tokens = tokenise(input, &ctx);
	if (check_and_handle_syntax_error(tokens, &ctx, input, exit_value))
		return (0);
	commands = parse_tokens(tokens, &ctx);
	if (!commands || is_command_empty(commands))
		return (handle_empty_command(tokens, commands, input, exit_value), 0);
	env_array = convert_env_to_array(*env_list);
	if (ft_strcmp(commands->argv[0], "exit") == 0)
	{
		*exit_value = handle_exit(commands->argv);
		cleanup_execution(input, tokens, commands, env_array);
		free_env_list(*env_list);
		exit (*exit_value);
	}
	execute_commands(commands, env_list, env_array, exit_value);
	cleanup_execution(input, tokens, commands, env_array);
	return (1);
}
