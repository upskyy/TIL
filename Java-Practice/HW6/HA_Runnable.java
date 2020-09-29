package HA_homework;
import java.util.Scanner; //Scanner클래스를 사용하기 위한 import

public class HA_Runnable {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in); //입력받기 위해 Scanner 클래스의 scanner 객체 생성
		System.out.print("아무 키나 입력>> ");
	    scanner.next();  //scanner.nextLine() 으로 하면 문자열을 입력하지 않고 엔터만 눌러도 넘어가기 때문이다.
	    Thread th = new Thread(new TimerRunnable());
		th.start();
	}
}

class TimerRunnable implements Runnable {
	int n =1;
	public void run() {
	    System.out.println("스레드 실행 시작");
		for(int i =0;i<10;i++) { //1부터 10까지 출력하기 위한 반복문
		System.out.print(n+ " ");
		n++;
		}
		System.out.println();
		System.out.println("스레드 종료");
	}
}
