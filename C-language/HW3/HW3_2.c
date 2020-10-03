#include<stdio.h>
int main()
{
	int num;    //변수 선언
	printf("Num :");
	scanf("%d", &num);
	for (int i = 0; i < num; i++)  //num만큼의 줄 만들기
	{
		if (i == 0 || i == num - 1)  //첫째줄 또는 마지막줄에 대한 조건식
		{
			for (int j = 0; j < num; j++)
			{
				printf("■");
			}
			printf("\n");  //줄바꿈
		}
		else if (i % 2 == 0)  //앞에 if문에서 한번 걸러진후 그 다음 i가 짝수라면 이라는 조건식
		{
			for (int j = 0; j < num; j++) {
				if (j == 0 || j == num - 1)   //맨 첫칸 또는 맨 마지막 칸에 대한 조건식
				{
					printf("■");
				}
				else if (i + j == num - 1 || i == j) //대각선이라면
				{
					printf("■");
				}
				else if (j % 2 == 0) //앞에 if문에서 걸러지고 남은 나머지 중 짝수라면
				{
					printf("□");
				}
				else {
					printf("  ");
				}
			} printf("\n");
		}
		else     //앞에 if문들에서 걸러지고 나머지
		{
			for (int j = 0; j < num; j++)
			{
				if (j == 0 || j == num - 1)
				{
					printf("■");
				}
				else {
					printf("  ");
				}
			}
			printf("\n");
		}
	}
	return 0;
}