#include<stdio.h>
#include<stdlib.h>
#define true 1 //보기 쉽게 true, false를 1, 0 으로 정의
#define false 0
typedef int boolean;  //가독성을 높이기 위해 int 자료형을 boolean 자료형으로 쓰겠다.
typedef int element;
typedef struct tTreeNode {  //이진트리 노드의 구조체
	element data;
	struct tTreeNode *left, *right;
	boolean key;
} TreeNode;
typedef struct {  //스택의 구조체
	TreeNode **stack;  //TreeNode의 포인터형을 삽입할 배열
	int max_size;  // 최대사이즈
	int top;
} Stack;

TreeNode* CreateTree(TreeNode *left, element item, TreeNode *right)
{
	TreeNode *pNewNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (pNewNode == NULL)
		return NULL;
	pNewNode->data = item;
	pNewNode->left = left;
	pNewNode->right = right;
	pNewNode->key = false; // false로 초기화 해준다.
	return pNewNode;
}
TreeNode* MakeTree() {  //트리를 만들어준다.
	TreeNode *eighteen = CreateTree(NULL, 18, NULL);
	TreeNode *seventeen = CreateTree(NULL, 17, eighteen);
	TreeNode *sixteen = CreateTree(NULL, 16, NULL);
	TreeNode *fifteen = CreateTree(NULL, 15, sixteen);
	TreeNode *fourteen = CreateTree(NULL, 14, fifteen);
	TreeNode *thirteen = CreateTree(seventeen, 13, fourteen);
	TreeNode *twelve = CreateTree(NULL, 12, thirteen);
	TreeNode *eleven = CreateTree(NULL, 11, NULL);
	TreeNode *ten = CreateTree(NULL, 10, eleven);
	TreeNode *nine = CreateTree(NULL, 9, ten);
	TreeNode *eight = CreateTree(NULL, 8, NULL);
	TreeNode *seven = CreateTree(NULL, 7, eight);
	TreeNode *six = CreateTree(NULL, 6, seven);
	TreeNode *five = CreateTree(nine, 5, six);
	TreeNode *four = CreateTree(NULL, 4, five);
	TreeNode *three = CreateTree(twelve, 3, four);
	TreeNode *two = CreateTree(NULL, 2, three);
	TreeNode *root = CreateTree(NULL, 1, two);

	return root;
}
boolean isEmpty(Stack *s) {
	return (s->top == -1);
}
boolean isFull(Stack *s) {
	return (s->top == s->max_size - 1);
}

Stack* CreateStack(int size) {     //Stack 동적 메모리 할당, size 만큼 stack 동적 메모리할당
	Stack *pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL)
	{
		return NULL;
	}
	pStack->stack = (TreeNode**)malloc((size) * sizeof(TreeNode));
	if (pStack->stack == NULL) {
		free(pStack);
		return NULL;
	}
	pStack->max_size = size;
	pStack->top = -1;
	return pStack;
}
void push(Stack *pStack, TreeNode* item) {
	if (isFull(pStack)) {
		printf("Stack is full");
		return;
	}
	pStack->stack[++pStack->top] = item;  // TreeNode 포인터 형 스택에 삽입
}
TreeNode* pop(Stack *pStack) {
	if (isEmpty(pStack)) {
		printf("Stack is empty");
		exit(0);
	}
	return pStack->stack[pStack->top--]; // TreeNode 포인터형을 스택에서 꺼내온 후 리턴해준다.
}
void DestroyStack(Stack *pStack) {
	free(pStack->stack);
	free(pStack);
}
void seekGoal(TreeNode* map, element goal) {
	Stack* pStack = CreateStack(50); // 여유있게 stack의 사이즈를 50으로 해서 만들어준다.
	boolean goalFound = false; //while문 탈출을 위한 flag 
	boolean finish = false; //while문 탈출을 위한 flag
	TreeNode * pMap = map;

	while (!goalFound) {
		if (pMap == NULL) {
			while (true) {
				if (isEmpty(pStack)) {
					printf("Goal is not founded.");
					finish = true; //while문 탈출을 위해 true로 바꾸어주고 break문을 통해 가까운 반복문 탈출
					break;
				}
				pMap = pop(pStack); // branch point까지 노드를 하나씩 꺼내준다.
				if (pMap->key == true) {
					pMap->key = false; // goal path를 출력하기 위해 key를 false로 하여 다시 stack에 삽입
					push(pStack, pMap);
					pMap = pMap->left; // branch point에서 반대쪽 노드로 이동
					break;
				}
			}
			if (finish == true) { // while문 탈출
				break;
			}
		}
		else {
			if (pMap->data == goal) { //goal을 찾았다면
				goalFound = true;  //while문 탈출을 위해 true로 변경
				push(pStack, pMap); // goal path를 출력하기 위해 goal도 stack에 삽입
				break; //가까운 반복문 탈출
			}
			else {
				if (pMap->left != NULL && pMap->right != NULL) {
					pMap->key = true;  //  branch point이면 key를 true로 대입
					push(pStack, pMap);
				}
				else {
					push(pStack, pMap);
				}
			}
			pMap = pMap->right; // 다음 노드로 연결해준다.
		}

	}

	if (goalFound) { // goal을 찾았다면
		printf("The path to your goal is : ");
		while (true) {
			if (!isEmpty(pStack)) { // stack이 비어있지 않다면 pop을 통해 goal path 출력
				printf("%d ", pop(pStack)->data);
			}
			else
				break;  // stack이 비어있다면 반복문 탈출
		}
	}
	DestroyStack(pStack); //동적 메모리 반납
}
int main() {
	TreeNode *tTreeNode = MakeTree(); // 트리를 만들어준다. 
	int goal;
	printf("Input your goal : ");
	scanf("%d", &goal); // goal을 입력받는다.
	seekGoal(tTreeNode, goal); // goal을 찾아준다.
}