/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:05:04 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/07/05 19:16:09 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_ptr(va_list args)
{
	void			*ptr;
	char			*hex_str;
	unsigned long	addr;
	int				count;	

	count = 0;
	ptr = va_arg(args, void *);
	if (!ptr)
		return (ft_putstr_pf("(nil)"));
	addr = (unsigned long)ptr;
	count += ft_putstr_pf("0x");
	hex_str = ft_tohex(addr);
	if (hex_str)
	{
		count += ft_putstr_pf(hex_str);
		free(hex_str);
	}
	return (count);
}
