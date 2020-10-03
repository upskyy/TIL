#include<stdio.h>
int main()
{
	int num;
	printf("Num :");
	scanf("%d", &num);
	for (int i = 0; i < num; i++) // num개의 줄 만들기
	{
		if (i == 0 || i == num - 1) //맨 첫째줄 또는 맨 마지막줄에 대한 조건식
		{
			for (int j = 0; j < num; j++)
			{
				printf("■");
			}
			printf("\n");  //줄바꿈
		}
		else {   //앞에 if문에서 한번 걸러지고 난 후 나머지
			for (int j = 0; j < num; j++)
			{
				if (j == 0 || j == num - 1) // 맨왼쪽 또는 맨 오른쪽이라면
				{
					printf("■");
				}
				else {
					printf("  ");
				}
			}
			printf("\n"); //줄바꿈
		}
	}
	return 0;
}