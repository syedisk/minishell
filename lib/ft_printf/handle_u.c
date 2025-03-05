/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:12:30 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/07/03 19:35:00 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_u(va_list args)
{
	unsigned int	num;
	int				count;

	num = va_arg(args, unsigned int);
	count = ft_putnbr_unsigned(num);
	return (count);
}
