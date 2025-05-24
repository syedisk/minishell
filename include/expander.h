/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:30:03 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 19:40:18 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "minishell.h"

char	*expand_variables(char *line, t_env *env_list, int *exit_value);
char	*ft_strjoin_free(char *s1, const char *s2);
char	*get_env_value(t_env *env, const char *key);
char	*ft_strjoin_char(char *s, char c);

#endif