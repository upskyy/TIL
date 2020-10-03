#include<stdio.h>
int main()
{
	char A[15] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E' }; //배열 A를 선언하고 주어진 값으로 초기화 
	char B[15] = { 'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T' };//배열 B를 선언하고 주어진 값으로 초기화
	char C[30]; //배열C 선언
	int index_a = 0; //배열 A의 출발점
	int index_b = 14; //배열 B의 출발점
	int up = 1;
	int down = 5;
	int k = 0;

	for (int x = 0; x < 5; x++) //A배열, B배열에서 순차적으로 입력하는 것을 5번 반복한다.
	{
		for (int i = index_a; i < index_a + up; i++) //A배열의 값을 C배열의 값으로 입력하는 반복문
		{
			C[k] = A[i];
			k++;
		}
		index_a += up; // 변수 index_a에 변수up을 더해서 다음 반복문에 초기값을 맞추어준다. 
		up++;

		for (int j = index_b; j > index_b - down; j--) //B배열의 값을 C배열의 값으로 입력하는 반복문
		{
			C[k] = B[j];
			k++;
		}
		index_b -= down; // 변수 index_b에 변수down을 빼서 다음 반복문에 초기값을 맞추어준다. 
		down--;
	}
	printf("A배열 : ");
	for (int x = 0; x < 15; x++) //A배열 출력 , %2c는 한칸씩 띄어서 쓰기 위해서이다.
	{
		printf("%2c", A[x]);
	}
	printf("\nB배열 : ");
	for (int x = 0; x < 15; x++)//B배열 출력 , %2c는 한칸씩 띄어서 쓰기 위해서이다.
	{
		printf("%2c", B[x]);
	}
	printf("\nC배열 : "); //C배열 출력 , %2c는 한칸씩 띄어서 쓰기 위해서이다.
	for (int x = 0; x < 30; x++)
	{
		printf("%2c", C[x]);
	}
}