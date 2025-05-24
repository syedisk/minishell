/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 19:42:52 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/24 19:43:05 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	set_signals(void);
void	sig_handler(int sig);
void	ignore_sigquit(void);
void	handle_heredoc_signals(void);
void	heredoc_sigint_handler(int sig);

#endif