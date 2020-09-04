package HA_homework;
import java.util.Vector;

interface IStack<T> {
T pop();
boolean push(T ob);
}

class Mystack<T> implements IStack<T>{
	Vector<T> v = new Vector<T>(10);
	public T pop() { 				// 맨 마지막에 있는 값을 하나씩 리턴해주는 메소드
		int num = v.size();
		if(num == 0) {
			return null;
		}
		else { 
			return v.remove(num-1); //리턴해주고 remove 메소드를 통해 값 삭제
		}
	}
	public boolean push(T ob) { //새로운 값을 넣어주는 메소드
		v.add(ob);
		return true;
	}
}
public class StackManager {

	public static void main(String[] args) {
		IStack<Integer> Stack = new Mystack<Integer>();   //Mystack객체 생성
	      for(int i=0; i<10; i++) {                  //0부터 9까지 값을 넣어주는 반복문
	         Stack.push(i);
	      }
	      while(true) {                           //더이상 값이 없을때까지 반복
	         Integer n = Stack.pop();   
	         if(n==null) {
	            break;
	         }
	         System.out.print(n+" ");               //값 출력
	      } 

	}

}
