#include<stdio.h>
#include<time.h>	//시간 측정을 위한 라이브러리

int fib(int num);
int fib2(int num);
int main() {
	clock_t start, end;
	float result;
	start = clock();  //시간 측정 시작
	int seriesSize;
	printf("Input numbers : ");
	scanf("%d", &seriesSize);	 //숫자를 입력받는다.

	printf("Print a Fibonacci series (Iteration). \n");

	for (int looper = 0; looper < seriesSize; looper++) {
		if (looper % 5)			// 숫자 5개씩 끊어서 줄을 바꾸었다.
			printf(", %4d", fib(looper));		// %4d를 이용하여 숫자끼리 띄어주었다.
		else
			printf("\n%4d", fib(looper));
	}
	printf("\n");
	end = clock();	//시간 측정 끝
	result = (float)(end - start) / CLOCKS_PER_SEC;
	printf("소요된 시간 : %f", result);
	return 0;

}
int fib(int num) {
	int result;
	if (num == 0 || num == 1) {
		return num;
	}
	else {
		result = fib2(num);		//피보나치 수열 계산 함수 호출
	}
	return result;
}
int fib2(int num) {			//Iteration을 이용한 피보나치 수열 계산
	int a = 0;
	int b = 1;
	int temp;
	for (int i = 0; i < num - 1; i++) {
		temp = a + b;
		a = b;
		b = temp;
	}
	return b;
}