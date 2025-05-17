/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:23:44 by thkumara          #+#    #+#             */
/*   Updated: 2025/05/17 16:41:30 by thkumara         ###   ########.fr       */
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
		return (1);
	}
	return (0);
}
