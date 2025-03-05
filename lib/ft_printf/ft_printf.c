/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:34:21 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/07/16 18:02:04 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_format(const char **format, va_list args)
{
	int	chars_written;

	chars_written = 0;
	if (**format == 'd' || **format == 'i')
		chars_written = handle_int(args);
	else if (**format == 's')
		chars_written = handle_str(args);
	else if (**format == 'c')
		chars_written = handle_char(args);
	else if (**format == 'p')
		chars_written = handle_ptr(args);
	else if (**format == 'u')
		chars_written = handle_u(args);
	else if (**format == 'x')
		chars_written = handle_hex(args, 0);
	else if (**format == 'X')
		chars_written = handle_hex(args, 1);
	else if (**format == '%')
		chars_written = write(1, "%", 1);
	else
	{
		chars_written = write(1, "%", 1);
		chars_written += write(1, *format, 1);
	}
	return (chars_written);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	int				total_chars;
	const char		*ptr;

	total_chars = 0;
	ptr = format;
	va_start(args, format);
	while (*ptr)
	{
		if (*ptr == '%' && *(ptr + 1) != '\0')
		{
			ptr++;
			total_chars += handle_format(&ptr, args);
		}
		else
			total_chars += write(1, ptr, 1);
		ptr++;
	}
	va_end(args);
	return (total_chars);
}
