/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:46:36 by thkumara          #+#    #+#             */
/*   Updated: 2025/06/22 14:39:41 by sbin-ham         ###   ########.fr       */
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
	char	**words;
	int		i;

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
}
