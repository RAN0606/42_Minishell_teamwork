/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:21:25 by rliu              #+#    #+#             */
/*   Updated: 2022/05/19 16:52:45 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_lexer(*cmd)
{
	if (cmd = :wq)

}

void ft_readcmd()
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
		if (!cmd)
			exit(EXIT_SUCCESS);
		if (!cmd[0])
		{
			free(cmd);
			continue;
		}
		free(cmd);
	}
	exit(0);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char **envtab;

	ft_readcmd();
	exit(EXIT_SUCCESS);
}
