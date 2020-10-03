#include<stdio.h>
#include<stdlib.h>
int main()
{
	int x, y = 0;
	int **map;
	int **map2;

	printf("행의 길이 :");
	scanf("%d", &x);
	printf("열의 길이 :");
	scanf("%d", &y);
	
	map = (int**)malloc(x * sizeof(int*)); //2줄
	for (int i = 0; i < x; i++) {  //한줄씩 주는 메모리 할당
		*(map + i) = (int*)malloc(y * sizeof(int));
	}

	map2 = (int**)malloc(y * sizeof(int*)); //2줄
	for (int i = 0; i < y; i++) {  //한줄씩 주는 메모리 할당
		*(map2 + i) = (int*)malloc(x * sizeof(int));
	}

	for (int p = x - 1; p >= 0; p--) {
		for (int q = y - 1; q >= 0; q--) {
			printf("A%d%d : ", x - p, y - q);
			scanf("%d", &map[x - p - 1][y - q - 1]);
		}
	}
	printf("입력된 행렬의 값\n");
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			printf("%3d", map[i][j]);
		}printf("\n");
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++) {
		map2[j][i] = map[i][j];
		}
	}

	printf("Tranpose 결과\n");
	for (int j = 0; j < y; j++) {
		for (int i = 0; i < x; i++) {
			printf("%3d", map2[j][i]);
		}printf("\n");
	}
}