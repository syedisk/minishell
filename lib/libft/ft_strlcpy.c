/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:34:01 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/05/27 15:25:34 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		src_len;
	const char	*s;

	src_len = 0;
	s = src;
	while (*s++)
		src_len++;
	if (size == 0)
		return (src_len);
	while (*src != '\0' && size > 1)
	{
		*dst++ = *src++;
		size--;
	}
	if (size > 0)
		*dst = '\0';
	return (src_len);
}
