/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:21:25 by rliu              #+#    #+#             */
/*   Updated: 2022/06/14 10:12:35 by rliu             ###   ########.fr       */
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
	(void)argc;
	(void)argv;
	char *cmd;
	char prompt[] = "mimishell:";
	t_list	*token_list;
	
	while (1)
	{
		printf("\033[0;32m");
		cmd = readline(prompt);
		printf("\033[0m");
		add_history(cmd);
		if (!cmd)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}	
		if (!cmd)
			cmd = readline(prompt);
		if (!cmd[0])
		{
			free(cmd);
			continue ;
		}
		if (ft_strcmp(cmd,"exit") == 0)
		{
			printf("exit\n");
			free(cmd);
			break;
		}
		token_list = ft_lexer(cmd, env);
		if (!token_list)
		{
			if (cmd)
				free (cmd);
			continue ;
		}
//		printf("token_list %p\n", token_list);
//		ft_lstiter (token_list, ft_print_token);		
		ft_parser_cmd(token_list, env);
//		ft_excute_simplecmd(token_list, env);
		ft_lstclear(&token_list, ft_free_token);
	//	printf("token_list %p\n", token_list);
		free(cmd);
		signal(SIGINT, ft_handler);
	}
	return (0);
}
