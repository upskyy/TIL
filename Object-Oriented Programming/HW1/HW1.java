
public class HW1 {

	public static void main(String[] args) {
		float c=0;
		for(float f=0;f<=300;f+=20) {
			c = (5*(f-32))/9;
			System.out.println((int)f+"   "+String.format("%.1f", c));
		}
	}

}
