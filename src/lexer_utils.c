/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:44:55 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/20 19:24:37 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_isspace(char c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f'
		|| ch == '\r')
		return (1);
	return (0);
}