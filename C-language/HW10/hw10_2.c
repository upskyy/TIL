#include<stdio.h>
#include<math.h>//제곱근을 구하는 함수 sqrt를 이용하기 위한 라이브러리
float calculator(char map[7][7]) //반환형이 float인 함수
{
	int i = 0;
	int j = 0;
	int before_x = 0;
	int before_y = 0;
	int after_x = 0;
	int after_y = 0;
	int count = 0;
	float length = 0;
	float all_length = 0; //총 최단거리
	for (int k = 0; k < 4; k++) //'X' 네개를 찾기 위해서 네번 반복한다.
	{
		if (map[0][0] == 'X')  //(0,0)에 'X'가 있는경우
		{
			map[0][0] = '0';
			continue;
		}
		for (int x = 1; x <= 11; x++) // map[i][j]라고 할때 달팽이모양으로 회전하면 j+, i+,   j-, j-, i-, i-,   j+, j+, j+, i+, i+, i+,   j-, j-, j-, j-, i-, i-, i-, i- 와 같은 규칙을 갖는다. 그때 최대로 돌수있는경우는 j가 순차적으로 11번 +되는경우이다.
		{
			if (x % 2 != 0)  //홀수일때는 플러스
			{
				for (count = 0; count < x; count++) //1이면 한번만 플러스, 3이면 세번만플러스 같은 형태로 반복되기 때문
				{
					if (i < 0 || j < 0) //배열에서 마이너스로 가면 j ++하고 넘어가기
					{
						j++;
					}
					else if (map[i][j] == 'X') // 'X'발견하면 그때 좌표 i,j를 after_x , after_y에 대입 하고 break로 가까운 반복문 탈출
					{
						after_x = i;
						after_y = j;
						break;
					}
					else j++; // 나머지는 j  1증가
				}
				for (count = 0; count < x; count++) //1이면 한번만 플러스, 3이면 세번만 플러스 같은 형태로 반복되기 때문
				{
					if (i < 0 || j < 0) //배열에서 마이너스로 가면 i++하고 넘어가기
					{
						i++;
					}
					else if (map[i][j] == 'X') // 'X'발견하면 그때 좌표 i,j를 after_x , after_y에 대입 하고 break로 가까운 반복문 탈출
					{
						after_x = i;
						after_y = j;
						break;
					}
					else i++; //나머지는 i  1증가
				}
			}
			else //짝수일때는 마이너스
			{
				for (count = 0; count < x; count++)  //2이면 두번만 마이너스, 4이면 네번만 마이너스 형태로 반복되기 때문
				{
					if (i < 0 || j < 0) //배열에서 마이너스로 가면 j--하고 넘어가기
					{
						j--;
					}
					else if (map[i][j] == 'X') // 'X'발견하면 그때 좌표 i,j를 after_x , after_y에 대입 하고 break로 가까운 반복문 탈출
					{
						after_x = i;
						after_y = j;
						break;
					}
					else j--; //나머지는 j  1감소
				}
				for (count = 0; count < x; count++) //2이면 두번만 마이너스, 4이면 네번만 마이너스 형태로 반복되기 때문
				{
					if (i < 0 || j < 0) //배열에서 마이너스로 가면 i--하고 넘어가기
					{
						i--;
					}
					else if (map[i][j] == 'X') // 'X'발견하면 그때 좌표 i,j를 after_x , after_y에 대입 하고 break로 가까운 반복문 탈출
					{
						after_x = i;
						after_y = j;
						break;
					}
					else i--; //나머지는 i  1감소
				}
			}
			if (map[i][j] == 'X') //'X'를 발견하면 'O'로 바꾸어주고 break로 가까운 반복문 탈출
			{
				map[i][j] = 'O';
				break;
			}
		}
		if (k == 0) //첫번째 일때는 (0,0)과 발견 점과의 거리(대각선포함)를 sqrt함수를 이용해서 구한다.
		{
			length = sqrt((after_x - 0)*(after_x - 0) + (after_y - 0)*(after_y - 0));
		}
		else if (k != 0) //나머지의 경우는 제곱근을 구하는 함수 sqrt를 이용해서 발견 점과 직전의 발견 점과의 거리(대각선포함)를 구한다.
		{
			length = sqrt((after_x - before_x)*(after_x - before_x) + (after_y - before_y)*(after_y - before_y));
		}
		before_x = after_x; //발견한 점의 좌표를 before_x에 대입
		before_y = after_y;//발견한 점의 좌표를 before_y에 대입
		all_length += length; //구한 최단거리를 all_length에 더해준다.
	}
	return all_length; // 총 최단거리 반환
}
int main()
{
	char map[7][7] = { 'O','O','O','X','O','O','O',
	'O','O','O','O','O','O','O',
	'X','O','O','O','O','O','O',
	'O','O','O','O','O','O','O',
	'O','O','O','X','O','O','O',
	'O','O','O','O','O','O','O',
	'O','O','O','O','O','O','X' };   //map선언
	float shorttest = 0;
	for (int x = 0; x < 7; x++)  //map 출력
	{
		for (int y = 0; y < 7; y++)
		{
			printf("%3c", map[x][y]);
		}
		printf("\n");
	}
	shorttest = calculator(map);
	printf("최단거리 : %f", shorttest);  //최단거리 출력
}