/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:38:43 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/05/23 19:37:13 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

volatile sig_atomic_t g_sig_received = 0;

char **tokens_to_args(t_token *tokens)
{
	int	count = 0;
	t_token *tmp = tokens;
	char **args;

	while (tmp)
	{
		if (tmp->type == WORD)
			count++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	tmp = tokens;
	count = 0;
	while (tmp)
	{
		if (tmp->type == WORD)
			args[count++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	args[count] = NULL;
	return (args);
}


void	debug_print_env_list(t_env *env) //debugger to delete
{
	printf("\n--- ENVIRONMENT DEBUG ---\n");
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		else
			printf("%s (no value)\n", env->key);
		env = env->next;
	}
	printf("--- END ENV ---\n\n");
}

static int is_readline_active = 0;

int readline_active_state(void)
{
    return is_readline_active;
}

char *custom_readline(const char *prompt)
{
    is_readline_active = 1;
    char *line = readline(prompt);
    is_readline_active = 0;
	if (!line)
        return NULL;
    return line;
}

static int is_only_whitespace(const char *str)
{
    while (*str)
    {
        if (!ft_isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

int	main(int argc, char **argv, char **envp)
{
	// Clean up old heredoc temp files
	//system("rm -f /tmp/.heredoc_*");

	char		*input;
	t_token 	*tokens;
	t_command	*commands;
	t_env		*env_list;
	char		**env_array;
	int			exit_value;

	exit_value = 0;
	(void)argc;
	(void)argv;
	
	// commands = NULL;
	// commands->exit_value = 0;
	env_list = create_env_list(envp);
	if (!env_list)
		return (printf("Error: Failed to create environment list\n"), 1);
	void ignore_sigquit(void);
	signal(SIGPIPE, SIG_IGN);
	while (1)
	{
		set_signals();
		input = custom_readline("$minishell ");
		if (!input)
		{
            printf("exit\n");
            free_env_list(env_list); // Free environment list
            exit(0); // Exit gracefully
        }
		if (g_sig_received == 130)
		{
			exit_value = 130;
    		g_sig_received = 0;
    		if (*input == '\0') // Only skip empty lines
    		{
				free(input);
				continue;
    		}
		}
		if (*input == '\0' || is_only_whitespace(input))
		{
    		free(input);
    		continue;
		}

		if (*input)
			add_history(input);
		if (check_syntax_error(input))
		{
			free(input);
			continue; 
		}
		//Step 1: tokenise
		tokens = tokenise(input);

		// Debug: print tokens
		// printf("==== TOKENS ====\n");
		// for (t_token *tmp = tokens; tmp; tmp = tmp->next)
		// 	printf("Token: [%s], Type: [%d]\n", tmp->value, tmp->type);
		
		//Step 2: Parse into command structure
		commands = parse_tokens(tokens, env_list, &exit_value);
		if (!commands)
		{
			free_tokens(tokens);
			free(input);
			continue; // Skip to next iteration if parsing fails
		}
		// printf("Command list created successfully. %s\n", commands->argv[0]);
		// // Debug: Heredoc test
		// for (t_command *cmd = commands; cmd; cmd = cmd->next)
		// {
		// 	if (cmd->infile)
		// 	{
		// 		int fd = open(cmd->infile, O_RDONLY);
		// 		if (fd < 0)
		// 			perror("open temp file");
		// 		else
		// 		{
		// 			char buf[1024];
		// 			int bytes;
		// 			// printf("\nHeredoc contents from %s:\n", cmd->infile);
		// 			while ((bytes = read(fd, buf, sizeof(buf) - 1)) > 0)
		// 			{
		// 				buf[bytes] = '\0';
		// 				printf("%s", buf);
		// 			}
		// 			printf("\n--- End of heredoc ---\n\n");
		// 			close(fd);
		// 			//unlink(cmd->infile); // clean up temp file
		// 		}
		// 	}
		// }

		// Debug: print command info
		// printf("==== COMMANDS ====\n");
		// for (t_command *cmd = commands; cmd; cmd = cmd->next)
		// {
		// 	printf("COMMAND:\n");
		// 	for (int i = 0; cmd->argv && cmd->argv[i]; i++)
		// 		printf("  Arg[%d]: %s\n", i, cmd->argv[i]);
		// 	if (cmd->infile)
		// 		printf("  Infile: %s\n", cmd->infile);
		// 	if (cmd->outfile)
		// 		printf("  Outfile: %s (append: %d)\n", cmd->outfile, cmd->append_out);
		// }
		// After parsing tokens and before executing commands:
		if (!commands || !commands->argv || !commands->argv[0] || commands->argv[0][0] == '\0')
		{
    		// No command to execute, match bash: exit 0, no error
    		free_tokens(tokens);
    		free_commands(commands);
    		free(input);
    		exit_value = 0;
    		continue;
		}
		//Step 3: Execute command
		env_array =  convert_env_to_array(env_list);
		execute_commands(commands, &env_list, env_array, &exit_value); // execve in here
		//Step 4: Clean up
		free(input);
		free_tokens(tokens);
		free_commands(commands);
		free_split(env_array);
	}
	return (free_env_list(env_list), 0);
}

