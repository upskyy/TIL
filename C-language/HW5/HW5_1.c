#include<stdio.h>
int main()
{
	char name[6], newname[6];
	int key, i;

	printf("문자열을 입력하세요\n");
	scanf("%s", &name);   //문자열 입력받기
	do {
		printf("key값을 입력하세요\n");
		scanf("%d", &key);   //key값 입력받기
	} while (key < 1 || key>26);   //key값으로 1부터 26사이의 값을 입력하지 않으면 다시 반복한다.
	for (i = 0; i < 5; i++)
	{
		newname[i] = name[i] + key; //각각의 문자열에  key값을 더한다.
	}
	for (i = 0; i < 5; i++)
	{
		if (newname[i] > 122) //알파벳 z에 숫자를 더했을때 다시 a부터 순환하도록 한다. (ASCII 코드 참고)
		{
			newname[i] -= 26;
		}
	}
	printf("기본 문자열 %s\n암호화 된 문자열 ", name);
	for (i = 0; i < 5; i++) //암호화 된 문자열 출력
	{
		printf("%c", newname[i]);
	}
	printf("\n");
	do {
		printf("key값을 입력하세요\n");
		scanf("%d", &key); //key값 입력받기
	} while (key < 1 || key>26); //key값으로 1부터 26사이의 값을 입력하지 않으면 다시 반복한다.
	for (i = 0; i < 5; i++) // 암호화 된 문자열에서 key 값을 뺀다.
	{
		name[i] = newname[i] - key;
	}
	for (i = 0; i < 5; i++)
	{
		if (name[i] < 97) //알파벳 a에서 숫자를 뺄 경우 반대로 z부터 순환하도록 한다. (ASCII 코드 참고)
		{
			name[i] += 26;
		}
	}
	printf("복호화 된 문자열 ");
	for (i = 0; i < 5; i++) //복호화 된 문자열을 출력한다.
	{
		printf("%c", name[i]);
	}
	printf("\n암호화 된 문자열 ");
	for (i = 0; i < 5; i++) //암호화 된 문자열을 출력한다.
	{
		printf("%c", newname[i]);
	}

	for (i = 0; i < 27; i++) // 1과 26사이의 모든 숫자들을 이용해서 복호화를 진행 한다.
	{
		printf("\nkey 값 %d 복호화 된 문자열 ", i);
		for (int j = 0; j < 5; j++)
		{
			if (newname[j] - i < 97) //알파벳 a에서 숫자를 뺄 경우 반대로 z부터 순환하도록 한다.
			{
				printf("%c", newname[j] - i + 26);
			}
			else
			{
				printf("%c", newname[j] - i);
			}
		}
	}
}