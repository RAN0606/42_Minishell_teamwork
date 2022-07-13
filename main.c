/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qxia <qxia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:21:25 by rliu              #+#    #+#             */
/*   Updated: 2022/07/13 14:41:38 by qxia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

void	ft_handler(int sigu)
{
	if (sigu == SIGINT && EINTR == errno)
	{
		ft_putstr_fd("\n", 0);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}

void	ft_init_data(t_data *data, char **env)
{
	data->env = ft_getenv(env);
	data->pwd = getcwd(NULL, 0);
	data->token_list = NULL;
}

void	ft_cntl_d(t_data *data)
{
	printf("exit\n");
	free(data->pwd);
	ft_free_env(data->env);
	exit(0);
}

void	ft_start_cmd(t_data *data, char *cmd, char **env)
{
	if (!cmd)
		ft_cntl_d(data);
	if (!cmd[0])
		return ;
	add_history(cmd);
	data->token_list = ft_lexer(cmd, data->env);
	if (!data->token_list)
		return ;
	ft_parser_cmd(data->token_list, env, data);
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
		ft_start_cmd(&data, cmd, env);
	}
	return (0);
}
