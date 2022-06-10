#include "minishell.h"
#include "sys/wait.h"
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
		execve("ls", argv1+1, envp);
		perror("excve");	
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

	char *argv1[ ]={"ls", "-al","ss", "ss", "/etc/passwd", NULL};
	char *envp[] = {"HOME=/root","PATH=/mnt/nfs/homes/rliu/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", NULL};
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
		else
			ft_ex(argv1, envp);
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
	 (void)env;
//	char prompt[] = "mimishell:";
//	char *cmd;
//	char **envtab;
//	ft_env(envtab); // test env
//	ft_print_value("PATH=", envtab);
	signal(SIGINT, ft_handler);
	ft_try();
//	ft_ex("ls", argv1, envp);
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
