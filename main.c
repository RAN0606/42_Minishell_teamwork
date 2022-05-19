/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:21:25 by rliu              #+#    #+#             */
/*   Updated: 2022/05/19 12:02:27 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *cmd;
	char prompt[] = "mimishell:";
	char	**envtab;
	
	envtab = ft_getenv(env); // this is malloc should be free before exit(include ctrl+D)
	//ft_env(envtab); //test
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
		if (ft_strcmp(cmd, "pwd") == 0) //add pwd
		{
			ft_pwd();
		}
		/*if (ft_strcmp(cmd, "echo") == 0) //add echo
		{
			ft_echo(args); //cmd to token and parsing
		}*/
		if (ft_strcmp(cmd, "env") == 0) //add env
		{
			ft_env(envtab);
		}
		if (ft_strcmp(cmd,"exit") == 0)
		{
			printf("%s\n", "exit");
			free(cmd);
			ft_free_env(envtab);
			break;
		}
		//printf("%s\n", cmd);
		free(cmd);
	}
	exit(EXIT_SUCCESS);
}
