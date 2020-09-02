#include <stdio.h>
#include <math.h>  //abs 절대값 사용하기 위한 헤더파일
#include<stdlib.h>
#define MAXSIZE 8 //최대 값
#define true 1 //보기 쉽게 true, false를 1, 0 으로 정의
#define false 0
typedef int boolean;  //가독성을 높이기 위해 int 자료형을 boolean 자료형으로 쓰겠다.
typedef int element;
typedef struct {
	element *stack;  //array to store elements
	int max_size;  //maximum size
	int top;   //stack top
	int count;  
} Stack;

Stack* CreateStack(int size) {     //Stack 동적 메모리 할당, size 만큼 stack 동적 메모리할당
	Stack *pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL)
	{
		return NULL;
	}
	pStack->stack = (element*)malloc((size) * sizeof(element));
	if (pStack->stack == NULL) {
		free(pStack);
		return NULL;
	}
	pStack->max_size = size;
	pStack->top = -1;  
	pStack->count = 0;
	return pStack;
}

void push(Stack *pStack, element item) {
	if (pStack->top == pStack->max_size - 1) {
		printf("Stack is full");
		return;
	}
	pStack->stack[++pStack->top] = item;
}
element pop(Stack *pStack) {
	if (pStack->top < 0) {
		printf("Stack is empty");
		return 0;
	}
	return pStack->stack[pStack->top--];
}
element top(Stack *pStack) {
	if (pStack->top < 0) {
		printf("Stack is empty");
		return 0;
	}
	return pStack->stack[pStack->top];
}

void DestroyStack(Stack *pStack) {
	free(pStack->stack);
	free(pStack);
}

boolean check(Stack *pStack) {    //배치 가능한지 검사
	int k = 0;
	boolean flag = true;
	while (k < pStack->top && flag)
	{	//같은 열이거나 대각선이면 배치 못한다.
		if (pStack->stack[pStack->top] == pStack->stack[k] || abs(pStack->stack[pStack->top] - pStack->stack[k]) == (pStack->top) - k) {
			flag = false;
		}
		k++;
	}
	if (flag == true) {
		return flag;
	}
	else if (flag == false) {
		pStack->top--;  //조건에 맞지 않은 경우 다시 top에서 1을 빼준다. 
		return flag;
	}
}
void put_queen(Stack *pStack) {
	if (check(pStack)) {
		if (pStack->top == (MAXSIZE - 1)) {  //판이 완성 되었으니까 count 1 증가
			pStack->count++;
			pStack->top--; //top을 다시 1 빼준다.
		}
		else {
			for (int j = 0; j < MAXSIZE; j++) {
				push(pStack, j);  //반복문을 통해 각 행에서 퀸이 놓여질 열 값을 stack에 저장한다.
				put_queen(pStack); // 재귀 함수와 push함수에서의 top 증가를 통해 위에서 아래의 행으로 내려간다.
				if (j == (MAXSIZE -1)) {  //j가 7까지 입력된 이후에도 규칙에 어긋난다면 다시 top에서 1을 빼준다.
					pStack->top--;
				}
			}
		}
	}
}
int main(void) {
	Stack *pStack = CreateStack(8);
	for (int i = 0; i < MAXSIZE; i++,pStack->top = -1) //반복문이 한바퀴 돌면 top을 다시 -1로 초기화해준다.
	{
		push(pStack, i); //반복문을 통해 0번째 행에 퀸이 놓여질 열 값을 stack에 저장한다.
		put_queen(pStack);
	}
	printf("\n8-queens problem solution : %d개\n", pStack->count);
	DestroyStack(pStack);
}