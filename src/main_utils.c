/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:44:48 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 12:45:23 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_only_whitespace(const char *str)
{
    while (*str)
    {
        if (!ft_isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

int	is_skippable_input(char *input)
{
	if (*input == '\0' || is_only_whitespace(input))
	{
		free(input);
		return (1);
	}
	return (0);
}