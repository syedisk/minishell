/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:11:41 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/07/05 19:07:43 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putstr_pf(const char *str);
int		ft_putnbr(int n);
char	*ft_tohex(unsigned long num);
int		ft_putnbr_unsigned(unsigned int n);
int		handle_int(va_list args);
int		handle_str(va_list args);
int		handle_char(va_list args);
int		handle_ptr(va_list args);
int		handle_u(va_list args);
int		handle_hex(va_list args, int uppercase);

#endif
