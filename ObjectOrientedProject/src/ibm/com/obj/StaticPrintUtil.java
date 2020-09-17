package ibm.com.obj;

import java.util.Date;

public class StaticPrintUtil {
	// 静态变量
		public static String classTopic = "面向对象";

		// 静态方法
		public static void printMessage() {
			System.out.println("这是一个静态方法");
		}

		// 静态代码块
		static {
			Date currentDate = new Date();
			System.out.println("现在时间是 " + currentDate);
			// 只允许访问静态的成员
			System.out.println("我们的课程是 " + classTopic);
			printMessage();
		}	
}
