#include<stdio.h>
#include<stdlib.h>
int main()
{
	int num;
	printf("원하는 크기를 입력하세요:");
	scanf("%d", &num);
	int **a;
	a = (int**)malloc(num * sizeof(int*));
	for (int i = 0; i < num; i++) {
		a[i] = (int *)malloc(num * sizeof(int));
	}
	int c = 1;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++)
		{
			a[i][j] = c;
			c++;
		}
	}
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			printf("%3d",*(*(a+i)+j) );
		}printf("\n");
	}
	
	for (int i = 0; i < num; i++)
	{

		free(*(a + i));
	}
	free(a);
}
