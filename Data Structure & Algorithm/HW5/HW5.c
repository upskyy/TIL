#include<stdio.h>
#include<stdlib.h>
#include<string.h> //strcpy 사용하기 위함.
#define true 1 //보기 쉽게 true, false를 1, 0 으로 정의
#define false 0
typedef int boolean; //가독성을 높이기 위해 int 자료형을 boolean 자료형으로 쓰겠다.

typedef struct ListNode {
	int year;
	char picture_name[100];
	char director[30];
	struct ListNode *link;
}ListNode;  // 노드
typedef struct {
	int count;
	ListNode *head;
	ListNode *pos;
}List; // Head 구조체
List* createList() {  // Head 구조체 생성 및 초기화
	List *pNewList = (List*)malloc(sizeof(List)); //동적 할당
	if (pNewList == NULL) {
		return NULL;
	}
	pNewList->count = 0;
	pNewList->head = NULL;
	pNewList->pos = NULL;
	return pNewList;
};
void insert_firstList(List* pList, int year, char picture_name[], char director[]) {
	//처음으로 노드 생성 할 때
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));

	pNewNode->year = year;
	strcpy(pNewNode->picture_name, picture_name);  //문자열 복사
	strcpy(pNewNode->director, director);  //문자열 복사

	pList->head = pNewNode; // Head 노드가 새로 만든 노드를 가리키게 한다.
	pNewNode->link = NULL;  // 새로 만든 노드의 link에 NULL 대입
	pList->count++;  //count 1증가
};
void insertList(List* pList, ListNode *pPre, int year, char picture_name[], char director[]) {
	ListNode* pNewNode = (ListNode*)malloc(sizeof(ListNode));

	pNewNode->year = year;
	strcpy(pNewNode->picture_name, picture_name); //문자열 복사
	strcpy(pNewNode->director, director); //문자열 복사


	if (pPre == NULL) {  //첫번째 노드로 들어가는 경우
		pNewNode->link = pList->head;
		//새로 만든 노드는 Head 노드가 가리켰던 노드를 가리킴.
		pList->head = pNewNode;
		// Head 노드는 새로 만든 노드를 가리킨다.
	}
	else {
		pNewNode->link = pPre->link;
		//pPre가 가리키던 노드를 새로 만든 노드가 가리킨다.
		pPre->link = pNewNode;
		// pPre는 새로 만든 노드를 가리킨다.
	}

	pList->count++;  //count 1 증가
};

boolean search_year_List(List* pList, ListNode **pPre, ListNode **pLoc, int year) {
	// year로 검색을 한다.
	for (*pPre = NULL, *pLoc = pList->head; *pLoc != NULL; *pPre = *pLoc, *pLoc = (*pLoc)->link) {
		if ((*pLoc)->year == year) {
			//pLoc이 가리키는 year와 parameter로 들어온 year가 같다면 true를 리턴.
			return true;
		}
		else if ((*pLoc)->year > year) {
			//pLoc이 가리키는 year가 parameter로 들어온 year보다 크다면 찾고자 하는 year를 넘어간 것이니까 더 이상 검색하는 것은 의미가 없기 때문에 break를 통해 반복문을 탈출하고 false를 리턴.
			break;
		}
	}
	return false;
};

void addListNode(List *pList, int year, char* picture_name, char* director) {
	ListNode *pPre = NULL, *pLoc = NULL;

	if (pList->count == 0) {  //처음 Data node를 삽입하는 경우
		insert_firstList(pList, year, picture_name, director);
		return;
	}
	boolean found = search_year_List(pList, &pPre, &pLoc, year);
	//pPre, pLoc의 주소값을 parameter로 사용.
	if (!found) { //search 하여 얻은 pPre를 이용해 data node 삽입.
		insertList(pList, pPre, year, picture_name, director);
	}
};
boolean print_picture_name(List* pList, int fromwhere, char picture_name[]) {
	if (fromwhere == 0 || pList->pos == NULL) {
		//처음 출력하는 경우 pList의 pos가 pList의 head가 가리키는 노드(첫 번째노드)를 가리키게 함.
		pList->pos = pList->head;
	}
	else {
		pList->pos = pList->pos->link; //pos가 가리키고 있는 노드의 link가 가리키는 노드를 pos가 가리킴.
	}

	if (pList->pos != NULL) {
		//마지막 노드가 아니면, pos가 가리키고 있는 노드의 picture name를 복사
		strcpy(picture_name, pList->pos->picture_name);
		return true;
	}
	else {
		return false;
	}
};
void deleteList(List *pList, ListNode *pPre, ListNode *pLoc)
{
	if (pPre == NULL) //첫 번째 노드를 삭제하는 경우
		pList->head = pLoc->link;
	else  // 첫 번째 이외에 노드를 삭제하는 경우
		pPre->link = pLoc->link;
	free(pLoc);  //동적 메모리 반납
	pList->count--;  //count 1 감소.
};

void removeList(List *pList, int year)
{
	ListNode *pPre = NULL, *pLoc = NULL;
	boolean found = search_year_List(pList, &pPre, &pLoc, year);
	//pPre, pLoc의 주소값을 parameter로 대입하여 search 한다.
	if (found) { //삭제할 노드가 있다면
		deleteList(pList, pPre, pLoc);
	}
};
void print_search_year(List *pList, int year)
{  //year로 검색하여 작품이 있다면 정보 출력, 없다면 작품이 없다고 출력.
	ListNode *pPre = NULL, *pLoc = NULL;
	boolean found = search_year_List(pList, &pPre, &pLoc, year);
	//pPre, pLoc의 주소값을 parameter로 대입하여 search 한다.
	if (found) {
		printf("picture name : %s\n", pLoc->picture_name);
		printf("director : %s", pLoc->director);
	}
	else {
		printf("찾는 작품이 없습니다.");
	}
}

void destroyList(List* pList) {
	ListNode *pDel = NULL, *pNext = NULL;
	for (pDel = pList->head; pDel != NULL; pDel = pNext) {
		// 하나하나씩 꼬리 물며 동적 메모리 반납.
		pNext = pDel->link;
		free(pDel);
	}
	free(pList); // 마지막으로 Head node 동적 메모리 반납
};
void clearInputBuffer()
{
	// 입력 버퍼에서 문자를 계속 꺼내고 \n를 꺼내면 반복을 중단
	while (getchar() != '\n');
};
void main() {
	List* pList = createList();
	char key;
	int year;
	char picture_name[100];
	char director[30];

	while (true) {
		printf("Input a key(P, S, I, D, Q) : ");
		scanf("%c", &key);  //key 값 입력받기

		if (key == 'P') {
			int n = 0;
			boolean check;
			do {
				check = print_picture_name(pList, n++, picture_name);
				if (check) {
					printf("%s  ", picture_name);
				}
			} while (check);
			printf("\n");

		}
		else if (key == 'S') {
			printf("input year : ");
			scanf("%d", &year);
			print_search_year(pList, year);
			//입력 받은 year로 검색하여 작품 출력
		}
		else if (key == 'I') {
			printf("Input year : ");
			scanf("%d", &year);
			printf("Input picture name : ");
			scanf("%s", picture_name);
			printf("Input director : ");
			scanf("%s", director);
			addListNode(pList, year, picture_name, director);
			//입력 받은 year, picture name, director data node에 삽입.
		}
		else if (key == 'D') {
			printf("Input year : ");
			scanf("%d", &year);
			printf("Input picture name : ");
			scanf("%s", picture_name);
			printf("Input director : ");
			scanf("%s", director);
			removeList(pList, year);
			//year를 통해 data node 삭제
		}
		else if (key == 'Q') {
			break; //break를 통해 반복문 탈출.
		}
		clearInputBuffer(); //입력 버퍼 비우기, key에 엔터키가 들어가서 사용함.
		printf("\n");
	}
	destroyList(pList); //동적 메모리 반납.
}