#include<stdio.h>

void my_strcat(char str1[], char str2[], char str[]) {
	char ch = NULL;
	int i = 0;
	int j = 0;
	while (1) {
		if (str1[j] == NULL) break;
		else str[i++] = str1[j++];
	}
	j = 0;
	while (1) {
		if (str2[j] == NULL) break;
		else str[i++] = str2[j++];
	}
	str[i] = NULL;
	return;
}

int main()
{
	char str1[100], str2[100];
	char str[100];
	char ch = NULL;
	int i = 0;

	printf("str1 :");
	while (1) {
		ch = getchar();
		if (ch == '\n') break;
		str1[i++] = ch;
	}
	str1[i] = NULL;
	i = 0;
	printf("\nstr2 : ");
	while (1) {
		ch = getchar();
		if (ch == '\n') break;
		str2[i++] = ch;
	}
	str2[i] = NULL;
	my_strcat(str1, str2, str);

	for (int k = 0; k < 10; k++) {
		printf("%c", str[k]);
	}
}