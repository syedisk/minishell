/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:13:05 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/19 18:08:43 by sbin-ham         ###   ########.fr       */
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
t_env				*create_env_node(char *env_str);
t_env				*create_env_list(char **envp);
char				*get_env_value(t_env *env, const char *key);
void				set_env_value(t_env **env, const char *key,
						const char *value);
int					env_size(t_env *env);
char				**convert_env_to_array(t_env *env);
void				free_env_list(t_env *env);

// env.c
int					ft_env(t_env *env);

// export.c
static int			is_valid_export_format(const char *str);
void				ft_export(char **args, t_env **env);

// unset.c
void				unset_env_key(t_env **env, const char *key);
void				ft_unset(char **args, t_env **env);

#endif