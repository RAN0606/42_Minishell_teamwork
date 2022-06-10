#include "minishell.h"
int ft_heredoc(char *path, char *str)
{
	int fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	dup2(fd, 0);
	ft_putstr_fd(str,0);
//	close(fd);
	return (0);
}
void ft_printf(int fd)
{
	int ret;
	char buf[1024];
	
	ft_bzero(buf,1024);
	ret = read(fd, buf, 100);
	printf("test:ret:%d:%s\n", ret, buf);
}

int main ()
{
//	int code;
	int fd;
//	int fd2;
	ft_heredoc("file1", "134");
	ft_heredoc("file1", "234");
	fd = open("file1", O_RDONLY, 0777);
//	unlink("file1");
	dup2(fd, 0);
	ft_printf(0);
	close(fd);
//	close(fd2);
}
