/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:30:03 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/17 20:31:52 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
#include "minishell.h"

char *expand_variables(char *line, t_env *env_list, int *exit_value);
char *ft_strjoin_free(char *s1, const char *s2);

#endif