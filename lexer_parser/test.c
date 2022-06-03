#include <stdio.h>
#include <stdlib.h>
void ft_test(int i, int ***j)
{
	int *c;
	
	c= (int *)malloc(3*sizeof(int)) ;
	c[1] = 1;
	c[2] = 2;
	c[0] = 1;
	**j = c;

}

int main ()
{
	int i;
	int **j;

	i = 0;

	ft_test(i, &j);
	printf("j0 %d, j2 %d  \n", j[0][0], j[0][1]);	
	free(*j);
}
