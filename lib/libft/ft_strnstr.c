/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:10:45 by sbin-ham          #+#    #+#             */
/*   Updated: 2024/06/15 16:29:51 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	big_len;
	size_t	i;
	size_t	j;

	little_len = ft_strlen(little);
	big_len = ft_strlen(big);
	if (len < little_len || little_len > big_len)
		return (NULL);
	if (little_len == 0)
		return ((char *)big);
	i = 0;
	while (i <= len - little_len && big[i] != '\0')
	{
		j = 0;
		while (j < little_len && big[i + j] == little[j])
			j++;
		if (j == little_len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
