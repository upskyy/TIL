#include<stdio.h>
#include<stdlib.h> //난수 생성을 위한 헤더파일
#include<time.h>  //항상 다른 난수를 얻기 위한 방법
int main()
{
	srand(time(NULL));   //항상 다른 난수를 얻기 위한 방법
	int num = rand() % 51 + 1;  //난수 생성
	int x, i;  // int형 변수선언
	printf("UP-DOWN GAME 시작! \n");  //글자프린트, \n은 줄바꿈


	for (i = 0; i < 5; i++)  //5번 기회를 주기위한 반복문
	{
		printf("숫자를 입력하시오:");  //글자프린트
		scanf("%d", &x);     //숫자 입력 받기
		if (x > num)    //난수보다 큰 값을 입력할 때 조건문 
			printf("DOWN!\n");  //더 낮은 값을 입력하라는 글자프린트
		if (x < num)   //난수보다 작은 값을 입력할 때 조건문
			printf("UP!\n");   //더 높은 값을 입력하라는 글자프린트
		if (x == num)  //난수와 같은 값을 입력할 때 조건문
		{
			printf("승리!");  //글자프린트
			break;   //가장 가까운 반복문 탈출!
		}

	}
	if (x != num)  //난수와 다른 값을 입력할 때 조건문
	{
		printf("패배! 정답은 %d입니다.", num);  //실패를 알려주고 답을 알려주는 글자프린트
	}

	return 0;
}