#include<stdio.h>
#include<time.h>	//시간 측정을 위한 라이브러리
int fib(int num);
int main() {
	clock_t start, end;
	float result;
	start = clock();	//시간 측정 시작
	int seriesSize;
	printf("Input numbers : ");
	scanf("%d", &seriesSize);  //숫자를 입력받는다.

	printf("Print a Fibonacci series (Recursion). \n");

	for (int looper = 0; looper < seriesSize; looper++) {
		if (looper % 5)  // 숫자 5개씩 끊어서 줄을 바꾸었다.
			printf(", %4d", fib(looper));  // %4d를 이용하여 숫자끼리 띄어주었다.
		else
			printf("\n%4d", fib(looper));
	}
	printf("\n");
	end = clock();		//시간 측정 끝
	result = (float)(end - start) / CLOCKS_PER_SEC;
	printf("소요된 시간 : %f", result);	// 소요된 시간 출력
	return 0;

}
int fib(int num) {			//재귀를 이용한 피보나치 수열 계산
	if (num == 0 || num == 1) {
		return num;
	}
	return(fib(num - 1) + fib(num - 2));
}