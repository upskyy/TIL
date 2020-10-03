#include<stdio.h>
int main()
{
	int num, col, row; //변수선언
	printf("Number ? : ");
	scanf("%d", &num); //  num값 입력받기

	for (row = 0; row < num; row++)    //줄을 반복하는 반복문
	{

		for (col = num; col > row + 1; col--)  //◆을 반복하는 반복문
		{
			printf("◆");
		}
		for (col = 0; col <= row; col++)  //◇을 반복하는 반복문
		{
			printf("◇");
		}

		printf("\n");  //줄바꾸기
	}
	return 0;
}