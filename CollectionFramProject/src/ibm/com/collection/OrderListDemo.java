package ibm.com.collection;

import java.util.ArrayList;
import java.util.List;
public class OrderListDemo {
	public static void main(String[] args) {
		//定义集合
		List list=new ArrayList<>();
		//往集合中添加数据
		list.add("aa");
		list.add("bb");
		list.add("cc");
		list.add("dd");
		//输出显示
		System.out.println("测试List集合的有序性：");
		for (Object o : list) {
			System.out.println(o);
		}
}
}
