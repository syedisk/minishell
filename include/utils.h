/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:33:19 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/22 15:16:38 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char	*remove_quotes(const char *str);
int		safe_write_line(int fd, const char *line);
void	free_split(char **split);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);


#endif