/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbin-ham <sbin-ham@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:38:43 by sbin-ham          #+#    #+#             */
/*   Updated: 2025/04/05 15:26:42 by sbin-ham         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_token 	*tokens;
	t_token		*tmp;
	t_command	*commands;
	// char	**args;
	// pid_t	pid;
	// int		i;

	// - [ ] to remove
	(void)argc;
	(void)argv;
	(void)envp;
	
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (ft_strncmp(input, "exit", 4) == 0 && input[4] == '\0')
		{
			free(input);
			break ;
		}
		tokens = tokenise(input);
		//test tokenise by printing tokens (for debugging)
		tmp = tokens;
		while (tmp)
		{
			printf("Token: [%s], Type: [%d]\n", tmp->value, tmp->type);
			tmp = tmp->next;
		}
		// parse tokens into commands
		commands = parse_tokens(tokens, envp);

		//print command structure test (for debugging)
		t_command *cmd = commands;
		int i;
		while (cmd)
		{
			printf("COMMAND:\n");
			for(i = 0; cmd->argv && cmd->argv[i]; i++)
				printf("  Arg[%d]: %s\n", i, cmd->argv[i]);
			if (cmd->infile)
				printf("  Infile: %s\n", cmd->infile);
			if (cmd->outfile)
				printf("  Outfile: %s (append: %d)\n", cmd->outfile, cmd->append_out);
			cmd = cmd->next;
		}

		// args = token_to_args(tokens);
		// if (args && args[0])
		// {
		// 	pid = fork();
		// 	if (pid == 0)
		// 	{
		// 		execve(args[0], args, NULL); // to add envp?
		// 		perror("execve");
		// 		exit(1);
		// 	}
		// 	else
		// 		wait(NULL);
		// }
		free(input);
		free_tokens(tokens);
		free_commands(commands);
		// i = 0;
		// while (args && args[i])
		// {
		// 	free(args[i]);
		// 	i++;
		// }
		// free(args);
	}
	return (0);
}
