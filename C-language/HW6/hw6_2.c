#include<stdio.h>
#include <math.h> 
float calculator(char map[5][5])
{
	float count = 0, all_count = 0;
	int before, after = 0;
	int j, base = 0;
	for (int i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			count = 0;
			if (map[i][j] == 'X')
			{
				before = j;
				break;
			}
		} if (i == 0)
		{
			count += before;
			after = before;
		}
		if (i >= 1)
		{
			base = abs(after - before);
			count = sqrt(base * base + 1);
			after = before;
		}		all_count += count;
	}
	return all_count;
}
int main()
{
	char map[5][5];
	float shortest_distance;
	for (int i = 0; i < 5; i++)
	{
		map[0][i] = 'O';
		if (i == 4)
		{
			map[0][i] = 'X';

		}
	}

	for (int i = 0; i < 5; i++)
	{
		map[1][i] = 'O';
		if (i == 2)
		{
			map[1][i] = 'X';
		}
	}
	for (int i = 0; i < 5; i++)
	{
		map[2][i] = 'O';
		if (i == 2)
		{
			map[2][i] = 'X';
		}
	}
	for (int i = 0; i < 5; i++)
	{
		map[3][i] = 'O';
		if (i == 1)
		{
			map[3][i] = 'X';
		}
	}
	for (int i = 0; i < 5; i++)
	{
		map[4][i] = 'O';
		if (i == 3)
		{
			map[4][i] = 'X';
		}
	}
	shortest_distance = calculator(map);
	printf("The shortest distance : %f\n", shortest_distance);
	printf("*******Map*******\n");
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%3c", map[i][j]);
		}
		printf("\n");
	}
}