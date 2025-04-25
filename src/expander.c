/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:28:52 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/25 16:25:48 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"
#include "minishell.h"

// char	*expand_variables(char *str, char **envp)
// {
// 	char	*varname;
// 	int		i;

// 	if (!str || str[0] != '$')
// 		return (ft_strdup(str));
// 	varname = str + 1;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], varname, ft_strlen(varname)) == 0
// 			&& envp[i][ft_strlen(varname)] == '=') // in case there's USER= and USERNAME=
// 		{
// 			return (ft_strdup(envp[i] + ft_strlen(varname) + 1));
// 		}
// 		i++;
// 	}
// 	return (ft_strdup("")); // not found, empty string
// }

char *ft_strjoin_free(char *s1, const char *s2)
{
	char *joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return joined;
}
char *ft_strjoin_char(char *s, char c)
{
	char str[2] = {c, '\0'};
	return ft_strjoin_free(s, str);
}

char *expand_variables(char *line, t_env *env_list, int last_exit_status)
{
	char	*result = ft_strdup(""); // start with empty string
	char	*temp;
	char	*var_name;
	char	*value;
	const char *start;

	while (*line)
	{
		if (*line == '$')
		{
			line++;
			if (*line == '?') // handle $?
			{
				temp = ft_itoa(last_exit_status);
				result = ft_strjoin_free(result, temp);
				free(temp);
				line++;
			}
			else if (*line == '{') // handle ${VAR}
			{
				line++;
				start = line;
				while (*line && *line != '}')
					line++;
				var_name = ft_substr(start, 0, line - start);
				value = get_env_value(env_list, var_name);
				result = ft_strjoin_free(result, value);
				free(var_name);
				if (*line == '}')
					line++; // skip closing brace
			}
			else if (ft_isalpha(*line) || *line == '_') // handle $VAR
			{
				start = line;
				while (*line && (ft_isalnum(*line) || *line == '_'))
					line++;
				var_name = ft_substr(start, 0, line - start);
				value = get_env_value(env_list, var_name);
				result = ft_strjoin_free(result, value);
				free(var_name);
			}
			else
			{
				// Just a lone $, treat literally
				result = ft_strjoin_char(result, '$');
			}
		}
		else
		{
			result = ft_strjoin_char(result, *line);
			line++;
		}
	}
	return result;
}