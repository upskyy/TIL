#include<stdio.h>
#include<string.h> //strcmp 함수를 이용하기 위한 라이브러리
#include<stdlib.h> //malloc, free 함수를 이용하기 위한 라이브러리
struct person
{
	char name[30];
	int score;
	int studentnumber;
};
int main()
{
	struct person *p, temp;
	int size, k;
	char seekname[30]; //찾을 이름
	char ch;
	printf("정보를 입력할 사람 수를 정해주세요 : ");
	scanf("%d", &size);
	p = (struct person *)malloc(sizeof(struct person)*size); //입력한 숫자만큼 구조체 배열을 동적할당 받기
	for (int i = 0; i < size; i++)
	{
		printf("%d 번째 사람의 학번 : ", i + 1);
		scanf("%d", &p[i].studentnumber);  //학번 입력
		printf("%d 번째 사람의 이름 : ", i + 1);
		while (getchar() != '\n');  //입력버퍼 비우기
		k = 0;
		while (1) {
			ch = getchar();
			if (ch == '\n') break;
			p[i].name[k++] = ch;
		}  //이름 입력
		p[i].name[k] = '\0'; // 문자열 끝에 널문자 입력해주기
		printf("%d 번째 사람의 점수 : ", i + 1);
		scanf("%d", &p[i].score); //점수 입력
	}
	for (int i = 0; i < size; i++) // 점수 비교해서 높은 점수를 앞쪽으로 보내기
	{
		for (int j = 0; j < i; j++) {
			if (p[j].score < p[i].score) {
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}
	k = 0;
	printf("순위를 알고 싶은 사람의 이름 : ");
	while (getchar() != '\n'); //입력버퍼 비우기
	while (1) //찾을 이름 입력
	{
		ch = getchar();
		if (ch == '\n') break;
		seekname[k++] = ch;
	}
	seekname[k] = '\0'; // 문자열 끝에 널문자 입력해주기
	for (int i = 0; i < size; i++) {
		if (strcmp(seekname, p[i].name) == 0) //이름이 동일하면 0을 반환
		{
			printf("%s의 등수는 %d등 입니다.", p[i].name, i + 1);
		}
	}
	free(p); //할당 받은 메모리 반환
}