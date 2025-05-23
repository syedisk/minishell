/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:46:36 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/23 19:36:25 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_inner_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
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

void	handle_single_quote(t_token *arg)
{
	char	*value;

	value = arg->value;
	printf("%s", value);
}

void	handle_double_or_no_quote(t_token *arg, t_env *env_list,
	int *exit_value)
{
	char	*expanded;
	char	*stripped;

	if (arg->quote_type == 2)
	{
		expanded = expand_variables(arg->value, env_list, exit_value);
		if (expanded)
		{
			printf("%s", expanded);
			free(expanded);
		}
	}
	else
	{
		stripped = strip_inner_quotes(arg->value);
		expanded = expand_variables(stripped, env_list, exit_value);
		free(stripped);
		if (expanded)
		{
			printf("%s", expanded);
			free(expanded);
		}
	}
}
