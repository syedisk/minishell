/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:28:52 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 19:37:01 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_braced_variable(char **line, char **result, t_env *env_list)
{
	const char		*start;
	char			*temp;
	char			*value;

	(*line)++;
	start = *line;
	while (**line && **line != '}')
		(*line)++;
	temp = ft_substr(start, 0, *line - start);
	value = get_env_value(env_list, temp);
	if (value)
		*result = ft_strjoin_free(*result, value);
	free(temp);
	if (**line == '}')
		(*line)++;
}

void	handle_simple_variable(char **line, char **result, t_env *env_list)
{
	const char		*start;
	char			*temp;
	char			*value;

	start = *line;
	while (**line && (ft_isalnum(**line) || **line == '_'))
		(*line)++;
	temp = ft_substr(start, 0, *line - start);
	value = get_env_value(env_list, temp);
	if (value)
		*result = ft_strjoin_free(*result, value);
	else
		*result = ft_strjoin_free(*result, "");
	free(temp);
}

void	handle_exit_code(char **result, int *exit_value)
{
	char	*temp;
	int		sig;
	int		status;

	sig = g_sig_received;
	status = *exit_value;
	if (sig == 131 || sig == 130)
	{
		temp = ft_itoa(sig);
		*result = ft_strjoin_free(*result, temp);
		free(temp);
	}
	temp = ft_itoa(status);
	*result = ft_strjoin_free(*result, temp);
	free(temp);
}

void	handle_dollar(char **line, char **result, t_env *env_list,
	int *exit_value)
{
	(*line)++;
	if (**line == '?')
	{
		handle_exit_code(result, exit_value);
		(*line)++;
	}
	else if (**line == '{')
		handle_braced_variable(line, result, env_list);
	else if (ft_isalpha(**line) || **line == '_')
		handle_simple_variable(line, result, env_list);
	else
		*result = ft_strjoin_char(*result, '$');
}

char	*expand_variables(char *line, t_env *env_list, int *exit_value)
{
	char			*result;

	result = ft_strdup("");
	while (*line)
	{
		if (*line == '$')
			handle_dollar(&line, &result, env_list, exit_value);
		else
		{
			result = ft_strjoin_char(result, *line);
			line++;
		}
	}
	return (result);
}
