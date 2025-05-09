/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:05:10 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/23 18:59:48 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
#include "minishell.h"

char	*generate_heredoc_filename(int id);
int create_heredoc_file(const char *filepath, char *delimiter, int expand, t_env *env_list);
		void handle_heredoc_signals(void);

#endif