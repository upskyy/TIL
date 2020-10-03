#include<stdio.h>
int my_strl(char str[])
{
	int count = 0;
	for (int i = 0; str[i] != NULL; i++)
	{
			count++;
	}
	return count;
}

int main()
{
	char str[100];
	int num;
	printf("문자열을 입력하세요 :");
	scanf("%s", str);
	num = my_strl(str);
	printf("문자열의 길이 : %d", num);
}