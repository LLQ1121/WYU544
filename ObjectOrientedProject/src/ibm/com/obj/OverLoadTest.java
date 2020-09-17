package ibm.com.obj;

public class OverLoadTest {
	public static void main(String[] args) {
		System.out.println("方法1："+sum(1,2));
		System.out.println("方法2："+sum(1.0,2.0));
		System.out.println("方法3："+sum(1L,2L));
		

	}
	public static int sum(int a,int b) {//方法1
		return a+b;
	}
	public static double sum(double a,double b) {//方法2
		return a+b;
	}
	public static long sum(long a,long b) {//方法3
		return a+b;
	}
}
