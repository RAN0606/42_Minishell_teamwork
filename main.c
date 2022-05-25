/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:21:25 by rliu              #+#    #+#             */
/*   Updated: 2022/05/25 17:59:54 by rliu             ###   ########.fr       */
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

void ft_free_token (void *token)
{
	if (((t_token *)token)->str)
		free(((t_token *)token) ->str);
	free((t_token *)token);
}

void	ft_print_token(void *token)
{
	printf("token: %d, str :%s\n", ((t_token *)token)->token, ((t_token *)token)->str);
}
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char *cmd;
	char prompt[] = "mimishell:";
//	t_list	*token_list;
	
	print_env(env); // this is a test

	while (1)
	{
		printf("\033[0;32m");
		cmd = readline(prompt);
		printf("\033[0m");
		add_history(cmd);
		//printf("%lu\n", ft_strlen(cmd));
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
		if (ft_strcmp(cmd, "pwd") == 0)
		{
			ft_pwd();
		}
		if (ft_strcmp(cmd,"exit") == 0)
		{
			printf("exit\n");
			free(cmd);
			break;
		}
		ft_lexer(cmd, env);
//		token_list = ft_lexer(cmd, env);
//		if (!token_list)
//			continue ;
//		printf("token: %d, str :%s\n", ((t_token *)(token_list->content))->token, ((t_token *)(token_list->content))->str);

//		ft_lstiter (token_list, ft_print_token);
//		ft_lstclear(&token_list, ft_free_token);
//		token_list = NULL;
	//	printf("%s\n", cmd);
		free(cmd);
	}
}

