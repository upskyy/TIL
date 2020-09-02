#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct {
	element *stack;  //array to store elements
	int max_size;  //maximum size
	int top;   //stack top
} Stack;

Stack* CreateStack(int size) {     //Stack 동적 메모리 할당, size 만큼 stack 동적 메모리할당
	Stack *pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL)
	{
		return NULL;
	}

	pStack->stack = (element*)malloc(size * sizeof(element));
	if (pStack->stack == NULL) {
		free(pStack);
		return NULL;
	}
	pStack->max_size = size;
	pStack->top = -1;
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



int main(void) {
	int num;
	Stack *pStack = CreateStack(100);
	printf("Input a decimal number : ");
	scanf("%d", &num);  //십진수입력받기
	while (true) {
		if (num == 1) {
			push(pStack, num);  //마지막 숫자1 스택에 입력
			break;  //while 반복문 탈출
		}
		push(pStack, num % 2);  //2로 나눈 나머지 스택에 입력
		num = (num / 2);
	}

	printf("binary number : ");
	while (pStack->top >= 0) {
		num = pop(pStack);  //스택에서 값 받아오기
		printf("%d", num);
	}
	printf("\n");

	DestroyStack(pStack);  //동적 메모리 반납
	pStack = NULL;

	return 0;
}

