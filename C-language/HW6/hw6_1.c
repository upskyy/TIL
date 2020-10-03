#include<stdio.h>
#include <math.h> 
int calculator(char map[5][5])
{
	int count = 0, all_count =0;	
	int before, after = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			count = 0;	
			if (map[i][j] == 'X')
			{
				before = j;
				break;
			}
		} if (j == 0)
		{
			count += before;
			after = before;
			count++;
		}
		if (j >= 1)
		{
			count += abs(after - before);
			after = before;
			count++;
		}		all_count += count;
	} 
	return all_count
}
int main()
{
	char map[5][5];
	int shortest_distance;
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
	printf("The shortest distance : %d\n", shortest_distance);
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