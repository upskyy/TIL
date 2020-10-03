#include<stdio.h>
#include <ctype.h>
#include <string.h>
int main()
{
	char name[100];
	int slen;
	printf("문자입력 : ");
	scanf("%s", &name);

	slen = strlen(name); //문자열길이 구하기
	for (int i = 0; i < slen; i++)
	{
		if (name[i] >= 97 && name[i] <= 122)  //아스키코드 이용  , if(islower(name[i])) 라고 해도됨.
		{
			printf("%c", name[i] - 32); // 대문자 만들기,   toupper(name[i])라고 해도됨.
		}
		else
			printf("%c", name[i]);
	}

}