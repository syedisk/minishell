/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42singapor>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:13:05 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/16 23:11:01 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// env_utils.c
t_env				*create_env_node(char *env_str, char *sep);
t_env				*create_env_list(char **envp);
char				*get_env_value(t_env *env, const char *key);
void				set_env_value(t_env **env, const char *key,
						const char *value);
char				**convert_env_to_array(t_env *env);
void				free_env_list(t_env *env);

//Builtins
int handle_cd(char **argv);
int handle_pwd(void);
int	handle_echo(char **argv, t_env	*env_list);
int	handle_export(char **argv, t_env **env_list);
int	handle_unset(char **args, t_env **env_list);
int handle_exit(char **argv);
int	handle_env(t_env *env);


#endif