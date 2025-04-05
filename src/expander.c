/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:28:52 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/05 17:37:24 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"

char	*expand_variables(char *str, char **envp)
{
	char	*varname;
	int		i;

	if (!str || str[0] != '$')
		return (ft_strdup(str));
	varname = str + 1;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], varname, ft_strlen(varname)) == 0
			&& envp[i][ft_strlen(varname)] == '=') // in case there's USER= and USERNAME=
		{
			return (ft_strdup(envp[i] + strlen(varname) + 1));
		}
		i++;
	}
	return (ft_strdup("")); // not found, empty string
}