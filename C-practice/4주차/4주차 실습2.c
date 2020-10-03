#include<stdio.h>
#include<math.h>
struct person {
	int x;
	int y;
};
float calculator(struct person *p1, struct person *p2, struct person *p3)
{
	float result1, result2, result3, biggest_length;
	result1 = sqrt((p2->x - p1->x) * (p2->x - p1->x) + (p2->y - p1->y) * (p2->y - p1->y));
	result2 = sqrt((p3->x - p1->x) * (p3->x - p1->x) + (p3->y - p1->y) * (p3->y - p1->y));
	result3 = sqrt((p3->x - p2->x) * (p3->x - p2->x) + (p3->y - p2->y) * (p3->y - p2->y));
	if (result1 > result2 && result1 > result3)
	{
		biggest_length = result1;
	}
	else if (result2 > result1 && result2 > result3)
	{
		biggest_length = result2;
	}
	else
	{		biggest_length = result3;
}
	return biggest_length;
}
int main()
{
	struct person p1, p2, p3;
	float z;
	printf("두점을 입력하세요:");
	scanf("%d %d", &p1.x, &p1.y);

	printf("두점을 입력하세요:");
	scanf("%d %d", &p2.x, &p2.y);

	printf("두점을 입력하세요:");
	scanf("%d %d", &p3.x, &p3.y);

	z = calculator(&p1, &p2, &p3);

	printf("가장긴변의 길이 : %f", z);

}