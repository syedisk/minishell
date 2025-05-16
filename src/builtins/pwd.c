/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42singapor>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:23:44 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/16 21:15:51 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pwd(void)
{
	char	cwd[1024];

	//cwd[0] = '\0';
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
	{
		perror("pwd");
		g_last_exit_status = 1;
		return (1);
	}
	g_last_exit_status = 0;
	return (0);
}
