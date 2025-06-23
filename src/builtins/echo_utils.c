/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:46:36 by thkumara          #+#    #+#             */
/*   Updated: 2025/06/23 20:35:02 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_flag(char *str)
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

static void	handle_unquoted(const char *value, t_env *env_list, int *exit_value)
{
	char	*stripped;
	char	*expanded;
	char	**words;
	int		i;

	stripped = strip_inner_quotes(value);
	if (!stripped)
		return ;
	expanded = expand_variables(stripped, env_list, exit_value);
	free(stripped);
	if (!expanded)
		return ;
	words = ft_split(expanded, ' ');
	free(expanded);
	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		if (i > 0)
			printf(" ");
		printf("%s", words[i]);
		i++;
	}
	free_split(words);
}

void	handle_double_or_no_quote(t_token *arg, t_env *env_list,
	int *exit_value)
{
	char	*expanded;

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
		handle_unquoted(arg->value, env_list, exit_value);
}
