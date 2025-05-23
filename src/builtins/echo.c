/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/23 19:35:53 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

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
	int *exit_value, int need_space)
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
			if (need_space)
				printf(" ");
			if (ft_strcmp(temp->value, "echo") == 0)
				temp = temp->next;
			print_echo_arg(temp, env_list, exit_value);
			need_space = 1;
		}
		temp = temp->next;
	}
}

int	handle_echo(t_token *args, t_env *env_list, int *exit_value)
{
	int		newline;
	int		need_space;
	t_token	*curr;

	need_space = 0;
	curr = args->next;
	process_echo_flags(&curr, &newline);
	process_echo_args(curr, env_list, exit_value, need_space);
	if (!newline)
		printf("\n");
	exit_value = 0;
	return (0);
}
