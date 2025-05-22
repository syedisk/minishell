/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 19:07:57 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/17 19:16:34 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H


#include <signal.h>



void set_signals(void);
void sig_handler(int sig);
void ignore_sigquit(void);
void handle_heredoc_signals(void);
void heredoc_sigint_handler(int sig);

#endif