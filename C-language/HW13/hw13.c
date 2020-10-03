#include<stdio.h>
int main()
{
	char str1[30]; //배열 선언
	FILE * rp = fopen("Hasangcheon.txt", "rt"); //파일을 읽기 모드로 연다. 
	if (rp == NULL) //파일 열기를 실패한 경우 
	{
		puts("Fail to Open the file");
		return -1; //파일의 끝을 표현하기 위한 상수(EOF)
	}
	else {
		puts("Success to open the file");
	}
	while (!feof(rp)) // 마지막에 있는 문자열만 str1에 입력. 파일에서 입출력이 일어나는 위치가 파일의 끝이면 1을 출력하는 feof함수
	{
		fgets(str1, sizeof(str1), rp);
	}
	printf("%s", str1); //str1 출력
	fclose(rp); //열린 파일을 닫는 함수 fclose
}