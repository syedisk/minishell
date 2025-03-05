/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tohex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:27:40 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/07/03 19:53:10 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hexlen(unsigned long num)
{
	int	len;

	len = 1;
	num = num / 16;
	while (num)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

char	*ft_tohex(unsigned long num)
{
	char	*hex_digits;	
	int		len;
	char	*hex_str;

	hex_digits = "0123456789abcdef";
	len = ft_hexlen(num);
	hex_str = (char *)malloc(len + 1);
	if (!hex_str)
		return (NULL);
	hex_str[len] = '\0';
	while (len--)
	{
		hex_str[len] = hex_digits[num % 16];
		num /= 16;
	}
	return (hex_str);
}
