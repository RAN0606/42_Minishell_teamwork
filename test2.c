#include "minishell.h"

int main ()
{
//	int code;
	int fd;
	int fd2;
	char *s1;
	char *s2;
	char buf[1024];
	int  ret;


	s1 = ft_strdup("123\n");
	s2 = ft_strdup("234\n");
	ft_bzero(buf,1024);
	fd = dup(0);
	printf("testfd: %d\n", fd);
	fd2 = dup(fd);
	ft_putstr_fd(s1, fd2);
	printf("testfd: %d %d\n", fd, fd2);
	close (fd2);
	dup(fd, 0);
	close(fd)
//	ft_putstr_fd(s2, fd);	
	ret = read(0, buf, 100);
	printf("test:ret:%d:%s\n", ret, buf);
	free(s1);
	free(s2);
//	close(fd);
//	close(fd2);
}
