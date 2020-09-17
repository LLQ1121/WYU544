package ibm.com.pack.test;
import java.util.Date;
import ibm.com.pack.Phone;
public class Main {
	public static void main(String[] args) {
		// 使用ibm.com.pack包下的Phone类，创建对象
		Phone huawei = new Phone();
		huawei.setCpu(2.5);
		huawei.setMemory(8);
		System.out.println("CPU is " + huawei.getCpu());
		System.out.println("Memory is " + huawei.getMemory());

		// 使用java.uitl包下的Date类， 输出当前时间
		Date currentDate = new Date();
		System.out.println("Current Time " + currentDate);
	}
}
