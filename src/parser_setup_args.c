/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setup_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:30:22 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/22 15:10:38 by sbin-ham         ###   ########.fr       */
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
			count++;
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

static int	process_word(t_command *cmd, t_token *token, t_parse_ctx *ctx,
		int *argc)
{
	char	*arg;
	char	**split;
	int		i;

	if (!expand_word(token, *(ctx->env_list), ctx->exit_value, &arg))
		return (free_argv_on_fail(cmd->argv, *argc));
	if (!arg)
		return (1);
	if (token->quote_type == 0 && ft_strchr(arg, ' ')) // && *argc == 0)
	{
		split = ft_split(arg, ' ');
		free(arg);
		if (!split)
			return (free_argv_on_fail(cmd->argv, *argc));
		i = 0;
		while (split[i])
			cmd->argv[(*argc)++] = ft_strdup(split[i++]);
		free_split(split);
	}
	else
		cmd->argv[(*argc)++] = arg;
	return (1);
}

int	handle_redirection(t_command *cmd, t_token **curr, t_parse_ctx *ctx)
{
	if ((*curr)->type == REDIR_IN || (*curr)->type == REDIR_OUT
		|| (*curr)->type == APPEND)
		return (handle_file_redir(cmd, curr));
	if ((*curr)->type == HEREDOC)
		return (handle_heredoc(cmd, curr, ctx));
	return (1);
}

int	setup_args_and_redirects(t_command *cmd, t_token **curr, t_parse_ctx *ctx)
{
	int	argc;
	int	arg_count;

	argc = 0;
	arg_count = count_args(*curr);
	cmd->argv = malloc(sizeof(char *) * (arg_count + 10)); // to allocate dynamically
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
