#include <iostream>
using namespace std;
const int MAX_SIZE = 20; // 최대 크기 상수 20

class Queue {
private:
	int *data; // queue
	int front;
	int rear;
public:
	Queue(int size);  //생성자
	~Queue();   //소멸자
	bool is_empty();  //queue가 비어있는 확인하는 함수
	bool is_full();  //queue가 꽉 차있는 확인하는 함수
	void Enqueue(int x);  //queue에 data 삽입
	int Dequeue();  //FIFO 순으로 data 삭제
	int QueueFront(); //앞에 있는 data를 검색
	int QueueRear(); //뒤에 있는 data를 검색
	void print(); // 출력하는 함수
	void test();  //테스트 함수
};

Queue::Queue(int size) {
	data = (int*)malloc(size * sizeof(int)); //size만큼 동적 메모리 할당
	if (data == NULL) {
		free(data);
	}
	front = -1; //front -1로 초기화
	rear = -1; //rear -1로 초기화
}

Queue::~Queue() {
	free(data); //동적 메모리 반납
}

bool Queue::is_empty() {
	return front == rear;
}

bool Queue::is_full() {
	return ((rear + 1) % MAX_SIZE) == front; //원형큐이다.
}

void Queue::Enqueue(int x) {
	if (is_full()) {
		cout << "큐가 포화상태 입니다." << '\n';
		return;
	}
	rear = (rear + 1) % MAX_SIZE; //원형큐이다. 
	data[rear] = x;
}

int Queue::Dequeue() {
	if (is_empty()) {
		cout << "큐가 비어있습니다." << '\n';
		return 0;
	}
	front = (front + 1) % MAX_SIZE; //원형큐이다. 
	return data[front];
}

int Queue::QueueFront() {
	return data[(front + 1) % MAX_SIZE];
}

int Queue::QueueRear() {
	return data[rear % MAX_SIZE];
}

void Queue::print() {
	cout << "Queue : ";
	if (!is_empty()) {
		int num = front;
		do {
			num = (num + 1) % (MAX_SIZE);
			cout << data[num] << " ";
			if (num == rear) { //모두 다 출력 했다는 의미이므로 break문을 통해 반복문 탈출
				break;
			}
		} while (num != front);
	}
	cout << "\n";
}

void Queue::test() {
	for (int i = 1; i < 20; i += 2) {
		Enqueue(i);
	}    //  1,3,5,7,9,11,13,15,17,19 를 queue에 넣는다.

	print(); //출력

	for (int i = 0; i < 7; i++) {
		Dequeue();
	}    // 처음에 들어간 수부터 7개를 뺀다.

	print();  //출력

	for (int i = 25; i > 15; i--) {
		Enqueue(i);
	}    //  25,24,23,22,21,20,19,18,17,16 을 queue에 넣는다.

	print(); //출력

	for (int i = 0; i < 5; i++) {
		Dequeue();
	}    // 처음에 들어간 수부터 5개를 뺀다.

	print();  //출력
}


int main() {
	Queue q(20);
	q.test();

	return 0;
}