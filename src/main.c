/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:38:43 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/19 17:50:23 by sbin-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token 	*tokens;
	t_command	*commands;
	t_env		*env_list;
	char		**env_array;

	(void)argc;
	(void)argv;
	
	env_list = create_env_list(envp);

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);

		// Step 1: tokenise
		tokens = tokenise(input);

		// Debug: print tokens
		printf("==== TOKENS ====\n");
		for (t_token *tmp = tokens; tmp; tmp = tmp->next)
			printf("Token: [%s], Type: [%d]\n", tmp->value, tmp->type);
		
		// Step 2: Parse into command structure
		commands = parse_tokens(tokens, envp);

		// Debug: Heredoc test
		for (t_command *cmd = commands; cmd; cmd = cmd->next)
		{
			if (cmd->infile)
			{
				int fd = open(cmd->infile, O_RDONLY);
				if (fd < 0)
					perror("open heredoc temp file");
				else
				{
					char buf[1024];
					int bytes;
					printf("\nHeredoc contents from %s:\n", cmd->infile);
					while ((bytes = read(fd, buf, sizeof(buf) - 1)) > 0)
					{
						buf[bytes] = '\0';
						printf("%s", buf);
					}
					printf("\n--- End of heredoc ---\n\n");
					close(fd);
					unlink(cmd->infile); // clean up temp file
				}
			}
		}

		// Debug: print command info
		printf("==== COMMANDS ====\n");
		for (t_command *cmd = commands; cmd; cmd = cmd->next)
		{
			printf("COMMAND:\n");
			for (int i = 0; cmd->argv && cmd->argv[i]; i++)
				printf("  Arg[%d]: %s\n", i, cmd->argv[i]);
			if (cmd->infile)
				printf("  Infile: %s\n", cmd->infile);
			if (cmd->outfile)
				printf("  Outfile: %s (append: %d)\n", cmd->outfile, cmd->append_out);
		}

		// Step 3: Execute command
		env_array =  convert_env_to_array(env_list);
		execute_commands(commands, &env_list, env_array); // execve in here
		free_split(env_array);

		// Step 4: Clean up
		free(input);
		free_tokens(tokens);
		free_commands(commands);
	}
	return (0);
}

