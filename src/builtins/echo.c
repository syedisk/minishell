/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/06/23 20:35:07 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo_arg(t_token *arg, t_env *env_list, int *exit_value)
{
	if (arg->quote_type == 1)
		handle_single_quote(arg);
	else
		handle_double_or_no_quote(arg, env_list, exit_value);
}

static void	process_echo_flags(t_token **curr, int *newline)
{
	t_token		*temp;

	temp = *curr;
	*newline = 0;
	while (temp && temp->type == WORD && is_n_flag(temp->value))
	{
		*newline = 1;
		temp = temp->next;
	}
	*curr = temp;
}

static void	process_echo_args(t_token *curr, t_env *env_list,
	int *exit_value, int *need_space)
{
	t_token	*temp;

	temp = curr;
	while (temp)
	{
		if (temp->type == REDIR_IN || temp->type == REDIR_OUT
			|| temp->type == APPEND || temp->type == HEREDOC)
		{
			temp = temp->next;
			if (temp)
				temp = temp->next;
			continue ;
		}
		if (temp->type == WORD)
		{
			if (*need_space)
				printf(" ");
			print_echo_arg(temp, env_list, exit_value);
			*need_space = 1;
		}
		temp = temp->next;
	}
}

static t_token	*skip_to_echo_args(t_token *curr)
{
	while (curr)
	{
		if (curr->type == REDIR_IN || curr->type == REDIR_OUT
			|| curr->type == APPEND || curr->type == HEREDOC)
		{
			curr = curr->next;
			if (curr)
				curr = curr->next;
			continue ;
		}
		if (curr->type == WORD && ft_strcmp(curr->value, "echo") == 0)
		{
			return (curr->next);
		}
		curr = curr->next;
	}
	return (NULL);
}

int	handle_echo(t_command *cmd, t_env *env_list, int *exit_value)
{
	int		newline;
	int		need_space;
	t_token	*curr;

	need_space = 0;
	curr = skip_to_echo_args(cmd->raw_tokens);
	process_echo_flags(&curr, &newline);
	process_echo_args(curr, env_list, exit_value, &need_space);
	if (!newline)
		printf("\n");
	return (0);
}
