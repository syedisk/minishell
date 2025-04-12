/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thkumara <thkumara@student.42singapor>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 21:58:45 by thkumara          #+#    #+#             */
/*   Updated: 2025/03/30 21:58:45 by thkumara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(char *str1, char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

size_t	ft_strcpy(char *dst, const char *src)
{
	size_t		src_len;
	const char	*s;

	src_len = 0;
	s = src;
	while (*s++)
		src_len++;
	while (*src != '\0')
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}

size_t	ft_strcat(char *dst, char *src)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	while (src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

int    ft_unsetenv(char *var)
{
    int i;
    int j;
    size_t  len;

    len = ft_strlen(var);
    i = 0;

    while (environ[i])
    {
        if (ft_strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
        {
            j = i;
            while(environ[j])
            {
                environ[j] = environ[j + 1];
                j++;
            }
            return (1);
        }
        i++;
    }
    return (0);
}

void    ft_env()
{
    int i;

    i = 0;
    
    if (!environ[i])
    {
	 printf("No environment variables available\n");
	 return ;
    } 	
    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }
}
void    handle_export(char  *arg)
{
    char	**value;
    char    **env;
    char    *existing_value;

    int i = 0;
        if (!arg)
		{
            while(environ[i])
            {
                printf("declare -x %s\n", environ[i]);
                i++;
            }
			return ;
		}
        if (arg[0])
            env = ft_split(arg, ' ');
        else
            env = &arg;
        while (env[i])
        {
            value = ft_split(env[i], '=');
            i++;
        }
        if (!value || !value[1])
        {
            printf ("export: invalid format, use KEY=VALUE %s\n", value[1]);
			return ;
        }
        i = 0;
        while (env[i])
        {
            existing_value = getenv(value[i]);
            if (existing_value)
			    printf("Updating existing variable: %s=%s\n", value[i], existing_value);
		    else
			    printf ("Creating new variable: %s=%s\n", value[i], value[i+1]);
            handle_newenv(value[i], value[i+1]);
            i++;
        }
        free(env);
        free(value);
        return ;
    }

   void     handle_newenv(char *key, char *value)
    {
        int len;
        char    *env_entry;
        char    *env_key;
        char    **split;
        int i;

        env_key = NULL;
        len = ft_strlen(key) + ft_strlen(value) + 2;
        env_entry = malloc (len);
        if (!env_entry)
        {
            perror("malloc failed");
            return ;
        }
        ft_strcpy(env_entry, key);
        ft_strcat(env_entry, "=");
        ft_strcat(env_entry, value);
        i = 0;
        while (environ[i])
        {
            split = ft_split(environ[i], '=');
            env_key = split[0];
            if (ft_strcmp(env_key, key) == 0)
            {
                environ[i] = env_entry;
                // free (split);
                // free(env_entry);
                return ;
            }
            i++;
        }
        environ[i] = env_entry;
        environ[i + 1] = NULL;
        // free (split);
        // free(env_entry);
    }

    int is_n_flag(char *str)
    {
        if (!str || str[0] != '-' || str[1] != 'n')
            return 0;
        if (str[1] != 'n')
            return 0;
        return 1;
    }


    void    handle_echo(char **argv)
    {
        int i = 1;
        int newline = 0;
    
        if (argv[i] && is_n_flag(argv[i]))
            newline = 1;
        if (newline == 1)
            i = 2;
        while (argv[i])
        {
            printf("%s", argv[i]);
            if (argv[i + 1])
                printf(" ");
            i++;
        }
        if (!newline)
            printf("\n");
    }

    void    handle_unset(char   *var)
    {
        if (!var)
        {
            printf("unset: not enough arguments\n");
            return ;
        }
        ft_unsetenv(var);
    }

    // void    handle_echo(char    **argv)
    // {
    //     int i;
    //     int append;
    //     char *outfile;
    //     int fd = STDOUT_FILENO;

    //     i = 1;
    //     append = 0;
    //     outfile = NULL;
    //     while (argv[i])
    //     {
    //         if (ft_strcmp(argv[i], ">") == 0 || ft_strcmp(argv[i], ">>") == 0)
    //         {
    //             append = (ft_strcmp(&argv[i], ">>") == 0);
    //             outfile = argv[i + 1];
    //             argv[i] = NULL;
    //             break;
    //         }
    //         i++;
    //     }
    //     if (outfile)
    // {
    //     fd = open(outfile, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
    //     if (fd == -1)
    //     {
    //         perror("Error opening file");
    //         return;
    //     }
    //     dup2(fd, STDOUT_FILENO); // Redirect stdout to the file
    // }

    // Print remaining arguments
    // while (cmd->argv[i])
	// 	{
	// 		printf("%s", cmd->argv[i]);
	// 		if(cmd->argv[i + 1])
	// 			printf(" ");
	// 		i++;
	// 	}
	// 	printf ("\n");

    //Restore stdout and close file
    // if (fd != STDOUT_FILENO)
    // {
    //     close(fd);
    //     dup2(STDOUT_FILENO, fd);
    // }
    // }
