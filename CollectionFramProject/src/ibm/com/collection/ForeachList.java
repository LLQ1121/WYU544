package ibm.com.collection;

import java.util.ArrayList;
import java.util.List;

public class ForeachList {
	public static void main(String[] args) {
		//定义集合
		List list=new ArrayList<>();
		//往集合中添加数据
		list.add("aa");
		list.add("bb");
		list.add("cc");
		System.out.println("List集合的foreach循环测试：");
		//foreach循环
		for (Object o : list) {
			System.out.println(o);
		}
	}
}
