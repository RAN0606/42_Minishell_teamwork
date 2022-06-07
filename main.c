/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:21:25 by rliu              #+#    #+#             */
/*   Updated: 2022/06/07 12:32:58 by rliu             ###   ########.fr       */
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
		if (!cmd[0])
		{
			free(cmd);
			continue;
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
		
		ft_parser_cmd(token_list);
		ft_lstclear(&token_list, ft_free_token);
	//	printf("token_list %p\n", token_list);
		free(cmd);
	}
	return (0);
}
