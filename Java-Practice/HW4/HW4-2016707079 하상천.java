import java.util.Scanner;

public abstract class Calc{
abstract void setValue(int a, int b);
abstract int calculate();
}

public class Add extends Calc{
	public Add() {
	}
private int a,b;
void setValue(int a, int b) {
	this.a=a;
	this.b=b;
}
int calculate() {
	return a+b;
}
}
public class Sub extends Calc{
	public Sub() {
	}
private int a,b;
void setValue(int a, int b) {
	this.a=a;
	this.b=b;
}
int calculate() {
	return a-b;
}
}
public class Mul extends Calc{
	public Mul() {
	}
private int a,b;
void setValue(int a, int b) {
	this.a=a;
	this.b=b;
}
int calculate() {
	return a*b;
}
}
public class Div extends Calc{
	public Div() {
	}
private int a,b;
void setValue(int a, int b) {
	this.a=a;
	this.b=b;
}
int calculate() {
	if(b!=0) {return a/b;}
	else return 0;
}
}

public class Homework4 {

	public static void main(String[] args) {
	int x, y;
	Scanner scanner = new Scanner(System.in);
	while(true) {
	System.out.print("두 정수와 연산자를 입력하시오>>");
	x= scanner.nextInt();
	y = scanner.nextInt();
	char key = scanner.next().charAt(0);
	switch(key) {
	case '+':{
		Add add = new Add();
		add.setValue(x, y);
		System.out.println(add.calculate());
		break;
	}
	case '-':{
		Sub sub =new Sub();
		sub.setValue(x,y);
		System.out.println(sub.calculate());
		break;
	}
	case '*':{
		Mul mul =new Mul();
		mul.setValue(x,y);
		System.out.println(mul.calculate());
		break;
	}
	case '/':{
		Div div =new Div();
		div.setValue(x,y);
		if(div.calculate()!=0) {
		System.out.println(div.calculate());
		break;}
		else  {System.out.println("다시 입력하세요!");
		continue;}
	}
	default: {System.out.println("연산자가 없습니다.");
	continue;}
	}
	break;
	}
	}
}
