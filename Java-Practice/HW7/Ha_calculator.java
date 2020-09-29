package HA_homework;


public class Ha_calculator {

	public static void main(String[] args) {
		int key = Integer.parseInt(args[0]);
		System.out.println("숫자를 입력하세요. "); 
	
		
		MultiThread[] mt = new MultiThread[key]; //입력 받은 숫자만큼 객체 배열의 레퍼런스 변수를 생성한다.
		for(int i=0;i<key;i++) {
			mt[i]=new MultiThread(); //객체 생성
			mt[i].store(i+1); // 1,2,3,4 ... key 까지 순서대로 값을 저장시킨다.
			mt[i].start();
		}
		try {
			for(int i=0;i<key;i++) {
				mt[i].join(); //다른 스레드의 종료를 기다린다.
			}
		}
		catch(InterruptedException e) {
			Thread.currentThread().interrupt(); //스레드를 종료하기 위한 메커니즘
		}
		System.out.println("total is "+ MultiThread.sum); //최종 total 값을 출력한다.

	}
}

class MultiThread extends Thread{
	static int sum=0; //전역변수 생성
	fac_calculator c;
	int num;
	MultiThread(){
		c =new fac_calculator(); //생성자에서 fac_calculator 객체 생성
	}
	public void store(int n) { //각각의 factorial 값을 구하기 위해 숫자를 저장시킨다.
		num = n;
	}
	public void run() {
		try {
			int result = c.factorial(num);
			sum += result; //static 변수 sum에 결과 값을 더해서 저장한다.
			System.out.println(num+"! ="+ result); //각각의 factorial의 합을 출력한다.
		}catch(Exception e) {
			e.printStackTrace(); //에러 메세지의 발생 근원지를 찾아 단계별로 에러 출력
			System.out.println("예외 발생!!");
		}
	}
}
class fac_calculator{
	public synchronized int factorial(int num) { //임계 영역을 설정하여 현재 데이터를 사용하고 있는 해당 스레드를 제외하고,나머지 스레드들은 데이터에 접근할 수 없도록 막기 위한 것 
	int result =0;
		if(num == 1) {
		result = 1;
	}
		else {
			result = num * factorial(num-1);
		}
		return result; //factorial의 합을 리턴
	}
}
