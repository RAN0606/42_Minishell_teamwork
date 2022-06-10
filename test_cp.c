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


	ft_bzero(buf,1024);
	fd = open("llll", O_RDONLY|O_CREAT|O_WRONLY, 0777);
	printf("testfd: %d\n", fd);
//	dup2(fd, 0);
//	unlink("llll");
//	close(fd);
//	printf("test%d",fd);
//	fd2 = open("z", O_WRONLY|O_TRUNC);
//	printf("test2%d",fd2);
/*	fd =(fcntl(fd, F_SETFL, ))
	if (fd<0)
		return (1);*/
	s1 = ft_strdup("123\n");
	s2 = ft_strdup("234\n");
//	fd = dup(0);
//	ft_putstr_fd(s1, fd);
//	old_flag = fcntl(0, F_GETFL, 0);
//	fcntl(fd ,F_SETFL, O_TRUNC);
	ft_putstr_fd(s2, fd);	
	fd2 = open("llll", O_RDONLY, 0777);
	printf("testfd: %d\n", fd);
//	ft_putstr_fd(s2, fd);
//	fd = dup(0);
//	fcntl(fd,O_RDONLY);
	ret = read(fd2, buf, 100);
	printf("test:ret:%d:%s\n", ret, buf);
	free(s1);
	free(s2);
	close(fd);
//	close(fd2);
}
