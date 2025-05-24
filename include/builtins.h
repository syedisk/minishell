/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:13:05 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 19:35:59 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

struct					s_token;
typedef struct s_token	t_token;
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

// Builtins
int	handle_cd(char **argv);
int handle_pwd(void);
int	handle_echo(t_token *args, t_env *env_list, int *exit_value);
int handle_export(char **argv, t_env **env_list);
int	handle_unset(char **args, t_env **env_list);
int	handle_exit(char **argv);
int	handle_env(t_env *env);
int	is_valid_identifier(const char *key);

char	*strip_inner_quotes(const char *str);

void		handle_single_quote(t_token *arg);
void		handle_double_or_no_quote(t_token *arg,
				t_env *env_list, int *exit_value);
void		handle_newenv(t_env **env_list, char *key, char *value);




#endif