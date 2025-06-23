/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:47:56 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/23 19:54:06 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	cleanup_execution(char *input, t_command *commands,
		char **env_array)
{
	free(input);
	free_commands(commands);
	free_split(env_array);
}

static int	handle_exit_command(t_command *cmd, t_env **env_list,
	char *input, char **env_array)
{
	int	exit_code;

	exit_code = handle_exit(cmd->argv);
	cleanup_execution(input, cmd, env_array);
	free_env_list(*env_list);
	exit(exit_code);
}

int	process_and_execute(char *input, t_env **env_list, int *exit_value)
{
	t_token		*tokens;
	t_command	*cmd;
	char		**env_array;
	t_parse_ctx	ctx;

	init_parse_context(&ctx, env_list, exit_value);
	tokens = tokenise(input, &ctx);
	if (check_and_handle_syntax_error(tokens, &ctx, input, exit_value))
		return (0);
	cmd = parse_tokens(tokens, &ctx);
	if (!cmd)
	{
		free_tokens(tokens);
		return (0);
	}
	if (is_command_empty(cmd))
		return (handle_empty_command(tokens, cmd, input, exit_value), 0);
	env_array = convert_env_to_array(*env_list);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		handle_exit_command(cmd, env_list, input, env_array);
	free_tokens(tokens);
	execute_commands(cmd, env_list, env_array, exit_value);
	cleanup_execution(input, cmd, env_array);
	return (1);
}
