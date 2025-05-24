/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:33:19 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 18:11:09 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int		safe_write_line(int fd, const char *line);
char	*remove_quotes(const char *str);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
int		ft_isspace(char c);
void	free_split(char **split);

#endif