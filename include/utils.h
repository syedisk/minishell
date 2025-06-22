/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:33:19 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/06/22 20:53:10 by thkumara         ###   ########.fr       */
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