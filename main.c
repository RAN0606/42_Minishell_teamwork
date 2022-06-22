/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:21:25 by rliu              #+#    #+#             */
/*   Updated: 2022/06/22 12:31:36 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env(char **env)// this is just a test for env
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
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
	char	*cmd;
	t_list	*token_list;
	t_data	data;	

	(void)argc;
	(void)argv;
	data.env = ft_getenv(env);
	while (1)
	{
		signal(SIGINT, ft_handler);
		printf("\033[0;32m");
		cmd = readline("minishell: ");
		add_history(cmd);	
		if (!cmd)
		{
			printf("exit\n");
			exit(0);
		}
		if (!cmd[0])
		{
			free(cmd);
			continue ;
		}
		token_list = ft_lexer(cmd, data.env);
		if (!token_list)
		{
			if (cmd)
				free (cmd);
			continue ;
		}
		ft_parser_cmd(token_list, env, &data);
		ft_lstclear(&token_list, ft_free_token);
		free(cmd);
	}
	return (0);
}
