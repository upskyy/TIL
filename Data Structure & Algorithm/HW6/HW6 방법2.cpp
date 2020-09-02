#include <iostream>
using namespace std;

typedef struct QueueNode { //Data node 구조체
	int data;
	struct QueueNode *link;
}QueueNode;

class Queue {
private:
	QueueNode *front;
	QueueNode *rear;
public:
	Queue();  //생성자
	bool is_empty();  //queue가 비어있는 확인하는 함수
	bool is_full();  //queue가 꽉 차있는 확인하는 함수
	void Enqueue(int data);  //queue에 data 삽입
	int Dequeue();  //FIFO 순으로 data 삭제
	void print(); // 출력하는 함수
	void test();  //테스트 함수
};

Queue::Queue() {
	front = 0;
	rear = 0;
}

bool Queue::is_empty() {
	return front == NULL;
}

bool Queue::is_full() {
	return 0;
}

void Queue::Enqueue(int data) {
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode)); //동적 메모리를 할당 받아서 data 삽입
	temp->data = data;
	temp->link = NULL;
	if (is_empty()) {
		front = temp;
		rear = temp;
	}
	else {
		rear->link = temp; //link를 통해 queue 연결
		rear = temp; //rear가 마지막 data 노드를 가리킴.
	}
}

int Queue::Dequeue() {
	QueueNode *temp = front; //temp가 front가 가리키던 노드를 가리키게 함.
	int data;
	if (is_empty()) {
		cout << "큐가 비어있습니다.";
		return 0;
	}
	else {
		data = temp->data;
		front = front->link;
		if (front == NULL) {
			rear = NULL;
		}
		free(temp); //동적 메모리 반납
		return data;
	}
}

void Queue::print() {
	QueueNode *p;
	cout << "Queue : ";
	for (p = front; p != NULL; p = p->link) { //반복문을 통해 queue 출력
		cout << p->data << " ";
	}
	cout << "\n";
}

void Queue::test() {
	for (int i = 2; i < 20; i += 2) {
		Enqueue(i);
	}    //  2,4,6,8,10,12,14,16,18 을 queue에 넣는다.

	print(); //출력

	for (int i = 0; i < 7; i++) {
		Dequeue();
	}    // 처음에 들어간 수부터 7개를 뺀다.

	print();  //출력

	for (int i = 7; i > 2; i--) {
		Enqueue(i);
	}    //  7,6,5,4,3 을 queue에 넣는다.

	print(); //출력

	for (int i = 0; i < 5; i++) {
		Dequeue();
	}    // 처음에 들어간 수부터 5개를 뺀다.

	print();  //출력
}


int main() {
	Queue q;
	q.test(); //테스트 함수

	return 0;
}