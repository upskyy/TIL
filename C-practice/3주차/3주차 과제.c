#include<stdio.h>

struct student {
	char name[100];
	int age;
	int studentnum;
	int score;
	char grade;
};

int main()
{
	struct student student[100], temp[100];
	int x, y, i, j, p, r;

	printf("입력할 학생의 수를 입력하세요:");
	scanf("%d", &x);

	for (y = 1; y <= x; y++)
	{
		printf("%d번 학생의 이름을 입력하세요:", y);
		scanf("%s", &student[y - 1].name);
		printf("%d번 학생의 나이를 입력하세요:", y);
		scanf("%d", &student[y - 1].age);
		printf("%d번 학생의 학번을 입력하세요:", y);
		scanf("%d", &student[y - 1].studentnum);
		printf("%d번 학생의 점수를 입력하세요:", y);
		scanf("%d", &student[y - 1].score);
		printf("\n");

	}


	for (r = 0; r < x; r++)
	{
		if (student[r].score >= 90)
			student[r].grade = 'A';
		else if (student[r].score >= 80)
			student[r].grade = 'B';
		else if (student[r].score >= 70)
			student[r].grade = 'C';
		else if (student[r].score >= 60)
			student[r].grade = 'D';
		else
			student[r].grade = 'F';
	}

	for (i = 0; i < x; i++)
	{
		for (j = 0; j < x - i; j++)
		{
			if (student[j + 1].score > student[j].score)

			{
				temp[j] = student[j];
				student[j] = student[j + 1];
				student[j + 1] = temp[j];
			}

		}
	}

	printf("석차 이름   나이   학번     점수 학점\n");
	for (p = 0; p < x; p++)
	{
		printf("  %d %s    %d %d    %d %c\n", p + 1, student[p].name, student[p].age, student[p].studentnum, student[p].score, student[p].grade);
	}

	return 0;
}