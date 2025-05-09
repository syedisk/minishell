/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:43:30 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/05/21 11:58:55 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (n--)
	{
		*p++ = (unsigned char)value;
	}
	return (ptr);
}
