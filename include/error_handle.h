/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:21:36 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/24 21:59:28 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLE_H
# define ERROR_HANDLE_H

int		is_quote(char c);
int		has_unclosed_quotes(const char *input);
int		has_trailing_operator(const char *input);
int		check_syntax_error(const char *input);
void	error_msg(char *error);

#endif