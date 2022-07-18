/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:21:25 by rliu              #+#    #+#             */
/*   Updated: 2022/07/18 12:56:02 by rliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ms	g_ms;

void	ft_handler(int sigu)
{
	if (sigu == SIGINT && EINTR == errno)
	{
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_ms.status = 130;
	}
}

void	ft_init_data(t_data *data, char **env)
{
	data->env = ft_getenv(env);
	data->pwd = getcwd(NULL, 0);
	data->token_list = NULL;
	g_ms.status = 0;
	g_ms.data = NULL;
}

void	ft_cntl_d(t_data *data)
{
	printf("exit\n");
	free(data->pwd);
	ft_free_env(data->env);
	exit(0);
}

void	ft_start_cmd(t_data *data, char *cmd)
{
	if (!cmd)
		ft_cntl_d(data);
	if (!cmd[0])
		return ;
	add_history(cmd);
	data->token_list = ft_lexer(cmd, data->env);
	if (!data->token_list)
		return ;
	ft_parser_cmd(data);
	if (data->token_list)
		ft_lstclear(&(data->token_list), ft_free_token);
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	t_data	data;	

	(void)argc;
	(void)argv;
	ft_init_data(&data, env);
	cmd = NULL;
	while (1)
	{
		signal(SIGINT, ft_handler);
		signal(SIGQUIT, SIG_IGN);
		if (data.token_list)
			ft_lstclear(&(data.token_list), ft_free_token);
		if (cmd)
			free(cmd);
		cmd = readline("minishell: ");
		ft_start_cmd(&data, cmd);
	}
	return (0);
}
