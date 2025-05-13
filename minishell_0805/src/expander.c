/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42singapor>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:28:52 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/12 20:58:41 by thkumara         ###   ########.fr       */
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

	if (!s1 || s1 == ft_strdup("")) // if s1 is null
		return (ft_strdup(s2));
	joined = ft_strjoin(s1, s2);
	free(s1);
	return joined;
}
char *ft_strjoin_char(char *s, char c)
{
	if (!s)
		return (ft_strdup(&c)); // if s is null, return c as string
    if (c == '\0') // if c is null character
        return s;  // don't add anything, just return s
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
	char    pos_quote = 0;

	while (*line)
	{
		if (*line == '\'') // handle ''
		{
			if (*line == '\'' && *(line + 1) == '\'') // empty single quotes
			{
				line += 2; // Skip over the two single quotes
			}
			if (*line == '\'' || *line == '"') // Handle quotes
			{
				if (pos_quote == 0) // Start of a quoted section
					pos_quote = *line;
				else if (pos_quote == *line) // End of the quoted section
					pos_quote = 0;
				else
					result = ft_strjoin_char(result, *line); // Append the quote if inside another quote
				line++;
			}
			else if (*line == '$' && pos_quote != '\'') // Handle variable expansion (skip if inside single quotes)
			{
				line++;
				if (*line == '?') // Handle $?
				{
					temp = ft_itoa(last_exit_status);
					result = ft_strjoin_free(result, temp);
					free(temp);
					line++;
				}
				else if (*line == '{') // Handle ${VAR}
				{
					line++;
					start = line;
					while (*line && *line != '}')
						line++;
					var_name = ft_substr(start, 0, line - start);
					value = get_env_value(env_list, var_name);
					if (value)
						result = ft_strjoin_free(result, value);
					free(var_name);
					if (*line == '}')
						line++; // Skip closing brace
				}
				else if (ft_isalpha(*line) || *line == '_') // Handle $VAR
				{
					start = line;
					while (*line && (ft_isalnum(*line) || *line == '_'))
						line++;
					var_name = ft_substr(start, 0, line - start);
					value = get_env_value(env_list, var_name);
					if (value)
						result = ft_strjoin_free(result, value);
					free(var_name);
				}
				else
					result = ft_strjoin_char(result, '$'); // Just a lone $, treat literally
			}
			else
			{
				result = ft_strjoin_char(result, *line);
				line++;
			}
		}
		return result;
	}
}