/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setup_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:30:22 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/23 20:22:09 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			if (token->quote_type == 0 && ft_strchr(token->value, '$'))
				count += 4;
			else
				count++;
		}
		else if (token->type == REDIR_IN || token->type == REDIR_OUT
			|| token->type == APPEND)
			token = token->next;
		token = token->next;
	}
	return (count);
}

static int	free_argv_on_fail(char **argv, int count)
{
	while (--count >= 0)
		free(argv[count]);
	free(argv);
	return (0);
}

static int	add_split_words(t_command *cmd, char **split, int *argc)
{
	int	i;

	i = 0;
	while (split[i])
	{
		cmd->argv[*argc] = ft_strdup(split[i]);
		if (!cmd->argv[*argc])
		{
			free_split(split);
			return (free_argv_on_fail(cmd->argv, *argc));
		}
		(*argc)++;
		i++;
	}
	free_split(split);
	return (1);
}

static int	process_word(t_command *cmd, t_token *token, t_parse_ctx *ctx,
		int *argc)
{
	char	*arg;
	char	**split;

	if (!expand_word(token, *(ctx->env_list), ctx->exit_value, &arg))
		return (free(arg), free_argv_on_fail(cmd->argv, *argc));
	if (!arg)
		return (1);
	if (token->quote_type == 0 && ft_strchr(arg, ' '))
	{
		split = ft_split(arg, ' ');
		free(arg);
		if (!split)
			return (free_argv_on_fail(cmd->argv, *argc));
		return (add_split_words(cmd, split, argc));
	}
	cmd->argv[*argc] = arg;
	(*argc)++;
	return (1);
}

int	setup_args_and_redirects(t_command *cmd, t_token **curr, t_parse_ctx *ctx)
{
	int	argc;
	int	arg_count;

	argc = 0;
	arg_count = count_args(*curr);
	cmd->argv = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->argv)
		return (0);
	while (*curr && (*curr)->type != PIPE)
	{
		if ((*curr)->type == WORD)
		{
			if (!process_word(cmd, *curr, ctx, &argc))
				return (0);
		}
		else if (!handle_redirection(cmd, curr, ctx))
			return (free_argv_on_fail(cmd->argv, argc));
		else
			continue ;
		*curr = (*curr)->next;
	}
	cmd->argv[argc] = NULL;
	return (1);
}
