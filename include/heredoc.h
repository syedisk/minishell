/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:05:10 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 19:56:05 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "minishell.h"

typedef struct s_heredoc_info
{
	const char	*filepath;
	char		*delimiter;
	int			expand;
	t_env		*env_list;
	int			*exit_value;
}				t_heredoc_info;

char			*generate_heredoc_filename(int id);
int				create_heredoc_file(t_heredoc_info *info);
void			handle_heredoc_signals(void);

#endif