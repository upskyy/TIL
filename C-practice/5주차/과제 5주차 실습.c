#include<stdio.h>
int main()
{
	int x, y, tmp = 0;
	char map[10][10];
	printf("행의 길이 :");
	scanf("%d", &x);
	printf("열의 길이 :");
	scanf("%d", &y);
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
			
				tmp = map[i][j];
				map[i][j] = map[j][i];
				map[j][i] = tmp;
			
		}
	}
	printf("Tranpose 결과\n");
	for (int j = 0; j < y; j++) {
		for (int i = 0; i < x; i++) {
			printf("%3d", map[j][i]);
		}printf("\n");
	}	
}