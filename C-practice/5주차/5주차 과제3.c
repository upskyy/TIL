#include<stdio.h>

void my_strcat(char *des, char *src, char *name)
{
	int i, k;
	for (k = 0; k < 200; k++)
	{
		if (*(des + k) != '\0')
		{
			*(name + k) = *(des + k);
		}
		else if (*(des + k) == '\0')
		{
			*(name + k) = *src;
			break;
		}
	}
	for (i = 1; i < 100; i++)
	{
		if (*(src + i) != '\0')
		{
			*(name + k + i) = *(src + i);
		}
		else if (*(src + i) == '\0')
		{
			*(name + k + i) = *(src + i);
			break;
		}
	}
}

int main()
{
	char des[100], src[100], name[100];
	printf("문자를 입력하세요: ");
	scanf("%s", des);
	printf("문자를 입력하세요: ");
	scanf("%s", src);

	my_strcat(des, src, name);
	printf("%s", name);
	

}