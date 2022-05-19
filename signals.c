/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:21:25 by rliu              #+#    #+#             */
/*   Updated: 2022/05/19 16:24:58 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_free_env(char **envtab)
{
	int i;
	i = 0;
	while(*(envtab + i))
		free(envtab[i++]);
	free(envtab);
}


char	**ft_getenv(char **env)
{
	int	i;
	char	**envtab;
	
	i = 0;
	while (*(env+i))
		i++;		
	envtab = (char **)malloc(sizeof(char *) * (i+1));
	i = 0;
	while (*(env + i))
	{
		envtab[i] = ft_strdup(*(env+i));
		i++;
	}
	envtab[i] = 0;
	return (envtab);
}

void ft_env(char **envtab)// this is just a test for env
{
	int i;

	i = 0;
	while (*(envtab+i))
		printf("%s\n", envtab[i++]);
}

int ft_ex(char **argv1, char **envp)
{
	int pid;
	int signal = 0;

	pid = fork();
	if (pid == -1)
		printf("erro");
	if (!pid)
	{
		execve("/usr/bin/ls", argv1, envp);	
	}
	else
	{
		waitpid(pid, &signal, 0);
		signal = WEXITSTATUS(signal);
	}
	return (signal);
}

void ft_try()
{
	char *cmd;

	char prompt[] = "mimishell:";
	cmd = NULL;
	while (1)
	{
		printf("\033[0;32m");
		cmd = readline(prompt);
		printf("\033[0m");
		add_history(cmd);
		//printf("%lu\n", ft_strlen(cmd));
		if (!cmd)
			exit(EXIT_SUCCESS);
		if (!cmd[0])
		{
			free(cmd);
			continue;
		}
	/*	if (ft_strcmp(cmd, "ls") == 0)
		{
			ft_ex(argv1, envp);
		}*/
		if (ft_strcmp(cmd,"exit") == 0)
		{
			free(cmd);
		//	ft_free_env(envtab);
			break;
		}
			printf("%s\n", cmd);
		free(cmd);
	}
	exit(0);
}


void ft_handler(int sigu)
{
	if (sigu == SIGINT)
	{
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
//	char prompt[] = "mimishell:";
//	char *cmd;
	char **envtab;
//	char *argv1[ ]={"ls", "-al","ss", "ss", "/etc/passwd", NULL};
//	char *envp[ ]={"PATH=/usr/bin", NULL};

	envtab = ft_getenv(env); // this is malloc should be free before exit(include ctrl+D)
//	ft_env(envtab); // test env
	ft_print_value("PATH=", envtab);
	signal(SIGINT, ft_handler);
	ft_try();
	printf("1");
/*	while (1)
	{
		printf("\033[0;32m");
		cmd = readline(prompt);
		printf("\033[0m");
		add_history(cmd);
		//printf("%lu\n", ft_strlen(cmd));
		if (!cmd)
			exit(EXIT_SUCCESS);
		if (!cmd[0])
		{
			free(cmd);
			continue;
		}
		if (ft_strcmp(cmd,"") == 0)
		{
			free(cmd);
			continue;
		}
		if (ft_strcmp(cmd, "ls") == 0)
		{
			ft_ex(argv1, envp);
		}
		if (ft_strcmp(cmd,"exit") == 0)
		{
			free(cmd);
			ft_free_env(envtab);
			break;
		}
		printf("%s\n", cmd);
		free(cmd);
	}*/
	exit(EXIT_SUCCESS);
}
