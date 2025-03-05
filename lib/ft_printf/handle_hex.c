/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:18:06 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/07/05 18:24:09 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	toupperhex(char *str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'f')
			*str = *str - 'a' + 'A';
		str++;
	}
}

int	handle_hex(va_list args, int uppercase)
{
	unsigned int	num;
	char			*hex_str;
	int				chars_written;

	num = va_arg(args, unsigned int);
	hex_str = ft_tohex(num);
	if (!hex_str)
		return (0);
	if (uppercase)
		toupperhex(hex_str);
	chars_written = ft_putstr_pf(hex_str);
	free(hex_str);
	return (chars_written);
}
