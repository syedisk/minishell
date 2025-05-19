/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:25:35 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/19 19:48:01 by thkumara         ###   ########.fr       */
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

static char	*strip_inner_quotes(const char *str)
{
	char	*result;
	int		i = 0;
	int		j = 0;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}


int	handle_echo(t_token *args, t_env *env_list, int *exit_value)
{
	int		newline;
	char	*expanded;
	int		need_space = 0;

	newline = 0;
	args = args->next;
	while (args && args->type == WORD && is_n_flag(args->value))
	{
		newline = 1;
		args = args->next;
	}
	while (args)
	{
		if (args->type == REDIR_IN || args->type == REDIR_OUT
			|| args->type == APPEND || args->type == HEREDOC)
		{
			args = args->next;
			if (args)
				args = args->next;
			continue ;
		}
		else if (args->type == WORD)
		{
			if (need_space)
				printf(" ");
			if (args->quote_type == 1)
				printf("%s", args->value);
			else if (args->quote_type == 2)
			{
				expanded = expand_variables(args->value, env_list, exit_value);
				if (expanded)
				{
					printf("%s", expanded);
					free(expanded);
				}
			}
			else
			{
				char *stripped = strip_inner_quotes(args->value);
				expanded = expand_variables(stripped, env_list, exit_value);
				free(stripped);
				if (expanded)
				{
					printf("%s", expanded);
					free(expanded);
				}
			}
			need_space = 1;
		}
		args = args->next;
	}
	if (!newline)
		printf("\n");
	exit_value = 0;
	return (0);
}
