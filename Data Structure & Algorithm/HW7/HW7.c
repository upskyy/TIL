#include<stdio.h>
#include<stdlib.h>
#include <time.h>

typedef int Element;
#define true 1
#define false 0

typedef struct Heap {
	Element *heapArray; // array to store items
	int maxSize; // maximum size of heapArray
	int size; // 현재 heapArray에 들어가있는 갯수
	int last;
} Heap;

Heap* CreateHeap(int size) {
	Heap* pNewHeap = (Heap*)malloc(sizeof(Heap)); //동적 메모리 할당
	if (pNewHeap == NULL) {
		return NULL;
	}
	pNewHeap->heapArray = (Element*)malloc(size * sizeof(Element)); //동적 메모리 할당
	if (pNewHeap->heapArray == NULL) {
		free(pNewHeap);
		return NULL;
	}
	pNewHeap->maxSize = size;  // 초기화
	pNewHeap->size = 0; // 초기화
	pNewHeap->last = -1; // 초기화
	return pNewHeap;
}
void ReheapUp(Heap *pHeap, int index)
{
	int parentIndex = 0;
	if (index <= 0 || index >= pHeap->size) //base case
		return;
	parentIndex = (index - 1) / 2;
	if (pHeap->heapArray[index] > pHeap->heapArray[parentIndex]) { // true : general case, false : base case
		// parent와 child의 data를 바꾸는 과정
		Element temp = pHeap->heapArray[index];
		pHeap->heapArray[index] = pHeap->heapArray[parentIndex];
		pHeap->heapArray[parentIndex] = temp;
		ReheapUp(pHeap, parentIndex); // recursion
	}
}

void InsertHeap(Heap *pHeap, Element data)
{
	if (pHeap->size >= pHeap->maxSize) {
		printf("Heap is full!\n");
		return;
	}
	pHeap->heapArray[++pHeap->last] = data;
	// ++last 를 한 이유는 배열이 0부터 시작하기 때문에 last를 1 증가시키고 인덱스로 사용한다.
	// shape property
	pHeap->size++; //size 1 증가
	ReheapUp(pHeap, pHeap->last); // order property
}


void ReheapDown(Heap *pHeap, int index)
{
	if (index < 0 || index >= pHeap->size)
		return;
	if (index * 2 + 1 < pHeap->size) {     // left subtree가 존재하는지 확인하고 없으면 바로 함수 종료
		//right subtree를 확인하지 않은 이유는 Heap이 complete binary tree 이기 때문에 왼쪽에 subtree가 없으면 오른쪽에도 subtree가 없다.
		int maxChild = index * 2 + 1;      // maxchild를 left로 대입
		if (maxChild + 1 < pHeap->size && pHeap->heapArray[maxChild + 1] > pHeap->heapArray[maxChild])
			// right subtree가 존재하는지 확인하고, right subtree의 값이 left subtree의 값보다 크다면 maxChild++을 통해 right로 바꿔준다.
			maxChild++;
		if (pHeap->heapArray[maxChild] > pHeap->heapArray[index]) { //true: general case, false: base case
			// parent와 child의 data를 바꾸는 과정
			Element temp = pHeap->heapArray[index];
			pHeap->heapArray[index] = pHeap->heapArray[maxChild];
			pHeap->heapArray[maxChild] = temp;
			ReheapDown(pHeap, maxChild); //recursion
		}
	}
}

int DeleteHeap(Heap *pHeap, Element *pDataOut)
{
	if (pHeap->size <= 0) {
		printf("Heap is empty!\n");
		return false;
	}
	*pDataOut = pHeap->heapArray[0];
	pHeap->heapArray[0] = pHeap->heapArray[pHeap->last--]; // heapArray에 마지막 값을 root에 대입하고 last를 1 감소시킨다.
	pHeap->size--; //size 1 감소
	ReheapDown(pHeap, 0);
	return true;
}



int SelectK(Heap *pHeap, int k) {
	int dataOut;
	int holdOut;
	int originalSize;

	if (k > pHeap->size) {
		return false;
	}
	originalSize = pHeap->size;
	for (int i = 0; i < k; i++) { //k번 반복하여 root data를 삭제
		DeleteHeap(pHeap, &dataOut);
		pHeap->heapArray[pHeap->size] = dataOut; //reconstruct heap을 위해서 root data를 heapArray의 대입 
	}
	holdOut = pHeap->heapArray[0]; //우리가 원하는 data를 holdOut에 대입

	while (pHeap->size < originalSize) {
		pHeap->size++;
		pHeap->last++;
		ReheapUp(pHeap, pHeap->last);
	}
	return holdOut;
}

void DestroyHeap(Heap *pHeap) { //동적 메모리 반납
	free(pHeap->heapArray);
	free(pHeap);
}

void MakeHeap(Heap *pHeap) {
	int num;
	srand(time(NULL)); // 계속 난수가 바뀌도록 한다.
	printf("unsorted array : ");

	for (int i = 0; i < 10; i++) {
		num = (rand() % 100) + 1;
		printf("%d ", num);
		InsertHeap(pHeap, num); // 1 ~ 100 범위의 난수 10개를 heap에 삽입
	}
	printf("\n");
	for (int i = 0; i < 10; i++) {
		printf("%d ", pHeap->heapArray[i]);
	}
}

void Test(Heap *pHeap) {
	int key;

	printf("\n몇 번째 요소를 선택하시겠습니까 ? (0 ~ 19)\n"); //크기가 20인 array를 만들었기 때문이다.
	scanf("%d", &key);

	printf("\n%d 입니다.", SelectK(pHeap, key));

}

int main() {
	Heap *pHeap = CreateHeap(20);
	MakeHeap(pHeap);
	Test(pHeap);

	DestroyHeap(pHeap);
}