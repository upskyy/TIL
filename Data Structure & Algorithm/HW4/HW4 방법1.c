#include <stdio.h>
#include <math.h> //abs 절댓값을 사용하기 위한 헤더파일
#define MAXSIZE 8 //최대 값
#define true 1 //보기 쉽게 true, false를 1, 0 으로 정의
#define false 0
typedef int boolean;  //가독성을 높이기 위해 int 자료형을 boolean 자료형으로 쓰겠다.
int count = 0;// 전역변수
int matrix[MAXSIZE];  //전역변수

boolean check(int num) { //배치 가능한지 검사
	int k = 0;
	boolean flag = true;
	while (k < num && flag)
	{	//같은 열이거나 대각선이면 배치 못한다.
		if (matrix[num] == matrix[k] || abs(matrix[num] - matrix[k]) == num - k) {
			flag = false;
		}
		k++;
	}
	return flag;
}
void put_queen(int num) {
	if (check(num)) {
		if (num == (MAXSIZE-1) {  //판이 완성 되었으니까 count 1증가
			count++;
		}
		else {
			for (int j = 0; j < MAXSIZE; j++) {
				matrix[num + 1] = j;  //반복문을 통해 각 열에 하나씩 배치, 배열의 인덱스가 행이고 값이 열이다.
				put_queen(num + 1); // 재귀 함수와 num+1을 통해 위에서 아래의 행으로 내려간다.
			}
		}
	}
}
int main(void) {
	for (int i = 0; i < MAXSIZE; i++)
	{
		matrix[0] = i;
		put_queen(0);
	}
	printf("\n8-queens problem solution : %d개\n", count);
	return 0;
}